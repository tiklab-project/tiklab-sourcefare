package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.scan.model.*;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

@Service
public class StatisticsServiceImpl implements StatisticsService{

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    RecordInstanceService recordInstanceService;

    @Autowired
    RecordDuplicatedService recordDuplicatedService;

    @Autowired
    RecordComplexityService complexityService;

    @Autowired
    ProjectCoverService coverService;


    @Override
    public Object issueStat(StatisticsQuery statisticsQuery) {
        Map<String, List> resultMap = new HashMap<>();
        //查询扫描记录
        List<ScanRecord> scanRecords = findScanRecordList(statisticsQuery);

        List<String> timeList = new ArrayList<>();
        if (CollectionUtils.isNotEmpty(scanRecords)){

            //查询问题等级
            if (("issueLevel").equals(statisticsQuery.getFindType())){
                List<Integer> severityList = new ArrayList<>();
                List<Integer> noticeList = new ArrayList<>();
                List<Integer> suggestList = new ArrayList<>();
                for (ScanRecord scanRecord:scanRecords){
                    LocalDateTime ldt = scanRecord.getCreateTime().toLocalDateTime();
                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                    String format = ldt.format(formatter);
                    timeList.add(format);

                    severityList.add(scanRecord.getSeverityTrouble());
                    noticeList.add(scanRecord.getNoticeTrouble());
                    suggestList.add(scanRecord.getSuggestTrouble());
                }
                resultMap.put("time",timeList);
                resultMap.put("severity",severityList);
                resultMap.put("notice",noticeList);
                resultMap.put("suggest",suggestList);
            }

            //查询问题类型
            if (("issueType").equals(statisticsQuery.getFindType())){
                List<Integer> securityList = new ArrayList<>();
                List<Integer> functionList = new ArrayList<>();
                List<Integer> normList = new ArrayList<>();

                List<RecordInstance> instanceList = recordInstanceService.findScanInstanceByCon(statisticsQuery.getProjectId(),"projectId");
                Map<String, List<RecordInstance>> stringListMap = instanceList.stream().collect(Collectors.groupingBy(RecordInstance::getScanRecordId));
                for (ScanRecord scanRecord:scanRecords){
                    List<RecordInstance> recordInstances = stringListMap.get(scanRecord.getId());

                    List<RecordInstance> security=null;
                    List<RecordInstance> function=null;
                    List<RecordInstance> norm=null;
                    if (CollectionUtils.isNotEmpty(recordInstances)){
                        security = recordInstances.stream().filter(a -> ("security").equals(a.getRuleType())).collect(Collectors.toList());
                        function = recordInstances.stream().filter(a -> ("function").equals(a.getRuleType())).collect(Collectors.toList());
                        norm = recordInstances.stream().filter(a -> ("norm").equals(a.getRuleType())).collect(Collectors.toList());
                    }

                    int securityNum = CollectionUtils.isNotEmpty(security) ? security.size() : 0;
                    int functionNum = CollectionUtils.isNotEmpty(function) ? function.size() : 0;
                    int normNum = CollectionUtils.isNotEmpty(norm) ? norm.size() : 0;
                    securityList.add(securityNum);
                    functionList.add(functionNum);
                    normList.add(normNum);

                    LocalDateTime ldt = scanRecord.getCreateTime().toLocalDateTime();
                    DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                    String format = ldt.format(formatter);
                    timeList.add(format);
                }
                resultMap.put("time",timeList);
                resultMap.put("security",securityList);
                resultMap.put("function",functionList);
                resultMap.put("norm",normList);
            }
        }
        return resultMap;
    }

    @Override
    public Object duplicatedStat(StatisticsQuery statisticsQuery) {
        Map<String, List> resultMap = new HashMap<>();

        //查询扫描记录
        List<ScanRecord> scanRecords = findScanRecordList(statisticsQuery);

        if (CollectionUtils.isNotEmpty(scanRecords)){
            List<RecordDuplicated> duplicatedList = recordDuplicatedService.findRecordDuplicatedByCon(statisticsQuery.getProjectId(),"projectId");

            Map<String, List<RecordDuplicated>> listMap = duplicatedList.stream().collect(Collectors.groupingBy(RecordDuplicated::getRecordId));

            List<Integer> lineList = new ArrayList<>();
            List<Integer> fileList = new ArrayList<>();
            List<String> timeList = new ArrayList<>();
            for (ScanRecord scanRecord:scanRecords){
                List<RecordDuplicated> recordDuplicatedList = listMap.get(scanRecord.getId());
                //执行时间
                LocalDateTime ldt = scanRecord.getCreateTime().toLocalDateTime();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                String format = ldt.format(formatter);
                timeList.add(format);

                if (CollectionUtils.isNotEmpty(recordDuplicatedList)){
                    int lineNum = recordDuplicatedList.stream().mapToInt(RecordDuplicated::getLines).sum();
                    int fileSize = CollectionUtils.isNotEmpty(recordDuplicatedList) ? recordDuplicatedList.size() : 0;

                    lineList.add(lineNum);
                    fileList.add(fileSize);
                }else {
                    lineList.add(0);
                    fileList.add(0);
                }
            }

            resultMap.put("time",timeList);
            resultMap.put("lines",lineList);
            resultMap.put("files",fileList);
        }
        return resultMap;
    }

