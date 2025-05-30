package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanRecordInstanceEntity;
import io.tiklab.sourcefare.scan.model.ScanRecordInstanceQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ScanRecordInstanceDao-扫描记录实例数据库访问
 */
@Repository
public class ScanRecordInstanceDao {

    private static Logger logger = LoggerFactory.getLogger(ScanRecordInstanceDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanRecordInstanceEntity
     * @return
     */
    public String createScanRecordInstance(ScanRecordInstanceEntity scanRecordInstanceEntity) {
        return jpaTemplate.save(scanRecordInstanceEntity,String.class);
    }

    /**
     * 更新
     * @param scanRecordInstanceEntity
     */
    public void updateScanRecordInstance(ScanRecordInstanceEntity scanRecordInstanceEntity){
        jpaTemplate.update(scanRecordInstanceEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanRecordInstance(String id){
        jpaTemplate.delete(ScanRecordInstanceEntity.class,id);
    }

    /**
     * 条件删除扫描记录实例
     * @param deleteCondition
     */
    public void deleteScanRecordInstance(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanRecordInstanceEntity findScanRecordInstance(String id){
        return jpaTemplate.findOne(ScanRecordInstanceEntity.class,id);
    }

    /**
    * 查询所有扫描记录实例
    * @return
    */
    public List<ScanRecordInstanceEntity> findAllScanRecordInstance() {
        return jpaTemplate.findAll(ScanRecordInstanceEntity.class);
    }

    /**
     * 通过ids查询扫描记录实例
     * @param idList
     * @return List <ScanRecordInstanceEntity>
     */
    public List<ScanRecordInstanceEntity> findScanRecordInstanceList(List<String> idList) {
        return jpaTemplate.findList(ScanRecordInstanceEntity.class,idList);
    }

    /**
     * 条件查询扫描记录实例
     * @param scanRecordInstanceQuery
     * @return List <ScanRecordInstanceEntity>
     */
    public List<ScanRecordInstanceEntity> findScanRecordInstanceList(ScanRecordInstanceQuery scanRecordInstanceQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanRecordInstanceEntity.class)
                .eq("scanRecordId",scanRecordInstanceQuery.getScanRecordId())
                .eq("scanPlayId",scanRecordInstanceQuery.getScanPlayId())
                .orders(scanRecordInstanceQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanRecordInstanceEntity.class);
    }

    /**
     * 条件分页查询扫描记录实例
     * @param scanRecordInstanceQuery
     * @return Pagination <ScanRecordInstanceEntity>
     */
    public Pagination<ScanRecordInstanceEntity> findScanRecordInstancePage(ScanRecordInstanceQuery scanRecordInstanceQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanRecordInstanceEntity.class)
                .eq("scanRecordId",scanRecordInstanceQuery.getScanRecordId())
                .eq("scanPlayId",scanRecordInstanceQuery.getScanPlayId())
                .orders(scanRecordInstanceQuery.getOrderParams())
                .pagination(scanRecordInstanceQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ScanRecordInstanceEntity.class);
    }
}