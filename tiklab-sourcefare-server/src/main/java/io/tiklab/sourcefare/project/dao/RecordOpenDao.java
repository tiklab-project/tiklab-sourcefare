package io.tiklab.sourcefare.project.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.project.entity.RecordOpenEntity;
import io.tiklab.sourcefare.project.model.RecordOpenQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * RecordOpenDao-打开项目的记录
 */
@Repository
public class RecordOpenDao {

    private static Logger logger = LoggerFactory.getLogger(RecordOpenDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param recordOpenEntity
     * @return
     */
    public String createRecordOpen(RecordOpenEntity recordOpenEntity) {
        return jpaTemplate.save(recordOpenEntity,String.class);
    }

    /**
     * 更新
     * @param recordOpenEntity
     */
    public void updateRecordOpen(RecordOpenEntity recordOpenEntity){
        jpaTemplate.update(recordOpenEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteRecordOpen(String id){
        jpaTemplate.delete(RecordOpenEntity.class,id);
    }

    public void deleteRecordOpen(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public RecordOpenEntity findRecordOpen(String id){
        return jpaTemplate.findOne(RecordOpenEntity.class,id);
    }

    /**
    * findAllRecordOpen
    * @return
    */
    public List<RecordOpenEntity> findAllRecordOpen() {
        return jpaTemplate.findAll(RecordOpenEntity.class);
    }

    /**
     * 通过ids查询
     * @param idList
     * @return
     */
    public List<RecordOpenEntity> findRecordOpenList(List<String> idList) {
        return jpaTemplate.findList(RecordOpenEntity.class,idList);
    }

    /**
     * 条件查询插件
     * @param recordOpenQuery
     * @return
     */
    public List<RecordOpenEntity> findRecordOpenList(RecordOpenQuery recordOpenQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RecordOpenEntity.class)
                .eq("userId", recordOpenQuery.getUserId())
                .eq("projectId", recordOpenQuery.getProjectId())
                .get();
        return jpaTemplate.findList(queryCondition, RecordOpenEntity.class);
    }

    /**
     * 条件分页查询插件
     * @param recordOpenQuery
     * @return
     */
    public Pagination<RecordOpenEntity> findRecordOpenPage(RecordOpenQuery recordOpenQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RecordOpenEntity.class)
                .eq("userId", recordOpenQuery.getUserId())
                .eq("projectId", recordOpenQuery.getProjectId())
                .get();
        return jpaTemplate.findPage(queryCondition, RecordOpenEntity.class);
    }

}