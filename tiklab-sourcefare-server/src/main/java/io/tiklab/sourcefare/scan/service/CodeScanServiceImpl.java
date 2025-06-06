package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.exception.ApplicationException;
import io.tiklab.core.exception.SystemException;
import io.tiklab.sourcefare.common.GitUntil;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.common.SourceWairServerFinal;
import io.tiklab.sourcefare.scan.model.*;

import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.common.CodeScanCommon;
import io.tiklab.sourcefare.scanner.common.ScanCommon;
import io.tiklab.sourcefare.scanner.model.ScanResult;
import io.tiklab.sourcefare.scanner.scan.CodeScanGo;
import io.tiklab.sourcefare.scanner.scan.CodeScanJava;
import io.tiklab.sourcefare.scanner.scan.CodeScanJavaScript;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.io.FileUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.ObjectUtils;

import java.io.File;
import java.sql.Date;
import java.util.*;
import java.util.stream.Collectors;

@Service
public class CodeScanServiceImpl implements CodeScanService {
    private static Logger logger = LoggerFactory.getLogger(CodeScanServiceImpl.class);

    @Autowired
    DeployEnvService deployEnvService;


    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    PathSetService pathSetService;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    ScanRecordInstanceService recordInstanceService;

    @Autowired
    ScanSchemeRuleService schemeRuleService;

    @Autowired
    ScanPlayService scanPlayService;

    @Autowired
    ScanSchemeRuleSetService scanSchemeRuleSetService;


   /* @Autowired
    CodeScanSpotBugsService scanSpotBugsService;*/
/*

    @Autowired
    CodeScanJavaScriptService codeScanJavaScriptService;

    @Autowired
    CodeScanGoService codeScanGoService;
*/


    public static Map<String , String> codeScanState = new HashMap<>();



    @Override
    public String codeScanExec(String scanPlayId) {
        logger.info("开始执行服务端扫描");
        ScanPlay scanPlay = scanPlayService.findOne(scanPlayId);

        //扫描计划中的扫描方案
        ScanScheme scanScheme = scanPlay.getScanScheme();

        ScanCommon.joinScanLog(scanPlayId,"开始执行服务端扫描："+scanPlay.getPlayName());
        ScanCommon.putExecStarTime(scanPlayId,new Date(System.currentTimeMillis()));

        //在服务端执行扫描
        if (("server").equals(scanPlay.getScanWay())){
          /*  String execRecord = codeScanState.get(scanPlayId);
            if (!ObjectUtils.isEmpty(execRecord)){
                throw new SystemException(SourceWairFinal.SYSTEM_EXCEPTION,"该扫描计划正在执行中");
            }*/
            //查询出规则集
            List<ScanSchemeRuleSet> schemeRuleList = scanSchemeRuleSetService.findScanSchemeRuleSetList(new ScanSchemeRuleSetQuery().setScanSchemeId(scanScheme.getId()));
            if (CollectionUtils.isEmpty(schemeRuleList)){
                ScanCommon.joinScanLog(scanPlayId,"关联的方案中没有添加规则");
                throw new SystemException(SourceWairServerFinal.NOT_FOUNT_EXCEPTION,"关联的方案中没有添加规则");
            }

            //开始构建项目
            DeployEnv deployEnv = deployEnvService.findOne(scanScheme.getDeployEnvId());

            //初始化扫描记录
            ScanRecord scanRecord = CodeScanCommon.initScanRecord(scanRecordService,scanPlay);

            try {
                //clone代码
                String clonePath = cloneCode(scanPlay);


                String lowerCase = scanScheme.getLanguage().toLowerCase();
                if (("java").equals(lowerCase)){
                    if (ObjectUtils.isEmpty(deployEnv)) {
                        ScanCommon.joinScanLog(scanPlayId,"执行SpotbugsBug扫描需要编译代码，计划关联的扫描方案没有配置maven环境，请在设置扫描配置里面配置maven环境");
                        throw new ApplicationException("执行SpotbugsBug扫描需要编译代码，计划关联的扫描方案没有配置maven环境，请在设置扫描配置里面配置maven环境");
                    }

                    //执行编译项目
                    Process buildProcess = SourceFareUtil.mavenBuild(deployEnv.getEnvAddress(), clonePath);
                    boolean state = CodeScanCommon.readExecResult(buildProcess,scanPlayId);
                    logger.info("SpotBugs扫描->mvn 编译结果"+state);
                    if (state){
                        ScanCommon.joinScanLog(scanPlayId,"编译成功，执行扫描");

                        //执行扫描
                        ScanResult  scanResult =  CodeScanJava.instance().serverScan(scanPlayId, clonePath);
                        scanResult.setLanguage("java");
                        scanResult.setCodeName(scanPlay.getRepositoryName());
                        //扫描完成后添加数据
                        scanCompleteAddData(scanResult,scanRecord,scanScheme.getId());

                    }else {
                        ScanCommon.joinScanLog(scanPlayId,"编译失败");
                        CodeScanCommon.updateFailScanRecord(scanRecordService,scanRecord);
                    }
                }


                //javascript 语言扫描
                if (("javascript").equals(lowerCase)){
                    if (ObjectUtils.isEmpty(deployEnv)) {
                        //即没有关联的node也没有全局的node
                        ScanCommon.joinScanLog(scanPlayId, "Node.js未正确安装");
                        CodeScanCommon.updateFailScanRecord(scanRecordService,scanRecord);
                        throw new ApplicationException("没有配置Node.js地址，也没有全局的Node.js环境");
                    }
                   //执行扫描
                    ScanResult scanResult = CodeScanJavaScript.instance().serverScan(scanPlayId, clonePath, deployEnv.getEnvAddress());
                    scanResult.setLanguage("javascript");
                    scanResult.setCodeName(scanPlay.getRepositoryName());
                    //扫描完成后添加数据
                    scanCompleteAddData(scanResult,scanRecord,scanScheme.getId());
                }


                //go 语言扫描
                if (("go").equals(lowerCase)){
                    ScanResult  scanResult = CodeScanGo.instance().serverScan(scanPlayId, clonePath);
                    scanResult.setLanguage("go");
                    scanResult.setCodeName(scanPlay.getRepositoryName());
                    //扫描完成后添加数据
                    scanCompleteAddData(scanResult,scanRecord,scanScheme.getId());
                }


            }catch (Exception e){
                e.printStackTrace();
                ScanCommon.joinScanLog(scanPlayId,"扫描失败："+e.getMessage());
                CodeScanCommon.updateFailScanRecord(scanRecordService,scanRecord);
            }
        }

        return "ok";
    }




