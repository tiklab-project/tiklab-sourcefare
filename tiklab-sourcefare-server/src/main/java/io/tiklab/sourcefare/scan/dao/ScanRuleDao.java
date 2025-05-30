package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanRuleEntity;
import io.tiklab.sourcefare.scan.model.ScanRuleQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ScanRuleDao-扫描规则数据库访问
 */
@Repository
public class ScanRuleDao {

    private static Logger logger = LoggerFactory.getLogger(ScanRuleDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanRuleEntity
     * @return
     */
    public String createScanRule(ScanRuleEntity scanRuleEntity) {
        return jpaTemplate.save(scanRuleEntity,String.class);
    }

    /**
     * 更新
     * @param scanRuleEntity
     */
    public void updateScanRule(ScanRuleEntity scanRuleEntity){
        jpaTemplate.update(scanRuleEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanRule(String id){
        jpaTemplate.delete(ScanRuleEntity.class,id);
    }

    /**
     * 条件删除存储库
     * @param deleteCondition
     */
    public void deleteScanRule(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanRuleEntity findScanRule(String id){
        return jpaTemplate.findOne(ScanRuleEntity.class,id);
    }

    /**
    * 查询所有存储库
    * @return
    */
    public List<ScanRuleEntity> findAllScanRule() {
        return jpaTemplate.findAll(ScanRuleEntity.class);
    }

    /**
     * 通过ids查询存储库
     * @param idList
     * @return List <ScanRuleEntity>
     */
    public List<ScanRuleEntity> findScanRuleList(List<String> idList) {
        return jpaTemplate.findList(ScanRuleEntity.class,idList);
    }

    /**
     * 条件查询存储库
     * @param scanRuleQuery
     * @return List <ScanRuleEntity>
     */
    public List<ScanRuleEntity> findScanRuleList(ScanRuleQuery scanRuleQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanRuleEntity.class)
                .eq("ruleSetId",scanRuleQuery.getRuleSetId())
                .orders(scanRuleQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanRuleEntity.class);
    }

    /**
     * 条件分页查询存储库
     * @param scanRuleQuery
     * @return Pagination <ScanRuleEntity>
     */
    public Pagination<ScanRuleEntity> findScanRulePage(ScanRuleQuery scanRuleQuery) {
        QueryCondition queryCondition =QueryBuilders.createQuery(ScanRuleEntity.class)
                .eq("ruleSetId", scanRuleQuery.getRuleSetId())
                .eq("problemLevel",scanRuleQuery.getProblemLevel())
                .eq("scanTool",scanRuleQuery.getScanTool())
                .like("ruleName",scanRuleQuery.getRuleName())
                .orders(scanRuleQuery.getOrderParams())
                .pagination(scanRuleQuery.getPageParam())
                 .get();
        return jpaTemplate.findPage(queryCondition, ScanRuleEntity.class);
    }
}