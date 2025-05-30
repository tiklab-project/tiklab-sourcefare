package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanIssuesEntity;
import io.tiklab.sourcefare.scan.model.ScanIssuesQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ScanIssuesDao-扫描结果数据库访问
 */
@Repository
public class ScanIssuesDao {

    private static Logger logger = LoggerFactory.getLogger(ScanIssuesDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanIssuesEntity
     * @return
     */
    public String createScanIssues(ScanIssuesEntity scanIssuesEntity) {
        return jpaTemplate.save(scanIssuesEntity,String.class);
    }

    /**
     * 更新
     * @param scanIssuesEntity
     */
    public void updateScanIssues(ScanIssuesEntity scanIssuesEntity){
        jpaTemplate.update(scanIssuesEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanIssues(String id){
        jpaTemplate.delete(ScanIssuesEntity.class,id);
    }

    /**
     * 条件删除存储库
     * @param deleteCondition
     */
    public void deleteScanIssues(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanIssuesEntity findScanIssues(String id){
        return jpaTemplate.findOne(ScanIssuesEntity.class,id);
    }

    /**
    * 查询所有存储库
    * @return
    */
    public List<ScanIssuesEntity> findAllScanIssues() {
        return jpaTemplate.findAll(ScanIssuesEntity.class);
    }

    /**
     * 通过ids查询存储库
     * @param idList
     * @return List <ScanIssuesEntity>
     */
    public List<ScanIssuesEntity> findScanIssuesList(List<String> idList) {
        return jpaTemplate.findList(ScanIssuesEntity.class,idList);
    }

    /**
     * 条件查询存储库
     * @param scanIssuesQuery
     * @return List <ScanIssuesEntity>
     */
    public List<ScanIssuesEntity> findScanIssuesList(ScanIssuesQuery scanIssuesQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanIssuesEntity.class)
                .eq("scanRecordId",scanIssuesQuery.getScanRecordId())
                .orders(scanIssuesQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanIssuesEntity.class);
    }

    /**
     * 条件分页查询存储库
     * @param scanIssuesQuery
     * @return Pagination <ScanIssuesEntity>
     */
    public Pagination<ScanIssuesEntity> findScanIssuesPage(ScanIssuesQuery scanIssuesQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanIssuesEntity.class)
                .eq("scanRecordId",scanIssuesQuery.getScanRecordId())
                .orders(scanIssuesQuery.getOrderParams())
                .pagination(scanIssuesQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ScanIssuesEntity.class);
    }
}