    @Override
    public Object complexityStat(StatisticsQuery statisticsQuery) {
        Map<String, List> resultMap = new HashMap<>();

        //查询扫描记录
        List<ScanRecord> scanRecords = findScanRecordList(statisticsQuery);

        if (CollectionUtils.isNotEmpty(scanRecords)){
            List<RecordComplexity> complexityList = complexityService.findRecordComplexityByCon(statisticsQuery.getProjectId(),"projectId");

            List<Integer> sizeList = new ArrayList<>();
            List<String> timeList = new ArrayList<>();
            for (ScanRecord scanRecord:scanRecords){
                List<RecordComplexity> complexities = complexityList.stream().filter(a -> scanRecord.getId().equals(a.getRecordId())).collect(Collectors.toList());

                LocalDateTime ldt = scanRecord.getCreateTime().toLocalDateTime();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                String format = ldt.format(formatter);
                timeList.add(format);
                if (CollectionUtils.isNotEmpty(complexities)){
                    //直接计算出类型为class的复杂度
                    int sum = complexities.stream().filter(a -> ("class").equals(a.getType()))
                            .mapToInt(RecordComplexity::getComplexityNum).sum();

                    //先找出所有类型class的集合 （如果有class类型的复杂度数据，就不用计算class里面方法的复杂度）
                    Set<String> complexityPathList = complexities.stream().filter(a -> ("class").equals(a.getType()))
                            .map(RecordComplexity::getPath)
                            .collect(Collectors.toSet());

                    //过滤出方法的复杂度
                    int methodSum = complexities.stream()
                            .filter(e -> "method".equals(e.getType()))
                            .filter(e -> !complexityPathList.contains(e.getPath()))
                            .mapToInt(RecordComplexity::getComplexityNum)
                            .sum();

                    int complexityNum = sum + methodSum;
                    sizeList.add(complexityNum);
                }else {
                    sizeList.add(0);
                }
                resultMap.put("time",timeList);
                resultMap.put("size",sizeList);
            }
        }
        return resultMap;
    }

    @Override
    public Object coverStat(StatisticsQuery statisticsQuery) {
        Map<String, List> resultMap = new HashMap<>();

        //查询扫描记录
        List<ScanRecord> scanRecords = findScanRecordList(statisticsQuery);

        if (CollectionUtils.isNotEmpty(scanRecords)){

            List<String> timeList = new ArrayList<>();
            List<Integer> instructionList = new ArrayList<>();
            List<Integer> branchList = new ArrayList<>();
            List<Integer> complexityList = new ArrayList<>();
            List<Integer> lineList = new ArrayList<>();
            List<Integer> methodList = new ArrayList<>();
            List<Integer> classList = new ArrayList<>();

            List<ProjectCover> projectCoverList = coverService.findProjectCoverList(new ProjectCoverQuery()
                    .setProjectId(statisticsQuery.getProjectId())
                    .setType("project"));
            for (ScanRecord scanRecord:scanRecords){

                //执行时间
                LocalDateTime ldt = scanRecord.getCreateTime().toLocalDateTime();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm");
                String format = ldt.format(formatter);
                timeList.add(format);

                List<ProjectCover> projectCovers = projectCoverList.stream().filter(a -> scanRecord.getId().equals(a.getScanRecordId())).collect(Collectors.toList());
                if (CollectionUtils.isNotEmpty(projectCovers)){
                    ProjectCover projectCover = projectCovers.get(0);

                    //指令覆盖
                    int instructions = projectCover.getInstructions() - projectCover.getInstructionsMissed();
                    instructionList.add(instructions);


                    //分支覆盖
                    int branch = projectCover.getBranch() - projectCover.getBranchMissed();
                    branchList.add(branch);

                    //复杂度覆盖
                    int complexity = projectCover.getComplexity() - projectCover.getComplexityMissed();
                    complexityList.add(complexity);

                    //行覆盖
                    int line = projectCover.getLine() - projectCover.getLineMissed();
                    lineList.add(line);

                    //方法覆盖
                    int method = projectCover.getMethods() - projectCover.getMethodsMissed();
                   methodList.add(method);

                    //类覆盖
                    int classNum = projectCover.getClasses() - projectCover.getClassesMissed();
                    classList.add(classNum);
                }
            }
            resultMap.put("instructions",instructionList);
            resultMap.put("branch",branchList);
            resultMap.put("complexity",complexityList);
            resultMap.put("line",lineList);
            resultMap.put("method",methodList);
            resultMap.put("class",classList);
            resultMap.put("time",timeList);
        }

        return resultMap;
    }


    public List<ScanRecord> findScanRecordList(StatisticsQuery statisticsQuery){
        List<ScanRecord> scanRecords=null;

        //查询扫描记录
        List<ScanRecord> scanRecordList = scanRecordService.findScanRecordListByProjectId(statisticsQuery.getProjectId());
        scanRecordList = scanRecordList.stream().sorted(Comparator.comparing(ScanRecord::getScanTime)).collect(Collectors.toList());

        if (CollectionUtils.isNotEmpty(scanRecordList)) {

            //获取查询数量的扫描记录
            int size = scanRecordList.size();
            if (size <= statisticsQuery.getFindNum()) {
                scanRecords = scanRecordList.subList(0, size);
            } else {
                scanRecords = scanRecordList.subList(0, statisticsQuery.getFindNum());
            }
        }
        return scanRecords;
    }

}
