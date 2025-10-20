package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ScanSchemeEntity;
import io.tiklab.sourcefare.scan.model.ScanSchemeQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ScanSchemeDao-扫描结果数据库访问
 */
@Repository
public class ScanShemeDao {

    private static Logger logger = LoggerFactory.getLogger(ScanShemeDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanSchemeEntity
     * @return
     */
    public String createScanScheme(ScanSchemeEntity scanSchemeEntity) {
        return jpaTemplate.save(scanSchemeEntity,String.class);
    }

    /**
     * 更新
     * @param scanSchemeEntity
     */
    public void updateScanScheme(ScanSchemeEntity scanSchemeEntity){
        jpaTemplate.update(scanSchemeEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanScheme(String id){
        jpaTemplate.delete(ScanSchemeEntity.class,id);
    }

    /**
     * 条件删除存储库
     * @param deleteCondition
     */
    public void deleteScanScheme(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ScanSchemeEntity findScanScheme(String id){
        return jpaTemplate.findOne(ScanSchemeEntity.class,id);
    }

    /**
    * 查询所有存储库
    * @return
    */
    public List<ScanSchemeEntity> findAllScanScheme() {
        return jpaTemplate.findAll(ScanSchemeEntity.class);
    }

    /**
     * 通过ids查询存储库
     * @param idList
     * @return List <ScanSchemeEntity>
     */
    public List<ScanSchemeEntity> findScanSchemeList(List<String> idList) {
        return jpaTemplate.findList(ScanSchemeEntity.class,idList);
    }

    /**
     * 条件查询存储库
     * @param scanSchemeQuery
     * @return List <ScanSchemeEntity>
     */
    public List<ScanSchemeEntity> findScanSchemeList(ScanSchemeQuery scanSchemeQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanSchemeEntity.class)
                .eq("category",scanSchemeQuery.getCategory())
                .eq("language",scanSchemeQuery.getLanguage())
                .orders(scanSchemeQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ScanSchemeEntity.class);
    }

    /**
     * 条件分页查询存储库
     * @param scanSchemeQuery
     * @return Pagination <ScanSchemeEntity>
     */
    public Pagination<ScanSchemeEntity> findScanSchemePage(ScanSchemeQuery scanSchemeQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ScanSchemeEntity.class)
                .eq("category",scanSchemeQuery.getCategory())
                .eq("language",scanSchemeQuery.getLanguage())
                .orders(scanSchemeQuery.getOrderParams())
                .pagination(scanSchemeQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ScanSchemeEntity.class);
    }
}