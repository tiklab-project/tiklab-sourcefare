package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.dao.RecordComplexityDao;
import io.tiklab.sourcefare.scan.entity.RecordComplexityEntity;
import io.tiklab.sourcefare.scan.model.RecordComplexity;
import io.tiklab.sourcefare.scan.model.RecordComplexityQuery;
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
* RecordComplexityServiceImpl-项目扫描记录复杂度
*/
@Service
@Exporter
public class RecordComplexityServiceImpl implements RecordComplexityService {

    @Autowired
    RecordComplexityDao recordComplexityDao;

    @Autowired
    JoinTemplate joinTemplate;


    @Autowired
    PathSetService pathSetService;

    @Override
    public String createRecordComplexity(RecordComplexity recordComplexity) {

        RecordComplexityEntity recordComplexityEntity = BeanMapper.map(recordComplexity, RecordComplexityEntity.class);
        recordComplexityEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String recordComplexityId= recordComplexityDao.createRecordComplexity(recordComplexityEntity);

        return recordComplexityId;
    }

    @Override
    public void createRecordComplexity(List<RecordComplexity> recordComplexity) {
        recordComplexityDao.createRecordComplexity(recordComplexity);

    }

    @Override
    public void updateRecordComplexity(@NotNull @Valid RecordComplexity recordComplexity) {
        RecordComplexityEntity recordComplexityEntity = BeanMapper.map(recordComplexity, RecordComplexityEntity.class);

        recordComplexityDao.updateRecordComplexity(recordComplexityEntity);
    }

    @Override
    public void deleteRecordComplexity(@NotNull String id) {
        recordComplexityDao.deleteRecordComplexity(id);
    }

    @Override
    public void deleteRecordComplexityByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(RecordComplexityEntity.class)
                .eq(key,value)
                .get();
        recordComplexityDao.deleteRecordComplexity(deleteCondition);
    }




    @Override
    public RecordComplexity findOne(String id) {
        RecordComplexityEntity recordComplexityEntity = recordComplexityDao.findRecordComplexity(id);

        RecordComplexity recordComplexity = BeanMapper.map(recordComplexityEntity, RecordComplexity.class);
        return recordComplexity;
    }

    @Override
    public List<RecordComplexity> findList(List<String> idList) {
        List<RecordComplexityEntity> recordComplexityEntityList =  recordComplexityDao.findRecordComplexityList(idList);

        List<RecordComplexity> recordComplexityList =  BeanMapper.mapList(recordComplexityEntityList, RecordComplexity.class);
        return recordComplexityList;
    }

    @Override
    public RecordComplexity findRecordComplexity(@NotNull String id) {
        RecordComplexity recordComplexity = findOne(id);
        
        return recordComplexity;
    }

    @Override
    public List<RecordComplexity> findAllRecordComplexity() {
        List<RecordComplexityEntity> recordComplexityEntityList =  recordComplexityDao.findAllRecordComplexity();

        List<RecordComplexity> recordComplexityList =  BeanMapper.mapList(recordComplexityEntityList, RecordComplexity.class);
        
        return recordComplexityList;
    }

    @Override
    public List<RecordComplexity> findRecordComplexityList(RecordComplexityQuery RecordComplexityQuery) {
        List<RecordComplexityEntity> recordComplexityEntityList = recordComplexityDao.findRecordComplexityList(RecordComplexityQuery);

        List<RecordComplexity> recordComplexityList = BeanMapper.mapList(recordComplexityEntityList, RecordComplexity.class);
        if (CollectionUtils.isNotEmpty(recordComplexityList)){
            recordComplexityList = recordComplexityList.stream().sorted(Comparator.comparing(RecordComplexity::getCreateTime).reversed()).collect(Collectors.toList());
        }

        return recordComplexityList;
    }

    @Override
    public List<RecordComplexity> findRecordComplexityByCon(String value,String type) {
        List<RecordComplexity> recordComplexityList = recordComplexityDao.findRecordComplexityByRecord(value,type);
        return recordComplexityList;
    }

    @Override
    public Pagination<RecordComplexity> findRecordComplexityPage(RecordComplexityQuery RecordComplexityQuery) {

        Pagination<RecordComplexityEntity>  pagination = recordComplexityDao.findRecordComplexityPage(RecordComplexityQuery);

        List<RecordComplexity> recordComplexityList = BeanMapper.mapList(pagination.getDataList(), RecordComplexity.class);
      
        
        return PaginationBuilder.build(pagination,recordComplexityList);
    }

}