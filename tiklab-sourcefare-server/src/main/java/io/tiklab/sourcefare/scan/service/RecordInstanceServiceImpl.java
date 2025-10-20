package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.entity.RecordInstanceEntity;
import io.tiklab.sourcefare.scan.dao.RecordInstanceDao;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.io.FileUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.io.File;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
* ScanRecordInstanceServiceImpl-扫描记录实例接口实现
*/
@Service
@Exporter
public class RecordInstanceServiceImpl implements RecordInstanceService {

    @Autowired
    RecordInstanceDao scanRecordInstanceDao;

    @Autowired
    RecordInstanceCondService recordInstanceCondService;

    @Autowired
    IssueStatisticService issueStatisticService;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    JoinTemplate joinTemplate;


    @Autowired
    PathSetService pathSetService;

    @Override
    public String createScanRecordInstance(@NotNull @Valid RecordInstance recordInstance) {

        RecordInstanceEntity recordInstanceEntity = BeanMapper.map(recordInstance, RecordInstanceEntity.class);
        recordInstanceEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String recordInstanceId= scanRecordInstanceDao.createScanRecordInstance(recordInstanceEntity);

        return recordInstanceId;
    }

    @Override
    public void createScanRecordInstance( List<RecordInstance> recordInstanceList) {
        scanRecordInstanceDao.addList(recordInstanceList);
    }

    @Override
    public void updateScanRecordInstance(@NotNull @Valid RecordInstance recordInstance) {
        RecordInstanceEntity recordInstanceEntity = BeanMapper.map(recordInstance, RecordInstanceEntity.class);

        scanRecordInstanceDao.updateScanRecordInstance(recordInstanceEntity);

        //更新扫描问题的状态时同时需要更新问题统计的状态
        IssueStatisticQuery statisticQuery = new IssueStatisticQuery();
        statisticQuery.setProjectId(recordInstance.getProjectId());
        statisticQuery.setFilePath(recordInstance.getFilePath());
        statisticQuery.setProblemLine(recordInstance.getProblemLine());
        statisticQuery.setRuleName(recordInstance.getRuleName());
        List<IssueStatistic> issueStatisticList = issueStatisticService.findIssueStatisticList(statisticQuery);
        if (CollectionUtils.isNotEmpty(issueStatisticList)){
            IssueStatistic issueStatistic = issueStatisticList.get(0);
            issueStatistic.setProblemState(recordInstance.getState());
            issueStatisticService.updateIssueStatistic(issueStatistic);
        }
    }

    @Override
    public void deleteScanRecordInstance(@NotNull String id) {
        scanRecordInstanceDao.deleteScanRecordInstance(id);
    }

    @Override
    public void deleteScanRecordInstanceByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(RecordInstanceEntity.class)
                .eq(key,value)
                .get();
        scanRecordInstanceDao.deleteScanRecordInstance(deleteCondition);

