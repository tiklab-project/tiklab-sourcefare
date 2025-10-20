package io.tiklab.sourcefare.scan.common;

import io.tiklab.core.exception.ApplicationException;
import io.tiklab.eam.common.context.LoginContext;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.sourcefare.scan.service.*;
import io.tiklab.sourcefare.scanner.common.ScanCommon;
import io.tiklab.sourcefare.scanner.model.*;
import io.tiklab.sourcefare.scanner.model.ScanResult;
import io.tiklab.sourcefare.scanner.model.ScanResultFile;
import io.tiklab.user.user.model.User;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.BeanUtils;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.sql.Timestamp;
import java.util.*;
import java.util.stream.Collectors;

public class CodeScanCommon {





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
     *  @param projectId 扫描的项目的id
     */
    public static ScanRecord initScanRecord(ScanRecordService scanRecordService, String projectId,String way ) {

        ScanRecord scanRecord = new ScanRecord();
        scanRecord.setProjectId(projectId);
        User user = new User();
        user.setId(LoginContext.getLoginId());

        scanRecord.setScanUser(user);
        scanRecord.setCreateTime(new Timestamp(System.currentTimeMillis()));
        scanRecord.setScanResult("run");
        scanRecord.setScanWay(way);
        String id = scanRecordService.createScanRecord(scanRecord);
        scanRecord.setId(id);
        return scanRecord;
    }










    /**
     * 创建扫描实例
     * @param scanSchemeRuleList 自定义的扫描方案的规则
     * @param scanRecord scanRecord
     * @param scanResult 扫描结果
     */
    public static void createRecordInstance(List<ScanSchemeRule> scanSchemeRuleList,
                                             RecordInstanceService recordInstanceService,
                                             ScanRecord scanRecord,
                                             ScanResult scanResult) {
        List<ScanResultFile> scanResultFiles = scanResult.getScanResultFiles();
        if (CollectionUtils.isNotEmpty(scanSchemeRuleList)&&CollectionUtils.isNotEmpty(scanResultFiles)){


            int severityNum=0;
            int errorNum=0;
            int noticeNum=0;
            int suggestNum=0;
            List<RecordInstance> arrayList = new ArrayList<>();
            for (ScanResultFile scanResultFile:scanResultFiles) {
                List<ScanSchemeRule> schemeRuleList = scanSchemeRuleList.stream()
                        .filter(a -> (scanResultFile.getErrorRuleName()).equals(a.getScanRule().getRuleName()))
                        .collect(Collectors.toList());
                if (CollectionUtils.isNotEmpty(schemeRuleList)){
                    ScanSchemeRule scanSchemeRule = schemeRuleList.get(0);

                    switch (scanSchemeRule.getProblemLevel()){
                        case 1:
                            severityNum+=1;
                            break;
                        case 2:
                            errorNum+=1;
                            break;
                        case 3:
                            noticeNum+=1;
                            break;
                        case 4:
                            suggestNum+=1;
                            break;
                    }
                    RecordInstance instance = new RecordInstance();
                    instance.setId(SourceFareUtil.getRandom(12));
                    BeanUtils.copyProperties(scanResultFile,instance);

                    instance.setProblemLevel(scanSchemeRule.getProblemLevel());
                    instance.setProjectId(scanRecord.getProjectId());
                    instance.setScanRecordId(scanRecord.getId());
                    instance.setRuleName(scanResultFile.getErrorRuleName());
                    instance.setRuleType(scanSchemeRule.getScanRule().getRuleType());

                    //获取code存储的位置
                    String projectId = scanRecord.getProjectId();

                    String filePath = scanResultFile.getFilePath();
                    String s = StringUtils.substringAfter(filePath, "/");
                    instance.setFileName(scanResult.getCodeName()+"/"+s);
                    instance.setFilePath(filePath);


                   /* if (("go").equals(scanResult.getLanguage())){
                        if (("server").equals(scanResult.getScanWay())){
                           instance.setFilePath(filePath);
                           Integer index = filePath.indexOf(scanResult.getScanObjectId()) + scanResult.getScanObjectId().length();
                           String relativePath = filePath.substring(index);
                            instance.setFileName(scanResult.getCodeName()+relativePath);
                        }else {
                            String fileName = SourceFareUtil.SystemTypeAddress(scanResult.getCodeName() + "/" + filePath);
                            String address = SourceFareUtil.SystemTypeAddress(filePath);
                            instance.setFileName(fileName);
                            instance.setFilePath(address);
                        }
                    } else if (("c++").equals(scanResult.getLanguage())||("c#").equals(scanResult.getLanguage())){
                        instance.setFileName(scanResult.getCodeName()+"/"+filePath);
                        instance.setFilePath(filePath);
                    }else {

                        instance.setFileName(scanResult.getCodeName()+"/"+filePath);
                        instance.setFilePath(filePath);
                     *//*   instance.setFileName(scanResult.getCodeName()+"/"+relativePath);
                        instance.setFilePath(relativePath);*//*
                    }*/
                    instance.setCreateTime(new Timestamp(System.currentTimeMillis()));
                    arrayList.add(instance);
                   // recordInstanceService.createScanRecordInstance(instance);
                }
        }

            recordInstanceService.createScanRecordInstance(arrayList);

            //根据自定义的扫描方案添加错误数量
            scanRecord.setSeverityTrouble(severityNum);
            scanRecord.setErrorTrouble(errorNum);
            scanRecord.setNoticeTrouble(noticeNum);
            scanRecord.setSuggestTrouble(suggestNum);
            scanRecord.setAllTrouble(severityNum+noticeNum+suggestNum+errorNum);
      }
    }

