package io.tiklab.sourcefare.scan.service;

import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.core.exception.ApplicationException;
import io.tiklab.core.exception.SystemException;
import io.tiklab.licence.licence.model.Version;
import io.tiklab.licence.licence.service.VersionService;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.common.GitUntil;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.common.SourceFareServerFinal;
import io.tiklab.sourcefare.project.model.*;
import io.tiklab.sourcefare.project.service.*;
import io.tiklab.sourcefare.scan.model.*;

import io.tiklab.sourcefare.scan.common.CodeScanCommon;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.sourcefare.scanner.common.ScanCommon;
import io.tiklab.sourcefare.scanner.common.SourceFareFinal;
import io.tiklab.sourcefare.scanner.model.*;

import io.tiklab.sourcefare.scanner.model.ScanResult;
import io.tiklab.sourcefare.scanner.scan.*;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.ObjectUtils;

import javax.servlet.ServletInputStream;
import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.LongStream;

import static io.tiklab.sourcefare.common.SourceFareServerFinal.*;
import static io.tiklab.sourcefare.scanner.common.ScanCommon.getStarTime;
import static io.tiklab.sourcefare.scanner.common.SourceFareFinal.*;

@Service
@Exporter
public class CodeScanServiceImpl implements CodeScanService {
    private static Logger logger = LoggerFactory.getLogger(CodeScanServiceImpl.class);

    @Autowired
    DeployEnvService deployEnvService;

    @Autowired
    VersionService versionService;


    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    PathSetService pathSetService;

    @Autowired
    ScanRecordService recordService;

    @Autowired
    ScanRecordLogService logService;

    @Autowired
    RecordInstanceService recordInstanceService;

    @Autowired
    ScanSchemeRuleService schemeRuleService;


    @Autowired
    ProjectCoverService coverService;

    @Autowired
    ProjectCoverGoService coverGoService;


    @Autowired
    RecordDuplicatedService recordDuplicatedService;

    @Autowired
    RecordComplexityService recordComplexityService;


    @Autowired
    ProjectService projectService;

    @Autowired
    ProjectRepService projectRepService;

    @Autowired
    ProjectRepUploadService repUploadService;

    @Autowired
    ScanSchemeRuleSetService scanSchemeRuleSetService;

    @Autowired
    ProjectEnvService projectEnvService;

    @Autowired
    ScanDoorService scanDoorService;

    @Autowired
    IssueStatisticService issueStatisticService;

    public static Map<String , String> codeScanState = new HashMap<>();

    public void removeScanState(String id){
        codeScanState.remove(id);
    }

