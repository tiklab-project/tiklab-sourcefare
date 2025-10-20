package io.tiklab.sourcefare.scan.service;

import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.core.exception.ApplicationException;
import io.tiklab.core.exception.SystemException;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.common.GitUntil;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.common.SourceWairServerFinal;
import io.tiklab.sourcefare.project.model.*;
import io.tiklab.sourcefare.project.service.*;
import io.tiklab.sourcefare.scan.model.*;

import io.tiklab.sourcefare.scan.common.CodeScanCommon;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.sourcefare.scanner.common.ScanCommon;
import io.tiklab.sourcefare.scanner.common.SourceFareFinal;
import io.tiklab.sourcefare.scanner.model.*;

import io.tiklab.sourcefare.scanner.model.ScanResult;
import io.tiklab.sourcefare.scanner.model.ScanResultFile;
import io.tiklab.sourcefare.scanner.scan.*;
import io.tiklab.toolkit.context.AppContext;
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
import java.sql.Date;
import java.sql.Timestamp;
import java.util.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;

import static io.tiklab.sourcefare.scanner.common.ScanCommon.getStarTime;
import static io.tiklab.sourcefare.scanner.common.SourceFareFinal.LOG_COMPILE;
import static io.tiklab.sourcefare.scanner.common.SourceFareFinal.LOG_SCAN;

@Service
@Exporter
public class CodeScanServiceImpl implements CodeScanService {
    private static Logger logger = LoggerFactory.getLogger(CodeScanServiceImpl.class);

    @Autowired
    DeployEnvService deployEnvService;


    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    PathSetService pathSetService;

    @Autowired
    ScanRecordService recordService;

    @Autowired
    ScanRecordLogService recordLogService;

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