    /**
     * 扫描完成后添加数据
     * @param scanResult 扫描结果
     * @param scanRecord 扫描记录
     * @param scanSchemeId 扫描方案的id
     * @throws ApplicationException 运行失败
     */
    public void scanCompleteAddData(ScanResult scanResult,
                                    ScanRecord scanRecord,
                                    String scanSchemeId){
        //扫描成功创建扫描文件信息
        if (!ObjectUtils.isEmpty(scanResult)){
            if (("success").equals(scanResult.getResult())){

                //查询扫描方案关联的扫描规则
                List<ScanSchemeRule> schemeRuleList = schemeRuleService.findScanSchemeRuleList(new ScanSchemeRuleQuery().setScanSchemeId(scanSchemeId));
                List<ScanSchemeRule> scanSchemeRules = schemeRuleList.stream().filter(a -> a.getIsDisable() == 0).collect(Collectors.toList());

                //创建扫描结果文件
                CodeScanCommon.createRecordInstance(scanSchemeRules,recordInstanceService,scanRecord,scanResult);
                CodeScanCommon.updateScanRecord(scanRecordService,scanRecord,scanResult);
            }
         return;
        }
        CodeScanCommon.updateFailScanRecord(scanRecordService,scanRecord);
    }









    /**
     *  clone代码
     * @param  scanPlay scanPlay
     */
    public String cloneCode(ScanPlay scanPlay)  {

        String backupsPath = pathSetService.codePath() + "/" + scanPlay.getRepositoryName();

        ScanCommon.joinScanLog(scanPlay.getId(),"执行代码clone");
        //本地存储地址
        String codePath = pathSetService.codePath() + "/" + scanPlay.getId();
        logger.info("SpotBugs扫描->git clone");
        File file = new File(codePath);
        if (file.exists()) {
            //界面中需要定位到错误在代码文件中具体的位置，防止删除后没有拉取到最新代码
            boolean dirName = SourceFareUtil.updateDirName(codePath, backupsPath, 1);
            if (!dirName){
                logger.info("修改代码文件名失败");
                ScanCommon.joinScanLog(scanPlay.getId(),"代码获取失败");
                throw new RuntimeException("修改代码文件名失败");
            }
            // FileUtils.deleteDirectory(new File(codePath));
        }

        //克隆裸仓库中
        try {
             GitUntil.cloneRepository(scanPlay.getRepositoryServer(),scanPlay.getRepositoryAddress(), scanPlay.getBranch(),codePath);
             ScanCommon.joinScanLog(scanPlay.getId(),"拉取代码"+scanPlay.getRepositoryAddress()+"成功，开始执行编译");

             //拉取成功删除备份的数据
             FileUtils.deleteDirectory(new File(backupsPath));
             return codePath;
        } catch (Exception e) {
            //拉取失败将原本的代码文件名恢复
           SourceFareUtil.updateDirName(backupsPath,codePath , 1);
            ScanCommon.joinScanLog(scanPlay.getId(),"代码拉取失败:"+e.getMessage());
            throw new RuntimeException(e);
        }
    }



}
