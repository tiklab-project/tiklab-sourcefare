package io.tiklab.sourcefare.project.service;

import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.project.model.ProjectRecordStat;
import io.tiklab.sourcefare.project.model.ProjectStat;
import io.tiklab.sourcefare.project.model.ScanPlayStat;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.model.ScanRecordQuery;
import io.tiklab.sourcefare.scan.service.ScanRecordService;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.stream.Collectors;

@Service
public class ProjectStatServiceImpl implements ProjectStatService{

    @Autowired
    ProjectService projectService;


    @Autowired
    ScanRecordService scanRecordService;


    @Override
    public ScanPlayStat scanPlayStat(String projectId) {
        ScanPlayStat projectStat = new ScanPlayStat();

        List<ScanRecord> scanRecordList = scanRecordService.findScanRecordList(new ScanRecordQuery().setProjectId(projectId));
        if (CollectionUtils.isNotEmpty(scanRecordList)){
          /*  List<String> scanPlayNameList = new ArrayList<>();
            List<Integer> scanPlayExecList = new ArrayList<>();

            Map<String, List<ScanRecord>> playListMap =scanRecordList.stream()
                    .filter(employee -> StringUtils.isNotBlank(employee.getScanPlay().getPlayName())) // 排除 name 为空的员工
                    .collect(Collectors.groupingBy(a -> a.getScanPlay().getId()));

            // 根据每个组的大小排序
            List<Map.Entry<String, List<ScanRecord>>> collect = playListMap.entrySet().stream()
                    .sorted((entry1, entry2) -> Integer.compare(entry2.getValue().size(), entry1.getValue().size())) // 按大小降序排序
                    .limit(4) // 取前两个
                    .collect(Collectors.toList());

            collect.forEach(entry -> {
                List<ScanRecord> scanRecords = playListMap.get(entry.getKey());

                scanPlayNameList.add(scanRecords.get(0).getScanPlay().getPlayName());
                scanPlayExecList.add(entry.getValue().size());
            });
            projectStat.setScanPlayExec(scanPlayExecList);
            projectStat.setScanPlayName(scanPlayNameList);*/


            //计算时间
            List<String> dataList = new ArrayList<>();
            List<Integer> dataNumList = new ArrayList<>();
            LocalDate today = LocalDate.now();
            DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
            for (int i = 1; i <= 7; i++) {
                LocalDate date = today.minusDays(7-i);
                dataList.add(date.format(formatter));
                LocalDate dateFromString = LocalDate.parse(date.format(formatter));

                List<ScanRecord> scanRecords = scanRecordList.stream().filter(a -> a.getCreateTime().toLocalDateTime().toLocalDate().isEqual(dateFromString))
                        .collect(Collectors.toList());

                int num = CollectionUtils.isNotEmpty(scanRecords) ? scanRecords.size() : 0;
                dataNumList.add(num);
            }

            projectStat.setTimeList(dataList);
            projectStat.setTimeNumList(dataNumList);

        }
        return projectStat;
    }

    @Override
    public ProjectStat findProjectStat() {
        ProjectStat projectStat = new ProjectStat();

        List<Project> allProject = projectService.findAllProject();
        if (CollectionUtils.isNotEmpty(allProject)){

            List<ProjectRecordStat> arrayList = new ArrayList<>();
            for (Project project:allProject){
                ProjectRecordStat projectRecordStat = new ProjectRecordStat();
                List<ScanRecord> recordList = scanRecordService.findScanRecordListByProjectId(project.getId());
                int num = CollectionUtils.isNotEmpty(recordList) ? recordList.size() : 0;
                projectRecordStat.setProjectName(project.getName());
                projectRecordStat.setRecordNum(num);

                arrayList.add(projectRecordStat);
            }

            //统计项目扫描次数
            List<ProjectRecordStat> recordStats = arrayList.stream().sorted(Comparator.comparing(ProjectRecordStat::getRecordNum).reversed())
                    .limit(4)
                    .collect(Collectors.toList());

            List<String> projectNameList = new ArrayList<>();
            List<Integer> ExecList = new ArrayList<>();
            recordStats.forEach(entry -> {
                projectNameList.add(entry.getProjectName());
                ExecList.add(entry.getRecordNum());
            });
            projectStat.setProjectNameList(projectNameList);
            projectStat.setExecList(ExecList);


            //计算一周每天扫描次数
            List<ScanRecord> allScanRecord = scanRecordService.findAllScanRecord();
            if (CollectionUtils.isNotEmpty(allScanRecord)){
                List<String> dataList = new ArrayList<>();
                List<Integer> dataNumList = new ArrayList<>();
                LocalDate today = LocalDate.now();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
                for (int i = 1; i <= 7; i++) {
                    LocalDate date = today.minusDays(7-i);
                    dataList.add(date.format(formatter));
                    LocalDate dateFromString = LocalDate.parse(date.format(formatter));

                    List<ScanRecord> scanRecords = allScanRecord.stream().filter(a -> a.getCreateTime().toLocalDateTime().toLocalDate().isEqual(dateFromString))
                            .collect(Collectors.toList());

                    int num1 = CollectionUtils.isNotEmpty(scanRecords) ? scanRecords.size() : 0;
                    dataNumList.add(num1);
                }
                projectStat.setTimeList(dataList);
                projectStat.setTimeNumList(dataNumList);
            }

        }
        return projectStat;
    }
}