    @Override
    public ScanRecord codeScanExec(String projectId) {

        //判断项目的扫描任务是否正在执行
        String execRecord = codeScanState.get(projectId);
        if (!ObjectUtils.isEmpty(execRecord)){
            throw new SystemException(SourceFareServerFinal.SYSTEM_EXCEPTION,"该项目扫描正在执行中");
        }else {
            //添加执行状态，并移除上一次扫描的日志
            codeScanState.put(projectId,"run");
            ScanCommon.scanLogs.remove(projectId);
        }


        Project project = projectService.findProject(projectId);
        project.setScanTime(new Timestamp(System.currentTimeMillis()));

        //查询项目的环境
        List<ProjectEnv> projectEnvList = projectEnvService.findProjectEnvList(new ProjectEnvQuery().setProjectId(projectId));

        //扫描计划中的扫描方案
        ScanScheme scanScheme = project.getScanScheme();

        //查询出规则集
        List<ScanSchemeRuleSet> schemeRuleList = scanSchemeRuleSetService.findScanSchemeRuleSetList(new ScanSchemeRuleSetQuery().setScanSchemeId(scanScheme.getId()));
        if (CollectionUtils.isEmpty(schemeRuleList)){
            codeScanState.remove(projectId);
            throw new SystemException(SourceFareServerFinal.NOT_FOUNT_EXCEPTION,"关联的方案中没有添加规则");
        }
        if ((CLIENT).equals(project.getScanWay())){
            codeScanState.remove(projectId);
            throw new SystemException("扫描方式client错误");
        }

        if ((SERVER_UPLOAD).equals(project.getScanWay())){
            ProjectRepUpload projectRepUpload = repUploadService.findProjectRepUploadByRepId(projectId);
            if (ObjectUtils.isEmpty(projectRepUpload)){
                throw new SystemException("code not found");
            }
           String clonePath = pathSetService.codePath() + "/" + projectId;
            if (!new File(clonePath).exists()){
                throw new SystemException("code not found");
            }
        }


        //初始化扫描记录、日志
        ScanRecord scanRecord = CodeScanCommon.initScanRecord(recordService,project.getId(),"server");
        List<ScanRecordLog> recordLog = logService.createRecordLog(project, scanRecord.getId());
        ObjectMapper mapper = new ObjectMapper();
        List<ScanLog> logs = recordLog.stream()
                .map(map -> mapper.convertValue(map, ScanLog.class))
                .collect(Collectors.toList());

        //添加开始时间、日志到内存中
        ScanCommon.putStarTime(projectId,new Date());
        String lowerCase = scanScheme.getLanguage().toLowerCase();
        ScanCommon.initScanLogs(logs,lowerCase);
        ScanCommon.joinScanLogs(projectId,LOG_COMPILE,2,"[sourceFare] start the server-side scan："+project.getName());


        ExecutorService executorService = Executors.newCachedThreadPool();
        executorService.submit(new Runnable() {
            @Override
            public void run() {
                //初始化扫描结果
                ScanResult scanResult = new ScanResult();
                scanResult.setScanObjectId(projectId);

                String repositoryName=null;
                try {
                    String clonePath=null;

                    //在服务端执行扫描
                    if ((SERVER).equals(project.getScanWay())){

                        List<ProjectRep> repositoryRepList = projectRepService.findProjectRepList(new ProjectRepQuery().setProjectId(projectId));
                        ProjectRep projectRep = repositoryRepList.get(0);
                        repositoryName = projectRep.getRepositoryName();

                        //clone代码
                        clonePath = cloneCode(scanResult,projectRep);
                    }
                    //在服务端upload扫描
                    if ((SERVER_UPLOAD).equals(project.getScanWay())){
                        clonePath = pathSetService.codePath() + "/" + projectId;
                        ProjectRepUpload projectRepUpload = repUploadService.findProjectRepUploadByRepId(projectId);
                        repositoryName=projectRepUpload.getCodeName();
                    }


                    //组装扫描数据
                    ScanData scanData = new ScanData();
                    scanData.setServerProKey(projectId);
                    scanData.setCodePath(clonePath);
                    String cover = project.getCover() == 1 ? "true" : "false";
                    String complexity = project.getComplexity() == 1 ? "true" : "false";
                    scanData.setCover(cover);
                    scanData.setComplexity(complexity);
                    scanData.setScanType("server");


                    //查询问题扫描的环境
                    List<ProjectEnv> projectEnvs = projectEnvList.stream().filter(a -> ("exec").equals(a.getType())).collect(Collectors.toList());


                    if ((SourceFareFinal.JAVA).equals(lowerCase)){
                        //执行环境
                        List<ProjectEnv> execDev = projectEnvList.stream().filter(a -> ("maven").equals(a.getDeployEnv().getEnvType())).collect(Collectors.toList());
                        if (ObjectUtils.isEmpty(execDev)) {
                            throw new ApplicationException("没有maven环境，请在配置maven环境");
                        }

                        scanData.setEnvPath(execDev.get(0).getDeployEnv().getEnvAddress());

                        //启动覆盖测试
                        if (1==project.getCover()){
                            //覆盖测试需要jdk环境
                            List<ProjectEnv> jdkEnv = projectEnvList.stream().filter(a -> ("jdk").equals(a.getDeployEnv().getEnvType())).collect(Collectors.toList());
                            if (ObjectUtils.isEmpty(jdkEnv)) {
                                throw new ApplicationException("The coverage test requires JDK. Please configure the JDK");
                            }
                            scanData.setJdkPath(jdkEnv.get(0).getDeployEnv().getEnvAddress());
                        }

                        scanData.setScanWay(project.getScanType());
                        scanData.setLanguage("java");
                        //执行扫描
                        scanResult =  CodeScanMaven.instance().execScan(scanData);

                        scanResult.setLanguage("java");
                        scanResult.setCodeName(repositoryName);
                    }


                    //javascript 语言扫描
                    if ((SourceFareFinal.JAVA_SCRIPT).equals(lowerCase)){
                        List<ProjectEnv> execDev = projectEnvList.stream().filter(a -> ("node").equals(a.getDeployEnv().getEnvType())).collect(Collectors.toList());
                        if (ObjectUtils.isEmpty(execDev)) {
                            throw new ApplicationException("没有配置Node.js地址");
                        }
                        scanData.setEnvPath(execDev.get(0).getDeployEnv().getEnvAddress());
                        scanData.setLanguage("javascript");
                        //执行扫描
                        scanResult = CodeScanJavaScript.instance().serverScan(scanData);
                        scanResult.setLanguage("javascript");
                        scanResult.setCodeName(repositoryName);
                    }

                    //go 语言扫描
                    if ((SourceFareFinal.GO).equals(lowerCase)){
                        scanData.setLanguage("go");

                        scanResult = CodeScanGo.instance().execScan(scanData);
                        scanResult.setLanguage("go");
                        scanResult.setCodeName(repositoryName);
                    }

                    //C、C++ 语言扫描
                    if ((SourceFareFinal.C).equals(lowerCase)){
                        scanData.setLanguage(SourceFareFinal.C);

                        scanResult = CodeScanC.instance().execScan(scanData);
                        scanResult.setLanguage(SourceFareFinal.C);
                        scanResult.setCodeName(repositoryName);
                    }

                    //c# 语言扫描
                    if ((SourceFareFinal.CC).equals(lowerCase)){
                        String buildPath = project.getBuildPath();
                        if (StringUtils.isNotBlank(buildPath)){

                            String path;
                            int systemType = ProjectUtil.findSystemType();
                            if (systemType==1){
                                String typeAddress = ProjectUtil.SystemTypeAddress(buildPath);
                                String after = StringUtils.substringAfter(typeAddress, "\\");
                                path=clonePath+"\\"+after;
                            }else {
                                String after = StringUtils.substringAfter(buildPath, "/");
                                path=clonePath+"/"+after;
                            }

                           logger.info("build path:"+path);
                            scanData.setBuildPath(path);
                        }

                        //执行环境
                        List<ProjectEnv> execDev = projectEnvList.stream().filter(a -> ("net").equals(a.getDeployEnv().getEnvType())).collect(Collectors.toList());
                        if (ObjectUtils.isEmpty(execDev)) {
                            throw new ApplicationException("没有net环境，请在配置net环境");
                        }
                        scanData.setEnvPath(execDev.get(0).getDeployEnv().getEnvAddress());

                        scanData.setLanguage(SourceFareFinal.CC);

                        scanResult = CodeScanNet.instance().execScan(scanData);
                        scanResult.setLanguage(SourceFareFinal.CC);
                        scanResult.setCodeName(repositoryName);
                    }

                    //python 语言扫描
                    if ((SourceFareFinal.PYTHON).equals(lowerCase)){
                        scanData.setLanguage(SourceFareFinal.PYTHON);

                        scanResult = CodeScanPython.instance().execScan(scanData);
                        scanResult.setLanguage(SourceFareFinal.PYTHON);
                        scanResult.setCodeName(repositoryName);
                    }


                    //扫描完成后添加数据
                    scanCompleteAddData(project,scanResult,scanRecord,scanScheme.getId());
                }catch (Exception e){
                    e.printStackTrace();
                    ScanCommon.joinScanLogs(projectId, LOG_COMPILE,0,"[sourceFare] scan code fail"+e.getMessage());
                    scanResult.setIssueResult(EXEC_FAIL);
                    ScanResult scanResult1 = ScanCommon.initScanResult(scanResult);
                    //更新失败扫描记录
                    updateFailScanRecord(scanRecord,scanResult1);

                    project.setScanResult("fail");
                    projectService.updateProject(project);
                }finally {
                    codeScanState.remove(projectId);
                }
            }});
        return scanRecord;
    }