    /**
     * 创建项目覆盖率
     * @param coverService coverService
     * @param scanResult 扫描结果
     */
    public static void createProjectCover(ProjectCoverService coverService,ScanResult scanResult){
        List<Cover> coverList = scanResult.getProjectCoverList();
        if (CollectionUtils.isNotEmpty(coverList)){
            if (("go").equals(scanResult.getLanguage())){

            }
            for (Cover cover:coverList){
                ProjectCover projectCover = new ProjectCover();
                BeanUtils.copyProperties(cover, projectCover);

                projectCover.setProjectId(scanResult.getScanObjectId());
                projectCover.setScanRecordId(scanResult.getScanRecordId());
                coverService.createProjectCover(projectCover);
            }
        }
    }

    /**
     * 创建重复数据
     * @param duplicatedService duplicatedService
     * @param scanResult 扫描结果
     */
    public static void createProjectDuplicated(RecordDuplicatedService duplicatedService, ScanResult scanResult){
        List<Duplicated> duplicatedList = scanResult.getDuplicatedList();
        List<RecordDuplicated> arrayList = new ArrayList<>();
        if (CollectionUtils.isNotEmpty(duplicatedList)){
            for (Duplicated duplicated:duplicatedList){
                RecordDuplicated recordDuplicated = new RecordDuplicated();
                BeanUtils.copyProperties(duplicated, recordDuplicated);

                recordDuplicated.setId(SourceFareUtil.getRandom(12));
                recordDuplicated.setProjectId(scanResult.getScanObjectId());
                recordDuplicated.setRecordId(scanResult.getScanRecordId());
                recordDuplicated.setCreateTime(new Timestamp(System.currentTimeMillis()));
                //duplicatedService.createRecordDuplicated(recordDuplicated);
                arrayList.add(recordDuplicated);
            }
            duplicatedService.createRecordDuplicated(arrayList);
        }
    }

    /**
     * 创建复杂度数据
     * @param complexityService complexityService
     * @param scanResult 扫描结果
     */
    public static void createProjectComplexity(RecordComplexityService complexityService, ScanResult scanResult){
        List<Complexity> complexityList = scanResult.getComplexityList();
        if (CollectionUtils.isNotEmpty(complexityList)){
            List<RecordComplexity> arrayList = new ArrayList<>();
            for (Complexity complexity:complexityList){
                RecordComplexity recordComplexity = new RecordComplexity();
                BeanUtils.copyProperties(complexity, recordComplexity);

                recordComplexity.setId(SourceFareUtil.getRandom(12));
                recordComplexity.setProjectId(scanResult.getScanObjectId());
                recordComplexity.setRecordId(scanResult.getScanRecordId());
                recordComplexity.setCreateTime(new Timestamp(System.currentTimeMillis()));
                //complexityService.createRecordComplexity(recordComplexity);
                arrayList.add(recordComplexity);
            }
            complexityService.createRecordComplexity(arrayList);
        }
    }


