package io.tiklab.sourcefare.scan.common;

import io.tiklab.core.exception.ApplicationException;
import io.tiklab.eam.common.context.LoginContext;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.scanner.common.ScanCommon;
import io.tiklab.sourcefare.scanner.model.ScanResult;
import io.tiklab.sourcefare.scanner.model.ScanResultFile;
import io.tiklab.sourcefare.scan.model.ScanPlay;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.model.ScanRecordInstance;
import io.tiklab.sourcefare.scan.model.ScanSchemeRule;
import io.tiklab.sourcefare.scan.service.ScanRecordInstanceService;
import io.tiklab.sourcefare.scan.service.ScanRecordService;
import io.tiklab.user.user.model.User;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.BeanUtils;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.sql.Date;
import java.sql.Timestamp;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class CodeScanCommon {
    //执行扫描执行开始时间
    public static Map<String , Date> scanExecStarTime = new HashMap<>();
    // 添加扫描的开始时间
    public static void putExecStarTime (String key, Date value) {scanExecStarTime.put(key, value);}

    // 获取扫描开始时间
    public static Date getExecStarTime (String key) {
        return scanExecStarTime.get(key);
    }


    public static String executeCommand(String command) {
        try {
            Process process = Runtime.getRuntime().exec(command);
            BufferedReader reader = new BufferedReader(
                    new InputStreamReader(process.getInputStream()));

            StringBuilder output = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                output.append(line);
            }
            int exitCode = process.waitFor();
            if (exitCode != 0) {
                throw new ApplicationException("命令执行失败: " + command);
            }
            return output.toString();
        }catch (Exception e){
            throw new ApplicationException(e);
        }
    }

    /**
     *  执行日志
     *  @param process:process
     * @param  playId 扫描计划的id
     */
    public  static boolean  readExecResult(Process process,String  playId) throws IOException {
        boolean state = true;

        // 获取命令行输出
        InputStream inputStream = process.getInputStream();
        BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
        String line;

        // mvn 编译日志,读取执行信息
        while ((line = reader.readLine()) != null) {
            ScanCommon.joinScanLog(playId,line);
            //校验日志信息
            String valid =validStatus(line,mavenBuildError());
            if (StringUtils.isNotEmpty(valid)){
                state = false;
            }

        }

        //spotBugs日志,读取err执行信息
        InputStream errorStream = process.getErrorStream();
        BufferedReader errorReader = new BufferedReader(new InputStreamReader(errorStream));
        String errorLine;
        while ((errorLine = errorReader.readLine()) != null) {
            ScanCommon.joinScanLog(playId,errorLine);
            //校验日志信息
            String valid =validStatus(errorLine,mavenBuildError());
            if (StringUtils.isNotEmpty(valid)){
                state = false;
            }
        }
        inputStream.close();
        errorStream.close();
        return state;
    }


    /**
     * 效验日志状态
     * @param s 日志
     * @param errors 错误状态
     * @return null 正确  other：错误
     */
    public static String validStatus(String s, Map<String,String> errors){
        for (Map.Entry<String, String> errorString : errors.entrySet()) {
            String key = errorString.getKey();
            if (!s.contains(key)){
                continue;
            }
            return errorString.getValue();
        }
        return null;
    }

    /*
     * maven编译错误信息
     * */
    public static Map<String,String> mavenBuildError(){
        Map<String,String> map = new HashMap<>();
        map.put("svn: E170000:","");
        map.put("invalid option;","");
        map.put("BUILD FAILURE","构建失败！");
        return map;
    }

    /**
     *  初始化扫描结果数据
     *  @param scanPlay 扫描计划
     */
    public static ScanRecord initScanRecord(ScanRecordService scanRecordService, ScanPlay scanPlay ) {

        ScanRecord scanRecord = new ScanRecord();
        scanRecord.setProjectId(scanPlay.getProjectId());
        scanRecord.setScanPlay(scanPlay);
        User user = new User();
        user.setId(LoginContext.getLoginId());

        scanRecord.setScanUser(user);
        scanRecord.setCreateTime(new Timestamp(System.currentTimeMillis()));
        scanRecord.setScanResult("run");
        scanRecord.setScanWay("hand");
        String id = scanRecordService.createScanRecord(scanRecord);
        scanRecord.setId(id);
        return scanRecord;
        //扫描对象
  /*      io.tiklab.gitpuk.commit.model.Commit commit = new Commit();
        commit.setRpyId(scanPlay.getRepository().getRpyId());
        commit.setRefCode(scanPlay.getBranch());
        commit.setRefCodeType("branch");
        CommitMessage branchCommit = commitServer.findLatelyBranchCommit(commit);
        scanRecord.setScanObject(branchCommit.getCommitId());*/

    }


    /**
     *  更新扫描失败状态
     *  @param scanRecord scanRecord
     */
    public static void updateFailScanRecord(ScanRecordService scanRecordService,
                                                  ScanRecord scanRecord) {

        String scanPlayId = scanRecord.getScanPlay().getId();
        scanRecord.setScanResult("fail");
        String time = SourceFareUtil.time(ScanCommon.getExecStarTime(scanPlayId),"scan");
        scanRecord.setScanTime(time);
        scanRecord.setExecLog(ScanCommon.getScanLog(scanPlayId));
        scanRecordService.updateScanRecord(scanRecord);
    }

    /**
     *  更新扫描成功状态
     *  @param scanRecord scanRecord
     * @param scanResult 扫描结果
     */
    public static void updateScanRecord(ScanRecordService scanRecordService,
                                               ScanRecord scanRecord,
                                               ScanResult scanResult) {
        String scanPlayId = scanRecord.getScanPlay().getId();

        String time = SourceFareUtil.time(ScanCommon.getExecStarTime(scanPlayId),"scan");
        scanRecord.setScanTime(time);
        scanRecord.setScanResult(scanResult.getResult());
        scanRecord.setExecLog(ScanCommon.getScanLog(scanPlayId));
        scanRecordService.updateScanRecord(scanRecord);
    }

    /**
     *  创建扫描实例
     * @param scanSchemeRuleList 自定义的扫描方案的规则
     *  @param scanRecord scanRecord
     * @param scanResult 扫描结果
     */
    public static void createRecordInstance(List<ScanSchemeRule> scanSchemeRuleList,
                                            ScanRecordInstanceService recordInstanceService,
                                             ScanRecord scanRecord,
                                             ScanResult scanResult) {
        List<ScanResultFile> scanResultFiles = scanResult.getScanResultFiles();

        if (CollectionUtils.isNotEmpty(scanSchemeRuleList)&&CollectionUtils.isNotEmpty(scanResultFiles)){
            int severityNum=0;
            int noticeNum=0;
            int suggestNum=0;
            for (ScanResultFile scanResultFile:scanResultFiles) {
                List<ScanSchemeRule> schemeRuleList = scanSchemeRuleList.stream().filter(a -> (scanResultFile.getErrorRuleName()).equals(a.getScanRule().getRuleName())).toList();
                if (CollectionUtils.isNotEmpty(schemeRuleList)){
                    ScanSchemeRule scanSchemeRule = schemeRuleList.get(0);

                    switch (scanSchemeRule.getProblemLevel()){
                        case 1:
                            severityNum+=1;
                            break;
                        case 2:
                            noticeNum+=1;
                            break;
                        case 3:
                            suggestNum+=1;
                            break;
                    }
                    ScanRecordInstance instance = new ScanRecordInstance();
                    BeanUtils.copyProperties(scanResultFile,instance);

                    instance.setProblemLevel(scanSchemeRule.getProblemLevel());
                    instance.setScanPlayId(scanRecord.getScanPlay().getId());
                    instance.setScanRecordId(scanRecord.getId());
                    instance.setRuleName(scanResultFile.getErrorRuleName());
                    recordInstanceService.createScanRecordInstance(instance);

                    //根据自定义的扫描方案添加错误数量
                    scanRecord.setSeverityTrouble(severityNum);
                    scanRecord.setNoticeTrouble(noticeNum);
                    scanRecord.setSuggestTrouble(suggestNum);
                    scanRecord.setAllTrouble(severityNum+noticeNum+suggestNum);
                }
        }
      }
    }
}