    @Override
    public void acceptScanResult(HttpServletRequest request) {
        logger.info("接收到客户端提交的扫描结果");
        ScanRecord scanRecord=null;
        ScanResult scanResult=null;
        Project project=null;
        try {
            ServletInputStream inputStream = request.getInputStream();
            ObjectMapper mapper = new ObjectMapper();
             scanResult = mapper.readValue(inputStream, ScanResult.class);// 转换为对象

            String objectId = scanResult.getScanObjectId();
             project = projectService.findOne(objectId);
            ScanScheme scanScheme = project.getScanScheme();

            //获取初始化的扫描记录
             scanRecord = recordService.findScanRecord(scanResult.getScanRecordId());


            scanCompleteAddData(project,scanResult,scanRecord,scanScheme.getId());

        }catch (IOException e) {
            if (!ObjectUtils.isEmpty(scanResult)){
                String scanObjectId = scanResult.getScanObjectId();
                ScanCommon.joinScanLogs(scanObjectId, LOG_COMPILE,0,"[sourceFare] scan code fail"+e.getMessage());
                scanResult.setIssueResult(EXEC_FAIL);
                ScanResult scanResult1 = ScanCommon.initScanResult(scanResult);

                //更新失败扫描记录
                updateFailScanRecord(scanRecord,scanResult1);
                project.setScanResult("fail");
                projectService.updateProject(project);
            }
            throw new RuntimeException(e);
        }
    }

