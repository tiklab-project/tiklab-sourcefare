package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanDoorEntity;
import io.tiklab.sourcefare.scan.model.ScanDoor;
import io.tiklab.sourcefare.scan.model.ScanDoorQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BatchPreparedStatementSetter;
import org.springframework.stereotype.Repository;

import java.sql.SQLException;
import java.util.List;

/**
 * ScanDoorDao-扫描门禁数据库访问
 */
@Repository
public class ScanDoorDao {

    private static Logger logger = LoggerFactory.getLogger(ScanDoorDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanDoorEntity
     * @return
     */
    public String createScanDoor(ScanDoorEntity scanDoorEntity) {
        return jpaTemplate.save(scanDoorEntity,String.class);
    }

    /**
     * 更新
     * @param scanDoorEntity
     */
    public void updateScanDoor(ScanDoorEntity scanDoorEntity){
        jpaTemplate.update(scanDoorEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanDoor(String id){
        jpaTemplate.delete(ScanDoorEntity.class,id);
    }

    /**
     * 条件删除存储库
     * @param deleteCondition
     */
    public void deleteScanDoor(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanDoorEntity findScanDoor(String id){
        return jpaTemplate.findOne(ScanDoorEntity.class,id);
    }

    /**
    * 查询所有存储库
    * @return
    */
    public List<ScanDoorEntity> findAllScanDoor() {
        return jpaTemplate.findAll(ScanDoorEntity.class);
    }

    /**
     * 通过ids查询存储库
     * @param idList
     * @return List <ScanDoorEntity>
     */
    public List<ScanDoorEntity> findScanDoorList(List<String> idList) {
        return jpaTemplate.findList(ScanDoorEntity.class,idList);
    }

    /**
     * 条件查询存储库
     * @param scanDoorQuery
     * @return List <ScanDoorEntity>
     */
    public List<ScanDoorEntity> findScanDoorList(ScanDoorQuery scanDoorQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanDoorEntity.class)
                .eq("projectId",scanDoorQuery.getProjectId())
                .orders(scanDoorQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanDoorEntity.class);
    }


}