    @Override
    public ScanRecord codeScanExec(String projectId) {

        //判断项目的扫描任务是否正在执行
        String execRecord = codeScanState.get(projectId);
        if (!ObjectUtils.isEmpty(execRecord)){
            throw new SystemException(SourceWairServerFinal.SYSTEM_EXCEPTION,"该项目扫描正在执行中");
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

        //添加扫描开始时间和第一阶段任务的开始时间 （服务端添加）
        ScanCommon.putStarTime(projectId,new Date(System.currentTimeMillis()));
        ScanCommon.putExecStarTime(projectId,new Date(System.currentTimeMillis()));
        ScanCommon.joinScanLogs(projectId,LOG_COMPILE,"[sourceFare] Start the server-side scan："+project.getName());


        //查询出规则集
        List<ScanSchemeRuleSet> schemeRuleList = scanSchemeRuleSetService.findScanSchemeRuleSetList(new ScanSchemeRuleSetQuery().setScanSchemeId(scanScheme.getId()));
        if (CollectionUtils.isEmpty(schemeRuleList)){
            codeScanState.remove(projectId);
            throw new SystemException(SourceWairServerFinal.NOT_FOUNT_EXCEPTION,"关联的方案中没有添加规则");
        }
        if (("client").equals(project.getScanWay())){
            codeScanState.remove(projectId);
            throw new SystemException("扫描方式client错误");
        }
        //初始化扫描记录
        ScanRecord scanRecord = CodeScanCommon.initScanRecord(recordService,project.getId(),"server");


        ExecutorService executorService = Executors.newCachedThreadPool();
        executorService.submit(new Runnable() {
            @Override
            public void run() {

                String repositoryName=null;
                try {
                    String clonePath=null;

                    //在服务端执行扫描
                    if (("server").equals(project.getScanWay())){


                        List<ProjectRep> repositoryRepList = projectRepService.findProjectRepList(new ProjectRepQuery().setProjectId(projectId));
                        ProjectRep projectRep = repositoryRepList.get(0);
                        repositoryName = projectRep.getRepositoryName();


                        //clone代码
                        clonePath = cloneCode(projectRep);
                    }

                    //在服务端upload扫描
                    if (("serverUpload").equals(project.getScanWay())){
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
                    ScanResult scanResult=null;

                    //查询问题扫描的环境
                    List<ProjectEnv> projectEnvs = projectEnvList.stream().filter(a -> ("exec").equals(a.getType())).collect(Collectors.toList());



                    String lowerCase = scanScheme.getLanguage().toLowerCase();
                    if ((SourceFareFinal.JAVA).equals(lowerCase)){
                        //执行环境
                        List<ProjectEnv> execDev = projectEnvList.stream().filter(a -> ("maven").equals(a.getDeployEnv().getEnvType())).collect(Collectors.toList());
                        if (ObjectUtils.isEmpty(execDev)) {
                            throw new ApplicationException("没有maven环境，请在设置扫描配置里面配置maven环境");
                        }


                        scanData.setEnvPath(execDev.get(0).getDeployEnv().getEnvAddress());

                        //启动覆盖测试
                        if (1==project.getCover()){
                            //覆盖测试需要jdk环境
                            List<ProjectEnv> jdkEnv = projectEnvList.stream().filter(a -> ("jdk").equals(a.getDeployEnv().getEnvType())).collect(Collectors.toList());
                            if (ObjectUtils.isEmpty(jdkEnv)) {
                                ScanCommon.joinScanLog(projectId,"覆盖测试需要JDK，请在设置扫描配置里面配置JDK");
                                throw new ApplicationException("覆盖测试需要JDK，请在设置扫描配置里面配置JDK");
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
                            //即没有关联的node也没有全局的node
                            ScanCommon.joinScanLog(projectId, "Node.js未正确安装");

                            //更新失败扫描记录
                            updateFailScanRecord(scanRecord);

                            project.setScanResult("fail");
                            projectService.updateProject(project);
                            throw new ApplicationException("没有配置Node.js地址，也没有全局的Node.js环境");
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
                    ScanCommon.joinScanLog(projectId,"扫描失败："+e.getMessage());

                    //更新失败扫描记录
                    updateFailScanRecord(scanRecord);
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
        try {
            ServletInputStream inputStream = request.getInputStream();
            ObjectMapper mapper = new ObjectMapper();
            ScanResult scanResult = mapper.readValue(inputStream, ScanResult.class);// 转换为对象

            String objectId = scanResult.getScanObjectId();
            Project project = projectService.findOne(objectId);
            ScanScheme scanScheme = project.getScanScheme();

            //获取初始化的扫描记录
            ScanRecord scanRecord = recordService.findScanRecord(scanResult.getScanRecordId());


            scanCompleteAddData(project,scanResult,scanRecord,scanScheme.getId());

        }catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Map<String,Object> findScanState(String projectId,String recordId) {
        Map<String, Object> hashMap = new HashMap<>();
        List<ScanLog> scanLogs = ScanCommon.getScanLogs(projectId);
        String s = codeScanState.get(projectId);
        hashMap.put("scanResult","run");
        if (StringUtils.isBlank(s)){
            hashMap.put("state","end");
            ScanRecord scanRecord = recordService.findOne(recordId);
            hashMap.put("scanResult",scanRecord.getScanResult());
        }
        Date starTime = getStarTime(projectId);
        if (ObjectUtils.isEmpty(starTime)){
            starTime= new Date(System.currentTimeMillis());
        }

        String time = ProjectUtil.time(getStarTime(projectId),"scan");
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

                //扫描结果
                String result=scanResult.getResult();
                if (("success").equals(scanResult.getResult())){

                    //查询扫描方案关联的扫描规则
                    List<ScanSchemeRule> schemeRuleList = schemeRuleService.findScanSchemeRuleList(new ScanSchemeRuleQuery().setScanSchemeId(scanSchemeId));
                    List<ScanSchemeRule> scanSchemeRules = schemeRuleList.stream().filter(a -> a.getIsDisable() == 0).collect(Collectors.toList());


                    //创建扫描问题的实例
                    CodeScanCommon.createRecordInstance(scanSchemeRules,recordInstanceService,scanRecord,scanResult);


                    //项目扫描门禁
                    ScanDoor scanDoor = scanDoorService.findScanDoorByProjectId(project.getId());
                    if (scanDoor.getSeverityState()==1&&scanDoor.getSeverityNum()<scanRecord.getSeverityTrouble()){
                        result="fail";
                    }
                    if (scanDoor.getNoticeState()==1&&scanDoor.getNoticeNum()<scanRecord.getNoticeTrouble()){
                        result="fail";
                    }
                    if (scanDoor.getErrorState()==1&&scanDoor.getErrorNum()<scanRecord.getErrorTrouble()){
                        result="fail";
                    }
                    if (scanDoor.getSuggestState()==1&&scanDoor.getSuggestNum()<scanRecord.getSuggestTrouble()){
                        result="fail";
                    }


                    //创建覆盖率
                    this.createCover(scanResult);

                    //创建重复数据
                    CodeScanCommon.createProjectDuplicated(recordDuplicatedService,scanResult);

                    //创建复杂度
                    CodeScanCommon.createProjectComplexity(recordComplexityService,scanResult);

                    Thread thread = new Thread() {
                        public void run() {
                            //创建问题统计
                            CodeScanCommon.createIssueStatistic(issueStatisticService,scanSchemeRules,scanResult);
                        }};
                    thread.start();
                }



                //扫描时间
                String time;
                if (("client").equals(scanResult.getScanWay())){
                    time = ("0秒").equals(scanResult.getScanTime()) ? "1秒" : scanResult.getScanTime();
                    //创建扫描日志
                    this.createClientRecordLog(scanResult);

                }else {
                    time = SourceFareUtil.time(ScanCommon.getStarTime(project.getId()),"scan");
                    //创建扫描日志
                    this.createRecordLog(scanRecord);
                }

                //更新扫描记录
                scanRecord.setScanTime(time);
                scanRecord.setScanResult(result);
                recordService.updateScanRecord(scanRecord);


                //更新扫描项目最近扫描状态
                project.setScanTime(new Timestamp(System.currentTimeMillis()));
                project.setScanResult(result);
                projectService.updateProject(project);
            }
        }catch (Exception e){
            e.printStackTrace();
            logger.error("扫描结束，创建扫描结果失败："+e.getMessage());
            //更新失败扫描记录
            updateFailScanRecord(scanRecord);
        }
    }




    /**
     *  clone代码
     * @param  projectRep projectRep
     */
    public String cloneCode(ProjectRep projectRep)  {
        String projectId = projectRep.getProjectId();

        String backupsPath = pathSetService.codePath() + "/" + projectRep.getRepositoryName();

        logger.info("拉取代码:"+projectRep.getRepositoryName());
        ScanCommon.joinScanLogs(projectId, LOG_COMPILE,"[sourceFare] execute the code clone:"+projectRep.getRepositoryName());

        //本地存储地址
        String codePath = pathSetService.codePath() + "/" + projectId;
        File file = new File(codePath);
        if (file.exists()) {
            //界面中需要定位到错误在代码文件中具体的位置，防止删除后没有拉取到最新代码
            boolean dirName = SourceFareUtil.updateDirName(codePath, backupsPath, 1);
            if (!dirName){
                ScanCommon.joinScanLogs(projectId, LOG_COMPILE,"[sourceFare] code acquisition fail");
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
            ScanCommon.joinScanLogs(projectId, LOG_COMPILE,"[sourceFare]  code clone path:"+address);

             GitUntil.cloneRepository(projectRep.getRepositoryServer(),address, projectRep.getBranch(),codePath);

             //拉取成功删除备份的数据
             FileUtils.deleteDirectory(new File(backupsPath));
            ScanCommon.joinScanLogs(projectId, LOG_COMPILE,"[sourceFare]  code clone success");
            return codePath;
        } catch (Exception e) {
            e.printStackTrace();
            //拉取失败将原本的代码文件名恢复
            SourceFareUtil.updateDirName(backupsPath,codePath , 1);
            ScanCommon.joinScanLogs(projectId, LOG_COMPILE,"[sourceFare]  code clone fail:"+e.getMessage());
            throw new RuntimeException(e.getMessage());
        }
    }



    /**
     *  更新扫描失败状态
     *  @param scanRecord scanRecord
     */
    public  void updateFailScanRecord(ScanRecord scanRecord) {

        String projectId = scanRecord.getProjectId();

        scanRecord.setScanResult("execFail");
        String time = SourceFareUtil.time(ScanCommon.getExecStarTime(projectId),"scan");
        scanRecord.setScanTime(time);
        recordService.updateScanRecord(scanRecord);

        //创建扫描记录日志
        createRecordLog(scanRecord);
    }

    /**
     *  创建服务端扫描记录日志
     *  @param scanRecord scanRecord
     */
    public  void createRecordLog(ScanRecord scanRecord) {

        ScanRecordLog recordLog = new ScanRecordLog();
        String projectId = scanRecord.getProjectId();
        recordLog.setProjectId(projectId);
        recordLog.setScanRecordId(scanRecord.getId());


        List<ScanLog> scanLogs = ScanCommon.getScanLogs(projectId);
        if (CollectionUtils.isNotEmpty(scanLogs)){
            for (ScanLog scanLog:scanLogs){
                recordLog.setExecLog(scanLog.getExecLog());
                recordLog.setTime(scanLog.getScanTime());
                recordLog.setType(scanLog.getGroup());
                addLogOrder(recordLog,scanLog.getGroup());
                recordLogService.createScanRecordLog(recordLog);
            }
        }

        /*Map<String,String> resultLogs = ScanCommon.getScanLogs(projectId);
        Set<String> mapKey = resultLogs.keySet();
        //扫描日志
        for (String key:mapKey){
            if (key.endsWith("time")){
                continue;
            }
            String s = resultLogs.get(key);
            String time = resultLogs.get(key+"time");
            recordLog.setExecLog(s);
            recordLog.setTime(time);
            recordLog.setType(key);

            addLogOrder(recordLog,key);
            recordLogService.createScanRecordLog(recordLog);
        }*/
    }

    /**
     *  创建客户端扫描记录日志
     *  @param scanResult scanResult
     */
    public  void createClientRecordLog(ScanResult scanResult) {

        ScanRecordLog recordLog = new ScanRecordLog();
        String projectId = scanResult.getScanObjectId();
        recordLog.setProjectId(projectId);
        recordLog.setScanRecordId(scanResult.getScanRecordId());

        List<ScanLog> resultLogs = scanResult.getLogs();
        if (CollectionUtils.isNotEmpty(resultLogs)){
            for (ScanLog scanLog:resultLogs){
                recordLog.setExecLog(scanLog.getExecLog());
                recordLog.setTime(scanLog.getScanTime());
                recordLog.setType(scanLog.getGroup());
                addLogOrder(recordLog,scanLog.getGroup());
                recordLogService.createScanRecordLog(recordLog);
            }
        }
        //扫描日志
        /*Map<String,String> resultLogs = scanResult.getLogs();
        if (ObjectUtils.isEmpty(resultLogs)){
            return;
        }
        Set<String> mapKey = resultLogs.keySet();

        for (String key:mapKey){
            if (key.endsWith("time")){
                continue;
            }
            String s = resultLogs.get(key);
            String time = resultLogs.get(key+"time");
            recordLog.setExecLog(s);
            recordLog.setTime(time);
            recordLog.setType(key);
            addLogOrder(recordLog,key);
            recordLogService.createScanRecordLog(recordLog);
        }*/
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


    public void addLogOrder(ScanRecordLog recordLog,String type){
        switch (type){
            case LOG_COMPILE -> {
                recordLog.setSort(1);
                recordLog.setTitle("项目构建");
            }
            case SourceFareFinal.LOG_SCAN_ENV -> {
                recordLog.setSort(1);
                recordLog.setTitle("初始扫描环境");
            }
            case SourceFareFinal.LOG_SCAN -> {
                recordLog.setSort(2);
                recordLog.setTitle("问题扫描");
            }
            case SourceFareFinal.LOG_DUPLICATED -> {
                recordLog.setSort(3);
                recordLog.setTitle("重复度扫描");
            }
            case SourceFareFinal.LOG_COMPLEXITY -> {
                recordLog.setSort(4);
                recordLog.setTitle("复杂度扫描");
            }
            case SourceFareFinal.LOG_COVER -> {
                recordLog.setSort(5);
                recordLog.setTitle("覆盖率扫描");
            }
        }
    }

}