    @Override
    public Map<String,Object> findScanState(String projectId,String recordId) {
        Map<String, Object> hashMap = new HashMap<>();
        List<ScanLog> scanLogs = ScanCommon.getScanLogs(projectId);
        String s = codeScanState.get(projectId);
        hashMap.put("issueResult","run");
        if (StringUtils.isBlank(s)){
            hashMap.put("state","end");
            ScanRecord scanRecord = recordService.findOne(recordId);
            hashMap.put("issueResult",scanRecord.getIssueResult());
            hashMap.put("comResult",scanRecord.getComResult());
            hashMap.put("dupResult",scanRecord.getDupResult());
            hashMap.put("coverResult",scanRecord.getCoverResult());
        }
        Date starTime = getStarTime(projectId);
        if (ObjectUtils.isEmpty(starTime)){
            starTime= new Date(System.currentTimeMillis());
        }

        long allTimeStamp=0L;
        List<ScanLog> logList = scanLogs.stream().filter(a -> a.getState() == 1||a.getState() ==0).collect(Collectors.toList());
        if (CollectionUtils.isNotEmpty(logList)){
             allTimeStamp = logList.stream().mapToLong(ScanLog::getTimestamp).sum();
        }

        List<ScanLog> logRunList = scanLogs.stream().filter(a -> a.getState() == 2).collect(Collectors.toList());
        for (ScanLog scanLog:logRunList){
            long timestamp = new Date().getTime()-scanLog.getStartTime().getTime();
            long l = timestamp <1000 ? 1000 : timestamp;
            allTimeStamp+=l;
            scanLog.setTime(ProjectUtil.timestamp(l,"scan"));
        }

        String time = ProjectUtil.timestamp(allTimeStamp,"scan");
        hashMap.put("createTime",getStarTime(projectId));
        hashMap.put("scanTime",time);
        hashMap.put("Logs",scanLogs);
        return hashMap;
    }


