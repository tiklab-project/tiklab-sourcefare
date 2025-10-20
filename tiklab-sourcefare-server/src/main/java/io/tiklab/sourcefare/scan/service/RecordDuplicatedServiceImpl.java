package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.dao.RecordDuplicatedDao;
import io.tiklab.sourcefare.scan.entity.RecordDuplicatedEntity;
import io.tiklab.sourcefare.scan.model.RecordDuplicated;
import io.tiklab.sourcefare.scan.model.RecordDuplicatedQuery;
import io.tiklab.sourcefare.scan.model.RecordInstance;
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
* RecordDuplicatedServiceImpl-项目扫描记录重复度
*/
@Service
@Exporter
public class RecordDuplicatedServiceImpl implements RecordDuplicatedService {

    @Autowired
    RecordDuplicatedDao recordDuplicatedDao;

    @Autowired
    JoinTemplate joinTemplate;


    @Autowired
    PathSetService pathSetService;

    @Override
    public String createRecordDuplicated(RecordDuplicated recordDuplicated) {

        RecordDuplicatedEntity recordDuplicatedEntity = BeanMapper.map(recordDuplicated, RecordDuplicatedEntity.class);
        recordDuplicatedEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String recordDuplicatedId= recordDuplicatedDao.createRecordDuplicated(recordDuplicatedEntity);

        return recordDuplicatedId;
    }

    @Override
    public void createRecordDuplicated(List<RecordDuplicated> recordDuplicated) {
        recordDuplicatedDao.createRecordDuplicated(recordDuplicated);
    }

    @Override
    public void updateRecordDuplicated(@NotNull @Valid RecordDuplicated recordDuplicated) {
        RecordDuplicatedEntity recordDuplicatedEntity = BeanMapper.map(recordDuplicated, RecordDuplicatedEntity.class);

        recordDuplicatedDao.updateRecordDuplicated(recordDuplicatedEntity);
    }

    @Override
    public void deleteRecordDuplicated(@NotNull String id) {
        recordDuplicatedDao.deleteRecordDuplicated(id);
    }

    @Override
    public void deleteRecordDuplicatedByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(RecordDuplicatedEntity.class)
                .eq(key,value)
                .get();
        recordDuplicatedDao.deleteRecordDuplicated(deleteCondition);
    }




    @Override
    public RecordDuplicated findOne(String id) {
        RecordDuplicatedEntity recordDuplicatedEntity = recordDuplicatedDao.findRecordDuplicated(id);

        RecordDuplicated recordDuplicated = BeanMapper.map(recordDuplicatedEntity, RecordDuplicated.class);
        return recordDuplicated;
    }

    @Override
    public List<RecordDuplicated> findList(List<String> idList) {
        List<RecordDuplicatedEntity> recordDuplicatedEntityList =  recordDuplicatedDao.findRecordDuplicatedList(idList);

        List<RecordDuplicated> recordDuplicatedList =  BeanMapper.mapList(recordDuplicatedEntityList, RecordDuplicated.class);
        return recordDuplicatedList;
    }

    @Override
    public RecordDuplicated findRecordDuplicated(@NotNull String id) {
        RecordDuplicated recordDuplicated = findOne(id);
        
        return recordDuplicated;
    }

    @Override
    public List<RecordDuplicated> findAllRecordDuplicated() {
        List<RecordDuplicatedEntity> recordDuplicatedEntityList =  recordDuplicatedDao.findAllRecordDuplicated();

        List<RecordDuplicated> recordDuplicatedList =  BeanMapper.mapList(recordDuplicatedEntityList, RecordDuplicated.class);
        
        return recordDuplicatedList;
    }

    @Override
    public List<RecordDuplicated> findRecordDuplicatedList(RecordDuplicatedQuery RecordDuplicatedQuery) {
        List<RecordDuplicatedEntity> recordDuplicatedEntityList = recordDuplicatedDao.findRecordDuplicatedList(RecordDuplicatedQuery);

        List<RecordDuplicated> recordDuplicatedList = BeanMapper.mapList(recordDuplicatedEntityList, RecordDuplicated.class);
        if (CollectionUtils.isNotEmpty(recordDuplicatedList)){
            recordDuplicatedList = recordDuplicatedList.stream().sorted(Comparator.comparing(RecordDuplicated::getCreateTime).reversed()).collect(Collectors.toList());
        }

        return recordDuplicatedList;
    }

    @Override
    public List<RecordDuplicated> findRecordDuplicatedByCon(String value,String type) {
        List<RecordDuplicated> recordDuplicatedList = recordDuplicatedDao.findRecordDuplicatedByCon(value,type);

        return recordDuplicatedList;
    }

    @Override
    public Pagination<RecordDuplicated> findRecordDuplicatedPage(RecordDuplicatedQuery RecordDuplicatedQuery) {

        Pagination<RecordDuplicatedEntity>  pagination = recordDuplicatedDao.findRecordDuplicatedPage(RecordDuplicatedQuery);

        List<RecordDuplicated> recordDuplicatedList = BeanMapper.mapList(pagination.getDataList(), RecordDuplicated.class);
      
        
        return PaginationBuilder.build(pagination,recordDuplicatedList);
    }

}