package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.RecordInstanceCondEntity;
import io.tiklab.sourcefare.scan.model.RecordInstanceCondQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Map;

/**
 * RecordInstanceCondDao-扫描记录实例的动态
 */
@Repository
public class RecordInstanceCondDao {

    private static Logger logger = LoggerFactory.getLogger(RecordInstanceCondDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanRecordInstanceCondEntity
     * @return
     */
    public String createRecordInstanceCond(RecordInstanceCondEntity scanRecordInstanceCondEntity) {
        return jpaTemplate.save(scanRecordInstanceCondEntity,String.class);
    }

    /**
     * 更新
     * @param scanRecordInstanceCondEntity
     */
    public void updateRecordInstanceCond(RecordInstanceCondEntity scanRecordInstanceCondEntity){
        jpaTemplate.update(scanRecordInstanceCondEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteRecordInstanceCond(String id){
        jpaTemplate.delete(RecordInstanceCondEntity.class,id);
    }

    /**
     * 条件删除扫描扫描记录实例的动态
     * @param deleteCondition
     */
    public void deleteRecordInstanceCond(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public RecordInstanceCondEntity findRecordInstanceCond(String id){
        return jpaTemplate.findOne(RecordInstanceCondEntity.class,id);
    }

    /**
    * 查询所有扫描记录实例的动态
    * @return
    */
    public List<RecordInstanceCondEntity> findAllRecordInstanceCond() {
        return jpaTemplate.findAll(RecordInstanceCondEntity.class);
    }

    /**
     * 通过ids查询扫描记录实例的动态
     * @param idList
     * @return List <RecordInstanceCondEntity>
     */
    public List<RecordInstanceCondEntity> findRecordInstanceCondList(List<String> idList) {
        return jpaTemplate.findList(RecordInstanceCondEntity.class,idList);
    }

    /**
     * 条件查询扫描记录实例的动态
     * @param scanRecordInstanceCondQuery
     * @return List <RecordInstanceCondEntity>
     */
    public List<RecordInstanceCondEntity> findRecordInstanceCondList(RecordInstanceCondQuery scanRecordInstanceCondQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RecordInstanceCondEntity.class)
                .eq("scanRecordId",scanRecordInstanceCondQuery.getScanRecordId())
                .eq("projectId",scanRecordInstanceCondQuery.getProjectId())
                .orders(scanRecordInstanceCondQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, RecordInstanceCondEntity.class);
    }

    /**
     * 条件分页查询扫描记录实例的动态
     * @param scanRecordInstanceCondQuery
     * @return Pagination <RecordInstanceCondEntity>
     */
    public Pagination<RecordInstanceCondEntity> findRecordInstanceCondPage(RecordInstanceCondQuery scanRecordInstanceCondQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RecordInstanceCondEntity.class)
                .eq("scanRecordId",scanRecordInstanceCondQuery.getScanRecordId())
                .eq("projectId",scanRecordInstanceCondQuery.getProjectId())
                .orders(scanRecordInstanceCondQuery.getOrderParams())
                .pagination(scanRecordInstanceCondQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, RecordInstanceCondEntity.class);
    }


    public List<RecordInstanceCondEntity> findInstanceCondByInstanceIds(String[] instanceIds) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RecordInstanceCondEntity.class)
                .in("recordInstanceId",instanceIds)
                .get();
        return jpaTemplate.findList(queryCondition, RecordInstanceCondEntity.class);
    }
}