package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanSchemeRuleEntity;
import io.tiklab.sourcefare.scan.model.ScanSchemeRuleQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ScanSchemeRuleDao-扫描方案和规则关系
 */
@Repository
public class ScanSchemeRuleDao {

    private static Logger logger = LoggerFactory.getLogger(ScanSchemeRuleDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanSchemeRuleEntity
     * @return
     */
    public String createScanSchemeRule(ScanSchemeRuleEntity scanSchemeRuleEntity) {
        return jpaTemplate.save(scanSchemeRuleEntity,String.class);
    }

    /**
     * 更新
     * @param scanSchemeRuleEntity
     */
    public void updateScanSchemeRule(ScanSchemeRuleEntity scanSchemeRuleEntity){
        jpaTemplate.update(scanSchemeRuleEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanSchemeRule(String id){
        jpaTemplate.delete(ScanSchemeRuleEntity.class,id);
    }

    /**
     * 条件删除存储库
     * @param deleteCondition
     */
    public void deleteScanSchemeRule(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanSchemeRuleEntity findScanSchemeRule(String id){
        return jpaTemplate.findOne(ScanSchemeRuleEntity.class,id);
    }

    /**
    * 查询所有存储库
    * @return
    */
    public List<ScanSchemeRuleEntity> findAllScanSchemeRule() {
        return jpaTemplate.findAll(ScanSchemeRuleEntity.class);
    }

    /**
     * 通过ids查询存储库
     * @param idList
     * @return List <ScanSchemeRuleEntity>
     */
    public List<ScanSchemeRuleEntity> findScanSchemeRuleList(List<String> idList) {
        return jpaTemplate.findList(ScanSchemeRuleEntity.class,idList);
    }

    /**
     * 条件查询存储库
     * @param scanSchemeRuleQuery
     * @return List <ScanSchemeRuleEntity>
     */
    public List<ScanSchemeRuleEntity> findScanSchemeRuleList(ScanSchemeRuleQuery scanSchemeRuleQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanSchemeRuleEntity.class)
                .eq("scanSchemeId",scanSchemeRuleQuery.getScanSchemeId())
                .eq("schemeRulesetId", scanSchemeRuleQuery.getSchemeRulesetId())
                .orders(scanSchemeRuleQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanSchemeRuleEntity.class);
    }

    /**
     * 条件分页查询存储库
     * @param scanSchemeRuleQuery
     * @return Pagination <ScanSchemeRuleEntity>
     */
    public Pagination<ScanSchemeRuleEntity> findScanSchemeRulePage(ScanSchemeRuleQuery scanSchemeRuleQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanSchemeRuleEntity.class)
                .eq("scanSchemeId",scanSchemeRuleQuery.getScanSchemeId())
                .eq("schemeRulesetId", scanSchemeRuleQuery.getSchemeRulesetId())
                .orders(scanSchemeRuleQuery.getOrderParams())
                .pagination(scanSchemeRuleQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ScanSchemeRuleEntity.class);
    }
}