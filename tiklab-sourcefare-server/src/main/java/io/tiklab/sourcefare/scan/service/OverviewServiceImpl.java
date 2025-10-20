package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.entity.ProjectCoverEntity;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.toolkit.beans.BeanMapper;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.ObjectUtils;

import java.io.FileReader;
import java.io.IOException;
import java.io.LineNumberReader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Timestamp;
import java.text.DecimalFormat;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

@Service
public class OverviewServiceImpl implements OverviewService{

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    RecordInstanceService scanRecordInstanceService;

    @Autowired
    ProjectCoverService projectCoverService;

    @Autowired
    PathSetService pathSetService;

    @Autowired
    RecordDuplicatedService duplicatedService;

    @Autowired
    RecordComplexityService complexityService;

    @Override
    public Object findProjectCoverStat(String recordId) {
        ProjectCoverQuery projectCoverQuery = new ProjectCoverQuery();
        projectCoverQuery.setScanRecordId(recordId);
        projectCoverQuery.setType("project");
        List<ProjectCover> projectCoverList = projectCoverService.findProjectCoverList(projectCoverQuery);

        if (CollectionUtils.isNotEmpty(projectCoverList)){
            ProjectCover projectCover = projectCoverList.get(0);
            Map<String, Object> resultMap = new HashMap<>();
            resultMap.put("instructionsMissed",projectCover.getInstructionsMissed());
            resultMap.put("branchMissed",projectCover.getBranchMissed());
            resultMap.put("complexityMissed",projectCover.getComplexityMissed());
            resultMap.put("lineMissed",projectCover.getLineMissed());
            resultMap.put("methodsMissed",projectCover.getMethodsMissed());
            resultMap.put("classesMissed",projectCover.getClassesMissed());

            resultMap.put("instructionsCover",projectCover.getInstructions()-projectCover.getInstructionsMissed());
            resultMap.put("branchCover",projectCover.getBranch()-projectCover.getBranchMissed());
            resultMap.put("complexityCover",projectCover.getComplexity()-projectCover.getComplexityMissed());
            resultMap.put("lineCover",projectCover.getLine()-projectCover.getLineMissed());
            resultMap.put("methodsCover",projectCover.getMethods()-projectCover.getMethodsMissed());
            resultMap.put("classesCover",projectCover.getClasses()-projectCover.getClassesMissed());
            return resultMap;
        }
        return null;
    }


    @Override
    public ScanRecord findScanRecordStat(String id) {
        ScanRecord scanRecord =scanRecordService.findOne(id);
        List<RecordInstance> scanRecordInstanceList = scanRecordInstanceService.findScanInstanceByCon(id,"recordId");
        if (CollectionUtils.isNotEmpty(scanRecordInstanceList)){
            List<Object> arrayList = new ArrayList<>();
            Map<String, List<RecordInstance>> listMap = scanRecordInstanceList.stream().collect(Collectors.groupingBy(RecordInstance::getRuleType));

            Set<String> types = listMap.keySet();
            for (String type:types){
                int size = listMap.get(type).size();
                Map<String, Object> hashMap = new HashMap<>();
                if ("function".equals(type)){
                    hashMap.put("name","功能: "+size);
                }
                if ("norm".equals(type)){
                    hashMap.put("name","规范: "+size);
                }
                if ("security".equals(type)){
                    hashMap.put("name","安全: "+size);
                }
                hashMap.put("value",size);
                arrayList.add(hashMap);
            }
            scanRecord.setTypeList(arrayList);
        }
        return scanRecord;
    }

    @Override
    public Object findMetricStat(String recordId, String projectId) {
        //代码文件的详细位置
        String folderPath = pathSetService.codePath()+"/"+projectId;

        //重复度数据
        List<RecordDuplicated> duplicatedList = duplicatedService.findRecordDuplicatedByCon(recordId,"recordId");
        //复杂度数据
        List<RecordComplexity> complexityList = complexityService.findRecordComplexityByCon(recordId,"recordId");


        Map<String, Object> resultMap = new HashMap<>();
        try {
            //获取所有文件
            List<Path> pathList = Files.walk(Paths.get(folderPath))
                    .filter(Files::isRegularFile)
                    .collect(Collectors.toList());

            int lineNum=0;
        /*    for (Path path:pathList){
                Path fileName = path.getFileName();
                String filePath = path.toString();

                //获取文件内容行数
                LineNumberReader reader = new LineNumberReader(new FileReader(filePath));
                reader.skip(Long.MAX_VALUE);  // 直接跳到文件末尾
                int line = reader.getLineNumber() + 1;
                lineNum+=line;
            }*/

            //重复度行数
            int duplicatedLine = duplicatedList.stream().mapToInt(RecordDuplicated::getLines).sum();

            //复杂度
            List<RecordComplexity> complexities = complexityList.stream()
                    .filter(e -> "project".equals(e.getType())).collect(Collectors.toList());

            Integer complexityNum=0;
            if (CollectionUtils.isNotEmpty(complexities)){
                 complexityNum = complexities.get(0).getComplexityNum();

                //lineNum=complexities.get(0).getCodeLineNon();
            }

            //resultMap.put("allLine",lineNum);
            resultMap.put("duplicatedLine",duplicatedLine);
            resultMap.put("complexityNum",complexityNum);
            if (!ObjectUtils.isEmpty(lineNum)){
                double percentage = ((double)duplicatedLine / lineNum) * 100;
                DecimalFormat df = new DecimalFormat("#.#%");
                String format = df.format(percentage / 100);

                resultMap.put("duplicated",format);
            }
            return resultMap;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
