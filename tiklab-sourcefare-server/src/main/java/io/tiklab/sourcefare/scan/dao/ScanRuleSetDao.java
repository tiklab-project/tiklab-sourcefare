package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanRuleSetEntity;
import io.tiklab.sourcefare.scan.model.ScanRuleSetQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ScanRuleSetDao-扫描规则集数据库访问
 */
@Repository
public class ScanRuleSetDao {

    private static Logger logger = LoggerFactory.getLogger(ScanRuleSetDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 执行sql
     * @param sql
     */
    public void execSql(String sql) {
          jpaTemplate.getJdbcTemplate().execute(sql);;
    }

    /**
     * 创建
     * @param scanRuleSetEntity
     * @return
     */
    public String createScanRuleSet(ScanRuleSetEntity scanRuleSetEntity) {
        return jpaTemplate.save(scanRuleSetEntity,String.class);
    }

    /**
     * 更新
     * @param scanRuleSetEntity
     */
    public void updateScanRuleSet(ScanRuleSetEntity scanRuleSetEntity){
        jpaTemplate.update(scanRuleSetEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanRuleSet(String id){
        jpaTemplate.delete(ScanRuleSetEntity.class,id);
    }

    /**
     * 条件删除存储库
     * @param deleteCondition
     */
    public void deleteScanRuleSet(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanRuleSetEntity findScanRuleSet(String id){
        return jpaTemplate.findOne(ScanRuleSetEntity.class,id);
    }

    /**
    * 查询所有存储库
    * @return
    */
    public List<ScanRuleSetEntity> findAllScanRuleSet() {
        return jpaTemplate.findAll(ScanRuleSetEntity.class);
    }

    /**
     * 通过ids查询存储库
     * @param idList
     * @return List <ScanRuleSetEntity>
     */
    public List<ScanRuleSetEntity> findScanRuleSetList(List<String> idList) {
        return jpaTemplate.findList(ScanRuleSetEntity.class,idList);
    }

    /**
     * 条件查询存储库
     * @param scanRuleSetQuery
     * @return List <ScanRuleSetEntity>
     */
    public List<ScanRuleSetEntity> findScanRuleSetList(ScanRuleSetQuery scanRuleSetQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanRuleSetEntity.class)
                .eq("language", scanRuleSetQuery.getLanguage())
                .like("ruleSetName",scanRuleSetQuery.getRuleSetName())
                .orders(scanRuleSetQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanRuleSetEntity.class);
    }

    /**
     * 条件分页查询存储库
     * @param scanRuleSetQuery
     * @return Pagination <ScanRuleSetEntity>
     */
    public Pagination<ScanRuleSetEntity> findScanRuleSetPage(ScanRuleSetQuery scanRuleSetQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanRuleSetEntity.class)
                .eq("language", scanRuleSetQuery.getLanguage())
                .orders(scanRuleSetQuery.getOrderParams())
                .pagination(scanRuleSetQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ScanRuleSetEntity.class);
    }
}