        //删除扫描计划时候需要吧对应计划的代码删除
        if (key.equals("scanPlayId")){
            String s = pathSetService.codePath() + "/" + value;
            File file = new File(s);
            if (file.exists()){
                try {
                    FileUtils.deleteDirectory(file);
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }




    @Override
    public RecordInstance findOne(String id) {
        RecordInstanceEntity recordInstanceEntity = scanRecordInstanceDao.findScanRecordInstance(id);

        RecordInstance recordInstance = BeanMapper.map(recordInstanceEntity, RecordInstance.class);
        return recordInstance;
    }

    @Override
    public List<RecordInstance> findList(List<String> idList) {
        List<RecordInstanceEntity> recordInstanceEntityList =  scanRecordInstanceDao.findScanRecordInstanceList(idList);

        List<RecordInstance> recordInstanceList =  BeanMapper.mapList(recordInstanceEntityList, RecordInstance.class);
        return recordInstanceList;
    }

    @Override
    public RecordInstance findScanRecordInstance(@NotNull String id) {
        RecordInstance recordInstance = findOne(id);

        joinTemplate.joinQuery(recordInstance);

        return recordInstance;
    }

    @Override
    public List<RecordInstance> findAllScanRecordInstance() {
        List<RecordInstanceEntity> recordInstanceEntityList =  scanRecordInstanceDao.findAllScanRecordInstance();

        List<RecordInstance> recordInstanceList =  BeanMapper.mapList(recordInstanceEntityList, RecordInstance.class);

        joinTemplate.joinQuery(recordInstanceList);

        return recordInstanceList;
    }

    @Override
    public List<RecordInstance> findScanRecordInstanceList(RecordInstanceQuery ScanRecordInstanceQuery) {
        List<RecordInstanceEntity> recordInstanceEntityList = scanRecordInstanceDao.findScanRecordInstanceList(ScanRecordInstanceQuery);
        List<RecordInstance> recordInstanceList = BeanMapper.mapList(recordInstanceEntityList, RecordInstance.class);
        if (CollectionUtils.isNotEmpty(recordInstanceList)){
            recordInstanceList = recordInstanceList.stream().sorted(Comparator.comparing(RecordInstance::getCreateTime).reversed()).collect(Collectors.toList());
        }
        return recordInstanceList;
    }


    @Override
    public List<RecordInstance> findScanInstanceByCon(String value,String type) {
        List<RecordInstance> recordInstanceList = scanRecordInstanceDao.findScanInstanceByCon(value,type);

        return recordInstanceList;
    }

    @Override
    public Pagination<RecordInstance> findScanRecordInstancePage(RecordInstanceQuery ScanRecordInstanceQuery) {
        Pagination<RecordInstanceEntity>  pagination = scanRecordInstanceDao.findScanRecordInstancePage(ScanRecordInstanceQuery);

        List<RecordInstance> recordInstanceList = BeanMapper.mapList(pagination.getDataList(), RecordInstance.class);
        joinTemplate.joinQuery(recordInstanceList);


        return PaginationBuilder.build(pagination,recordInstanceList);
    }

    @Override
    public Pagination<RecordInstance> findRecordInstancePageByPlay(RecordInstanceQuery scanRecordInstanceQuery) {

        Pagination<RecordInstance> scanRecordInstancePage = this.findScanRecordInstancePage(scanRecordInstanceQuery);

        return scanRecordInstancePage;
    }

    @Override
    public Pagination<RecordInstance> findProjectInstancePage( RecordInstanceQuery scanRecordInstanceQuery) {
        String projectId = scanRecordInstanceQuery.getProjectId();

        Pagination<RecordInstanceEntity> pagination = scanRecordInstanceDao.findProjectInstancePage(scanRecordInstanceQuery);
        List<RecordInstance> recordInstanceList = BeanMapper.mapList(pagination.getDataList(), RecordInstance.class);


        if (CollectionUtils.isNotEmpty(recordInstanceList)){
            //查询最新一次的扫描记录
            List<ScanRecord> scanRecordList = scanRecordService.findScanRecordListByProjectId(projectId);
            List<ScanRecord> recordList = scanRecordList.stream().sorted(Comparator.comparing(ScanRecord::getScanTime)).collect(Collectors.toList());
            ScanRecord scanRecord = recordList.get(0);

            for (RecordInstance recordInstance:recordInstanceList){
                String fileName = recordInstance.getFileName();
                String ruleName = recordInstance.getRuleName();
                Integer problemLine = recordInstance.getProblemLine();

                //查询最新一次扫描中同一个文件是否相同行问题是否存在
                RecordInstanceQuery recordInstanceQuery = new RecordInstanceQuery();
                recordInstanceQuery.setScanRecordId(scanRecord.getId());
                recordInstanceQuery.setRuleName(ruleName);
                recordInstanceQuery.setFileName(fileName);
                recordInstanceQuery.setProblemLine(problemLine);
                List<RecordInstance> instanceList = this.findScanRecordInstanceList(recordInstanceQuery);
                String state = CollectionUtils.isNotEmpty(instanceList) ? "unsolved" : "solved";
                recordInstance.setProblemState(state);

                if (CollectionUtils.isNotEmpty(instanceList)){
                    String s = recordInstance.getState() == 0 ? "unsolved" : "solved";
                    recordInstance.setProblemState(s);
                }
            }
        }
        return PaginationBuilder.build(pagination,recordInstanceList);
    }

    @Override
    public Object findProjectInstanceNum(RecordInstanceQuery scanRecordInstanceQuery) {
         scanRecordInstanceDao.findProjectInstanceNum(scanRecordInstanceQuery);

        return null;
    }

}