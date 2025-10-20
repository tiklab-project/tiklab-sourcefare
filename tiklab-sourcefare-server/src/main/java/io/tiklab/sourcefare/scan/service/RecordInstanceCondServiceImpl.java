package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.scan.dao.RecordInstanceCondDao;
import io.tiklab.sourcefare.scan.entity.RecordInstanceCondEntity;
import io.tiklab.sourcefare.scan.model.RecordInstanceCond;
import io.tiklab.sourcefare.scan.model.RecordInstanceCondQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
* RecordInstanceCondServiceImpl-扫描记录实例的动态
*/
@Service
@Exporter
public class RecordInstanceCondServiceImpl implements RecordInstanceCondService {

    @Autowired
    RecordInstanceCondDao scanRecordInstanceCondDao;

    @Autowired
    JoinTemplate joinTemplate;


    @Override
    public String createRecordInstanceCond(@NotNull @Valid RecordInstanceCond openRecord) {

        RecordInstanceCondEntity openRecordEntity = BeanMapper.map(openRecord, RecordInstanceCondEntity.class);
        openRecordEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String openRecordId= scanRecordInstanceCondDao.createRecordInstanceCond(openRecordEntity);

        return openRecordId;
    }

    @Override
    public void updateRecordInstanceCond(@NotNull @Valid RecordInstanceCond openRecord) {
        RecordInstanceCondEntity openRecordEntity = BeanMapper.map(openRecord, RecordInstanceCondEntity.class);

        scanRecordInstanceCondDao.updateRecordInstanceCond(openRecordEntity);
    }

    @Override
    public void deleteRecordInstanceCond(@NotNull String id) {
        scanRecordInstanceCondDao.deleteRecordInstanceCond(id);

    }

    @Override
    public void deleteRecordInstanceCondByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(RecordInstanceCondEntity.class)
                .eq(key,value)
                .get();
        scanRecordInstanceCondDao.deleteRecordInstanceCond(deleteCondition);
    }

    @Override
    public RecordInstanceCond findOne(String id) {
        RecordInstanceCondEntity openRecordEntity = scanRecordInstanceCondDao.findRecordInstanceCond(id);

        RecordInstanceCond openRecord = BeanMapper.map(openRecordEntity, RecordInstanceCond.class);
        return openRecord;
    }

    @Override
    public List<RecordInstanceCond> findList(List<String> idList) {
        List<RecordInstanceCondEntity> openRecordEntityList =  scanRecordInstanceCondDao.findRecordInstanceCondList(idList);

        List<RecordInstanceCond> openRecordList =  BeanMapper.mapList(openRecordEntityList, RecordInstanceCond.class);
        return openRecordList;
    }

    @Override
    public RecordInstanceCond findRecordInstanceCond(@NotNull String id) {
        RecordInstanceCond openRecord = findOne(id);

        joinTemplate.joinQuery(openRecord);

        return openRecord;
    }

    @Override
    public List<RecordInstanceCond> findAllRecordInstanceCond() {
        List<RecordInstanceCondEntity> openRecordEntityList =  scanRecordInstanceCondDao.findAllRecordInstanceCond();

        List<RecordInstanceCond> openRecordList =  BeanMapper.mapList(openRecordEntityList, RecordInstanceCond.class);

        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public List<RecordInstanceCond> findRecordInstanceCondList(RecordInstanceCondQuery RecordInstanceCondQuery) {
        List<RecordInstanceCondEntity> openRecordEntityList = scanRecordInstanceCondDao.findRecordInstanceCondList(RecordInstanceCondQuery);

        List<RecordInstanceCond> openRecordList = BeanMapper.mapList(openRecordEntityList, RecordInstanceCond.class);
        joinTemplate.joinQuery(openRecordList);
        if (CollectionUtils.isNotEmpty(openRecordList)){
            openRecordList = openRecordList.stream().sorted(Comparator.comparing(RecordInstanceCond::getCreateTime).reversed()).collect(Collectors.toList());
        }

        return openRecordList;
    }

    @Override
    public Pagination<RecordInstanceCond> findRecordInstanceCondPage(RecordInstanceCondQuery RecordInstanceCondQuery) {
        Pagination<RecordInstanceCondEntity>  pagination = scanRecordInstanceCondDao.findRecordInstanceCondPage(RecordInstanceCondQuery);

        List<RecordInstanceCond> openRecordList = BeanMapper.mapList(pagination.getDataList(), RecordInstanceCond.class);
        joinTemplate.joinQuery(openRecordList);


        return PaginationBuilder.build(pagination,openRecordList);
    }

    @Override
    public List<RecordInstanceCond> findRecordInstanceCondList(String[] instanceIds) {
        List<RecordInstanceCondEntity> openRecordEntityList=scanRecordInstanceCondDao.findInstanceCondByInstanceIds(instanceIds);

        List<RecordInstanceCond> recordList = BeanMapper.mapList(openRecordEntityList, RecordInstanceCond.class);
        return recordList;
    }
}