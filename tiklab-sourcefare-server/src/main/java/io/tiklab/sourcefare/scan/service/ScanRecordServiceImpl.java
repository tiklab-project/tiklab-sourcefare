package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.sourcefare.scan.entity.ScanRecordEntity;
import io.tiklab.sourcefare.scan.dao.ScanRecordDao;
import io.tiklab.sourcefare.scan.model.RecordInstance;
import io.tiklab.sourcefare.scan.model.RecordInstanceQuery;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.model.ScanRecordQuery;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.*;
import java.util.stream.Collectors;

/**
* ScanRecordServiceImpl-扫描记录接口实现
*/
@Service
@Exporter
public class ScanRecordServiceImpl implements ScanRecordService {

    @Autowired
    ScanRecordDao scanRecordDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    RecordInstanceService scanRecordInstanceService;

    @Autowired
    RecordInstanceCondService recordInstanceCondService;

    @Autowired
    ScanRecordLogService recordLogService;

    @Autowired
    ProjectCoverService projectCoverService;

    @Autowired
    RecordComplexityService complexityService;

    @Autowired
    RecordDuplicatedService duplicatedService;

    @Override
    public String createScanRecord(@NotNull @Valid ScanRecord openRecord) {

        ScanRecordEntity openRecordEntity = BeanMapper.map(openRecord, ScanRecordEntity.class);
        openRecordEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String openRecordId= scanRecordDao.createScanRecord(openRecordEntity);

        return openRecordId;
    }

    @Override
    public void updateScanRecord(@NotNull @Valid ScanRecord openRecord) {
        ScanRecordEntity openRecordEntity = BeanMapper.map(openRecord, ScanRecordEntity.class);

        scanRecordDao.updateScanRecord(openRecordEntity);
    }

    @Override
    public void deleteScanRecord(@NotNull String id) {


        scanRecordDao.deleteScanRecord(id);
        //删除扫描记录实例
        scanRecordInstanceService.deleteScanRecordInstanceByCondition("scanRecordId",id);

        //扫描记录实例的动态
        recordInstanceCondService.deleteRecordInstanceCondByCondition("scanRecordId",id);

        //删除扫描日志
        recordLogService.deleteScanRecordLogByCondition("scanRecordId",id);

        //删除扫描覆盖率
        projectCoverService.deleteProjectCoverByCondition("scanRecordId",id);

        //删除扫描重复率
        duplicatedService.deleteRecordDuplicatedByCondition("recordId",id);

        //删除扫描复杂度
        complexityService.deleteRecordComplexityByCondition("recordId",id);

    }

    @Override
    public void deleteScanRecordByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ScanRecordEntity.class)
                .eq(key,value)
                .get();
        scanRecordDao.deleteScanRecord(deleteCondition);
    }

    @Override
    public ScanRecord findOne(String id) {
        ScanRecordEntity openRecordEntity = scanRecordDao.findScanRecord(id);

        ScanRecord openRecord = BeanMapper.map(openRecordEntity, ScanRecord.class);
        return openRecord;
    }

    @Override
    public List<ScanRecord> findList(List<String> idList) {
        List<ScanRecordEntity> openRecordEntityList =  scanRecordDao.findScanRecordList(idList);

        List<ScanRecord> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanRecord.class);
        return openRecordList;
    }

    @Override
    public ScanRecord findScanRecord(@NotNull String id) {
        ScanRecord openRecord = findOne(id);

        joinTemplate.joinQuery(openRecord);

        return openRecord;
    }

    @Override
    public List<ScanRecord> findAllScanRecord() {
        List<ScanRecordEntity> openRecordEntityList =  scanRecordDao.findAllScanRecord();

        List<ScanRecord> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanRecord.class);

        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public List<ScanRecord> findScanRecordList(ScanRecordQuery ScanRecordQuery) {
        List<ScanRecordEntity> openRecordEntityList = scanRecordDao.findScanRecordList(ScanRecordQuery);

        List<ScanRecord> openRecordList = BeanMapper.mapList(openRecordEntityList, ScanRecord.class);
        joinTemplate.joinQuery(openRecordList);
        if (CollectionUtils.isNotEmpty(openRecordList)){
            openRecordList = openRecordList.stream().sorted(Comparator.comparing(ScanRecord::getCreateTime).reversed()).collect(Collectors.toList());
        }

        return openRecordList;
    }

    @Override
    public List<ScanRecord> findScanRecordListByProjectId(String projectId) {
        ScanRecordQuery scanRecordQuery = new ScanRecordQuery().setProjectId(projectId);
        List<ScanRecordEntity> openRecordEntityList = scanRecordDao.findScanRecordList(scanRecordQuery);
        List<ScanRecord> openRecordList = BeanMapper.mapList(openRecordEntityList, ScanRecord.class);
        return openRecordList;
    }

    @Override
    public ScanRecord findNewScanRecord(String projectId) {
        ScanRecordQuery scanRecordQuery = new ScanRecordQuery();
        scanRecordQuery.setProjectId(projectId);
        List<ScanRecordEntity> openRecordEntityList = scanRecordDao.findScanRecordList(scanRecordQuery);
        List<ScanRecord> openRecordList = BeanMapper.mapList(openRecordEntityList, ScanRecord.class);
        if (CollectionUtils.isEmpty(openRecordList)){
            return null;
        }

        List<ScanRecord> scanRecords = openRecordList.stream().sorted(Comparator.comparing(ScanRecord::getCreateTime).reversed()).collect(Collectors.toList());

        return scanRecords.get(0);
    }

    @Override
    public Pagination<ScanRecord> findScanRecordPage(ScanRecordQuery ScanRecordQuery) {
        Pagination<ScanRecordEntity>  pagination = scanRecordDao.findScanRecordPage(ScanRecordQuery);

        List<ScanRecord> openRecordList = BeanMapper.mapList(pagination.getDataList(), ScanRecord.class);
        joinTemplate.joinQuery(openRecordList,new String[]{"scanUser"});

        openRecordList = openRecordList.stream().sorted(Comparator.comparing(ScanRecord::getCreateTime).reversed()).collect(Collectors.toList());
        return PaginationBuilder.build(pagination,openRecordList);
    }


}