    /**
     *  创建问题统计
     *  @param scanResult scanResult
     */

    public static void createIssueStatistic(IssueStatisticService issueStatisticService,
                                            List<ScanSchemeRule> scanSchemeRules,
                                            ScanResult scanResult){

        List<ScanResultFile> scanResultFiles = scanResult.getScanResultFiles();
        if (CollectionUtils.isNotEmpty(scanSchemeRules)&&CollectionUtils.isNotEmpty(scanResultFiles)){

            //查询项目的问题统计数据
            IssueStatisticQuery statisticQuery = new IssueStatisticQuery();
            statisticQuery.setProjectId(scanResult.getScanObjectId());
            List<IssueStatistic> issueStatisticList = issueStatisticService.findIssueStatisticList(statisticQuery);


            Map<String, List<ScanResultFile>> listMap = scanResultFiles.stream().collect(Collectors.groupingBy(ScanResultFile::getFilePath));
            Set<String> filePaths = listMap.keySet();
            List<IssueStatistic> arrayList = new ArrayList<>();
            for (String key:filePaths){
                List<ScanResultFile> scanResultFileList = listMap.get(key);
                //通过条件过滤
                List<IssueStatistic> statisticList = issueStatisticList.stream().filter(a -> key.equals(a.getFilePath()))
                        .collect(Collectors.toList());

                if (CollectionUtils.isNotEmpty(statisticList)){
                    issueStatisticService.deleteIssueStatisticByCondition("filePath",key);
                }
                for (ScanResultFile scanResultFile:scanResultFileList){
                    List<ScanSchemeRule> schemeRuleList = scanSchemeRules.stream()
                            .filter(a -> (scanResultFile.getErrorRuleName()).equals(a.getScanRule().getRuleName()))
                            .collect(Collectors.toList());

                    if (CollectionUtils.isNotEmpty(schemeRuleList)){
                        ScanSchemeRule scanSchemeRule = schemeRuleList.get(0);

                        String filePath = scanResultFile.getFilePath();

                        IssueStatistic issueStatistic = new IssueStatistic();
                        issueStatistic.setId(SourceFareUtil.getRandom(12));
                        issueStatistic.setProjectId(scanResult.getScanObjectId());
                        issueStatistic.setFilePath(filePath);
                        issueStatistic.setProblemDesc(scanResultFile.getProblemDesc());
                        issueStatistic.setProblemLine(scanResultFile.getProblemLine());
                        issueStatistic.setProblemLevel(scanResultFile.getProblemLevel());
                        issueStatistic.setRuleName(scanResultFile.getErrorRuleName());
                        issueStatistic.setProblemLine(scanResultFile.getProblemLine());
                        issueStatistic.setProblemDesc(scanResultFile.getProblemDesc());
                        issueStatistic.setRuleType(scanSchemeRule.getScanRule().getRuleType());
                        issueStatistic.setProblemState(0);
                        issueStatistic.setCreateTime(new Timestamp(System.currentTimeMillis()));
                        arrayList.add(issueStatistic);
                        //issueStatisticService.createIssueStatistic(issueStatistic);
                    }
                }
            }
            issueStatisticService.createIssueStatistic(arrayList);
        /*    // 过滤出 issueStatisticList 中在 scanResultFiles 中不存在的元素 (代表已经解决)
            List<IssueStatistic> statisticList = issueStatisticList.stream()
                    .filter(issue -> scanResultFiles.stream().noneMatch(scanResultFile ->
                            scanResultFile.getFilePath().equals(issue.getFilePath()) &&
                                    scanResultFile.getErrorRuleName().equals(issue.getRuleName()) &&
                                    scanResultFile.getProblemLine().equals(issue.getProblemLine())))
                    .collect(Collectors.toList());

            if (CollectionUtils.isNotEmpty(statisticList)){
                for (IssueStatistic issueStatistic:statisticList){
                    issueStatistic.setProblemState(1);
                    issueStatisticService.updateIssueStatistic(issueStatistic);
                }
            }*/
        }
    }
}