    /**
     * 扫描完成后添加数据
     * @param scanResult 扫描结果
     * @param scanRecord 扫描记录
     * @param scanSchemeId 扫描方案的id
     * @throws ApplicationException 运行失败
     */
    public void scanCompleteAddData(Project project,
                                    ScanResult scanResult,
                                    ScanRecord scanRecord,
                                    String scanSchemeId){

        try {
            //扫描成功创建扫描文件信息
            if (!ObjectUtils.isEmpty(scanResult)){
                scanResult.setScanRecordId(scanRecord.getId());

                //问题扫描结果
                String issueResult = scanResult.getIssueResult();
                if ((SUCCESS).equals(issueResult)){

                    //根据当前是否订阅。  查询扫描方案关联的扫描规则
                    Version version = versionService.getVersion();
                    List<ScanSchemeRule> schemeRuleList;
                    if (version.getRelease()==1){

                       schemeRuleList = schemeRuleService.findScanSchemeRuleList(new ScanSchemeRuleQuery()
                                .setScanSchemeId(scanSchemeId).setProperty(0));

                    }else {
                        schemeRuleList = schemeRuleService.findScanSchemeRuleList(new ScanSchemeRuleQuery()
                                .setScanSchemeId(scanSchemeId));
                    }
                    List<ScanSchemeRule> scanSchemeRules = schemeRuleList.stream().filter(a -> a.getIsDisable() == 0).collect(Collectors.toList());

                    //创建扫描问题的实例
                    List<RecordInstance> recordInstance = CodeScanCommon.createRecordInstance(scanSchemeRules, recordInstanceService, scanRecord, scanResult);

                    if (CollectionUtils.isNotEmpty(recordInstance)){
                        //项目扫描门禁
                        ScanDoor scanDoor = scanDoorService.findScanDoorByProjectId(project.getId());
                        if (scanDoor.getSeverityState()==1&&scanDoor.getSeverityNum()<scanRecord.getSeverityTrouble()){
                            issueResult="fail";
                        }
                        if (scanDoor.getNoticeState()==1&&scanDoor.getNoticeNum()<scanRecord.getNoticeTrouble()){
                            issueResult="fail";
                        }
                        if (scanDoor.getErrorState()==1&&scanDoor.getErrorNum()<scanRecord.getErrorTrouble()){
                            issueResult="fail";
                        }
                        if (scanDoor.getSuggestState()==1&&scanDoor.getSuggestNum()<scanRecord.getSuggestTrouble()){
                            issueResult="fail";
                        }


                        Thread thread = new Thread() {
                            public void run() {
                                //创建问题统计
                                CodeScanCommon.createIssueStatistic(issueStatisticService,scanSchemeRules,recordInstance);
                            }};
                        thread.start();
                    }
                }

                //复杂度
                String comResult = scanResult.getComResult();
                if ((SUCCESS).equals(comResult)){
                    CodeScanCommon.createProjectComplexity(recordComplexityService,scanResult);
                }

                //重复度
                String dupResult = scanResult.getDupResult();
                if ((SUCCESS).equals(dupResult)){
                    CodeScanCommon.createProjectDuplicated(recordDuplicatedService,scanResult);
                }

                //覆盖率
                String coverResult = scanResult.getCoverResult();
                if ((SUCCESS).equals(coverResult)){
                    this.createCover(scanResult);
                }



                //扫描时间
                this.updateRecordLog(scanResult);
                long sum =  scanResult.getLogs().stream().filter(a->a.getState()!=3).mapToLong(ScanLog::getTimestamp).sum();
                String time = ProjectUtil.timestamp(sum, "scan");


                //更新扫描记录
                scanRecord.setIssueResult(issueResult);
                scanRecord.setDupResult(dupResult);
                scanRecord.setComResult(comResult);
                scanRecord.setCoverResult(coverResult);
                scanRecord.setScanTime(time);
                recordService.updateScanRecord(scanRecord);


                //更新扫描项目最近扫描状态
                if (EXEC_FAIL.equals(dupResult)||EXEC_FAIL.equals(comResult)||
                        EXEC_FAIL.equals(coverResult)|| EXEC_FAIL.equals(issueResult)){
                    project.setScanResult(EXEC_FAIL);
                }else {
                    project.setScanResult(SUCCESS);
                }
                project.setScanTime(new Timestamp(System.currentTimeMillis()));
                projectService.updateProject(project);
            }
        }catch (Exception e){
            e.printStackTrace();
            logger.error("扫描结束，创建扫描结果失败："+e.getMessage());
            //更新失败扫描记录
            updateFailScanRecord(scanRecord,scanResult);
        }
    }




    /**
     *  clone代码
     * @param  projectRep projectRep
     */
    public String cloneCode(ScanResult scanResult,ProjectRep projectRep)  {
        String projectId = projectRep.getProjectId();

        String backupsPath = pathSetService.codePath() + "/" + projectRep.getRepositoryName();

        logger.info("拉取代码:"+projectRep.getRepositoryName());
        ScanCommon.joinScanLogs(projectId, LOG_COMPILE,2,"[sourceFare] execute the code clone:"+projectRep.getRepositoryName());

        //本地存储地址
        String codePath = pathSetService.codePath() + "/" + projectId;
        File file = new File(codePath);
        if (file.exists()) {
            //界面中需要定位到错误在代码文件中具体的位置，防止删除后没有拉取到最新代码
            boolean dirName = SourceFareUtil.updateDirName(codePath, backupsPath, 1);
            if (!dirName){
                ScanCommon.joinScanLogs(projectId, LOG_COMPILE,0,"[sourceFare] code acquisition fail");
                scanResult.setIssueResult(EXEC_FAIL);
                throw new RuntimeException("修改代码文件名失败");
            }
            // FileUtils.deleteDirectory(new File(codePath));
        }

        //克隆裸仓库中
        try {
            String address = projectRep.getRepositoryAddress();
            if (address.contains("http")){
                int firstSlash = address.indexOf('/', address.indexOf('/', address.indexOf('/') + 1) + 1);

                String substring = address.substring(firstSlash);
                address = projectRep.getRepositoryServer().getAddress()+  substring;

            }

            logger.info("[sourceFare]  code clone path:"+address);
            ScanCommon.joinScanLogs(projectId, LOG_COMPILE,2,"[sourceFare]  code clone path:"+address);

             GitUntil.cloneRepository(projectRep.getRepositoryServer(),address, projectRep.getBranch(),codePath);

             //拉取成功删除备份的数据
             FileUtils.deleteDirectory(new File(backupsPath));
            ScanCommon.joinScanLogs(projectId, LOG_COMPILE,2,"[sourceFare]  code clone success");
            return codePath;
        } catch (Exception e) {
            e.printStackTrace();
            //拉取失败将原本的代码文件名恢复
            SourceFareUtil.updateDirName(backupsPath,codePath , 1);
            ScanCommon.joinScanLogs(projectId, LOG_COMPILE,0,"[sourceFare]  code clone fail:"+e.getMessage());
            scanResult.setIssueResult(EXEC_FAIL);
            throw new RuntimeException(e.getMessage());
        }
    }



