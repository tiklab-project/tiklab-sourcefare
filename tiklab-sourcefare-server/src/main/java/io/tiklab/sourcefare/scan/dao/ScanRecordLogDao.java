package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanRecordLogEntity;
import io.tiklab.sourcefare.scan.model.ScanRecordLogQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ScanRecordLogDao-扫描记录日志
 */
@Repository
public class ScanRecordLogDao {

    private static Logger logger = LoggerFactory.getLogger(ScanRecordLogDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanRecordLogEntity
     * @return
     */
    public String createScanRecordLog(ScanRecordLogEntity scanRecordLogEntity) {
        return jpaTemplate.save(scanRecordLogEntity,String.class);
    }

    /**
     * 更新
     * @param scanRecordLogEntity
     */
    public void updateScanRecordLog(ScanRecordLogEntity scanRecordLogEntity){
        jpaTemplate.update(scanRecordLogEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanRecordLog(String id){
        jpaTemplate.delete(ScanRecordLogEntity.class,id);
    }

    /**
     * 条件删除扫描记录日志
     * @param deleteCondition
     */
    public void deleteScanRecordLog(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanRecordLogEntity findScanRecordLog(String id){
        return jpaTemplate.findOne(ScanRecordLogEntity.class,id);
    }

    /**
    * 查询所有扫描记录日志
    * @return
    */
    public List<ScanRecordLogEntity> findAllScanRecordLog() {
        return jpaTemplate.findAll(ScanRecordLogEntity.class);
    }

    /**
     * 通过ids扫描记录日志
     * @param idList
     * @return List <ScanRecordLogEntity>
     */
    public List<ScanRecordLogEntity> findScanRecordLogList(List<String> idList) {
        return jpaTemplate.findList(ScanRecordLogEntity.class,idList);
    }

    /**
     * 条件查询扫描记录日志
     * @param scanRecordLogQuery
     * @return List <ScanRecordLogEntity>
     */
    public List<ScanRecordLogEntity> findScanRecordLogList(ScanRecordLogQuery scanRecordLogQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanRecordLogEntity.class)
                .eq("scanRecordId",scanRecordLogQuery.getScanRecordId())
                .eq("projectId",scanRecordLogQuery.getProjectId())
                .orders(scanRecordLogQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanRecordLogEntity.class);
    }

    /**
     * 条件分页查询扫描记录日志
     * @param scanRecordLogQuery
     * @return Pagination <ScanRecordLogEntity>
     */
    public Pagination<ScanRecordLogEntity> findScanRecordLogPage(ScanRecordLogQuery scanRecordLogQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanRecordLogEntity.class)
                .eq("scanRecordId",scanRecordLogQuery.getScanRecordId())
                .eq("projectId",scanRecordLogQuery.getProjectId())
                .orders(scanRecordLogQuery.getOrderParams())
                .pagination(scanRecordLogQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ScanRecordLogEntity.class);
    }


}