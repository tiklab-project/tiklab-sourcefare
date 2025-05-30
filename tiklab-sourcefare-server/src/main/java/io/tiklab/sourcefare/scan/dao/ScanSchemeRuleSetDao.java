package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanSchemeRuleSetEntity;
import io.tiklab.sourcefare.scan.model.ScanSchemeRuleSetQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ScanSchemeRuleSetDao-扫描方案规则集关系
 */
@Repository
public class ScanSchemeRuleSetDao {

    private static Logger logger = LoggerFactory.getLogger(ScanSchemeRuleSetDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanSchemeRuleSetEntity
     * @return
     */
    public String createScanSchemeRuleSet(ScanSchemeRuleSetEntity scanSchemeRuleSetEntity) {
        return jpaTemplate.save(scanSchemeRuleSetEntity,String.class);
    }

    /**
     * 更新
     * @param scanSchemeRuleSetEntity
     */
    public void updateScanSchemeRuleSet(ScanSchemeRuleSetEntity scanSchemeRuleSetEntity){
        jpaTemplate.update(scanSchemeRuleSetEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanSchemeRuleSet(String id){
        jpaTemplate.delete(ScanSchemeRuleSetEntity.class,id);
    }

    /**
     * 条件删除存储库
     * @param deleteCondition
     */
    public void deleteScanSchemeRuleSet(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanSchemeRuleSetEntity findScanSchemeRuleSet(String id){
        return jpaTemplate.findOne(ScanSchemeRuleSetEntity.class,id);
    }

    /**
    * 查询所有存储库
    * @return
    */
    public List<ScanSchemeRuleSetEntity> findAllScanSchemeRuleSet() {
        return jpaTemplate.findAll(ScanSchemeRuleSetEntity.class);
    }

    /**
     * 通过ids查询存储库
     * @param idList
     * @return List <ScanSchemeRuleSetEntity>
     */
    public List<ScanSchemeRuleSetEntity> findScanSchemeRuleSetList(List<String> idList) {
        return jpaTemplate.findList(ScanSchemeRuleSetEntity.class,idList);
    }

    /**
     * 条件查询存储库
     * @param scanSchemeRuleSetQuery
     * @return List <ScanSchemeRuleSetEntity>
     */
    public List<ScanSchemeRuleSetEntity> findScanSchemeRuleSetList(ScanSchemeRuleSetQuery scanSchemeRuleSetQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanSchemeRuleSetEntity.class)
                .eq("scanSchemeId",scanSchemeRuleSetQuery.getScanSchemeId())
                .eq("ruleSetId",scanSchemeRuleSetQuery.getRuleSetId())
                .orders(scanSchemeRuleSetQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanSchemeRuleSetEntity.class);
    }

    /**
     * 条件分页查询存储库
     * @param scanSchemeRuleSetQuery
     * @return Pagination <ScanSchemeRuleSetEntity>
     */
    public Pagination<ScanSchemeRuleSetEntity> findScanSchemeRuleSetPage(ScanSchemeRuleSetQuery scanSchemeRuleSetQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanSchemeRuleSetEntity.class)
                .eq("scanSchemeId",scanSchemeRuleSetQuery.getScanSchemeId())
                .eq("ruleSetId",scanSchemeRuleSetQuery.getRuleSetId())
                .orders(scanSchemeRuleSetQuery.getOrderParams())
                .pagination(scanSchemeRuleSetQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ScanSchemeRuleSetEntity.class);
    }
}