    /**
     *  更新扫描失败状态
     *  @param scanRecord scanRecord
     */
    public  void updateFailScanRecord(ScanRecord scanRecord,ScanResult scanResult) {

        String projectId = scanRecord.getProjectId();

        scanRecord.setIssueResult("execFail");
        String time = SourceFareUtil.time(ScanCommon.getStarTime(projectId),"scan");
        scanRecord.setScanTime(time);
        recordService.updateScanRecord(scanRecord);

        //创建扫描记录日志
        updateRecordLog(scanResult);
    }

    /**
     *  创建服务端扫描记录日志
     *  @param scanRecord scanRecord
     */
    /*public  void createRecordLog(ScanRecord scanRecord) {

        ScanRecordLog recordLog = new ScanRecordLog();
        String projectId = scanRecord.getProjectId();
        recordLog.setProjectId(projectId);
        recordLog.setScanRecordId(scanRecord.getId());


        List<ScanLog> scanLogs = ScanCommon.getScanLogs(projectId);
        if (CollectionUtils.isNotEmpty(scanLogs)){
            for (ScanLog scanLog:scanLogs){
                recordLog.setExecLog(scanLog.getExecLog());
                recordLog.setTime(scanLog.getTime());
                recordLog.setType(scanLog.getType());
                SourceFareUtil.addLogOrder(recordLog,scanLog.getType());
                recordLogService.createScanRecordLog(recordLog);
            }
        }
    }*/

    /**
     *  更新客户端扫描记录日志
     *  @param scanResult scanResult
     */
    public  void updateRecordLog(ScanResult scanResult) {

        List<ScanLog> resultLogs = scanResult.getLogs();
        if (CollectionUtils.isNotEmpty(resultLogs)){
            for (ScanLog scanLog:resultLogs){
                if (scanLog.getState()==2){
                    scanLog.setState(0);
                }
                ScanRecordLog scanRecordLog = new ScanRecordLog();
                BeanUtils.copyProperties(scanLog,scanRecordLog);

                logService.updateScanRecordLog(scanRecordLog);
            }
        }
    }



    /**
     *  创建覆盖率
     *  @param scanResult scanResult
     */
    public void createCover(ScanResult scanResult){
        List<Cover> coverList = scanResult.getProjectCoverList();
        if (CollectionUtils.isNotEmpty(coverList)){
            for (Cover cover:coverList){
                if (("go").equals(scanResult.getLanguage())){
                    ProjectCoverGo projectCoverGo = new ProjectCoverGo();
                    BeanUtils.copyProperties(cover, projectCoverGo);

                    projectCoverGo.setProjectId(scanResult.getScanObjectId());
                    projectCoverGo.setScanRecordId(scanResult.getScanRecordId());
                    projectCoverGo.setFilePath(cover.getPath());
                    coverGoService.createProjectCoverGo(projectCoverGo);
                }
                if (("java").equals(scanResult.getLanguage())){
                    ProjectCover projectCover = new ProjectCover();
                    BeanUtils.copyProperties(cover, projectCover);

                    projectCover.setProjectId(scanResult.getScanObjectId());
                    projectCover.setScanRecordId(scanResult.getScanRecordId());
                    coverService.createProjectCover(projectCover);
                }
             }
        }
    }

}
