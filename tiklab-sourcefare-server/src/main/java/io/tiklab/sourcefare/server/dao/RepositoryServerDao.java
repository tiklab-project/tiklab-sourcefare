package io.tiklab.sourcefare.server.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.server.entity.RepositoryServerEntity;
import io.tiklab.sourcefare.server.model.RepositoryServerQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * RepositoryServerDao-仓库服务
 */
@Repository
public class RepositoryServerDao {

    private static Logger logger = LoggerFactory.getLogger(RepositoryServerDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param RepositoryServerEntity
     * @return
     */
    public String createRepositoryServer(RepositoryServerEntity RepositoryServerEntity) {
        return jpaTemplate.save(RepositoryServerEntity,String.class);
    }

    /**
     * 更新
     * @param RepositoryServerEntity
     */
    public void updateRepositoryServer(RepositoryServerEntity RepositoryServerEntity){
        jpaTemplate.update(RepositoryServerEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteRepositoryServer(String id){
        jpaTemplate.delete(RepositoryServerEntity.class,id);
    }

    public void deleteRepositoryServer(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     */
    public RepositoryServerEntity findRepositoryServer(String id){
        return jpaTemplate.findOne(RepositoryServerEntity.class,id);
    }

    /**
    * findAllRepositoryServer
    */
    public List<RepositoryServerEntity> findAllRepositoryServer() {
        return jpaTemplate.findAll(RepositoryServerEntity.class);
    }

    /**
     * 通过ids查询
     * @param idList
     * @return
     */
    public List<RepositoryServerEntity> findRepositoryServerList(List<String> idList) {
        return jpaTemplate.findList(RepositoryServerEntity.class,idList);
    }

    /**
     * 条件查询
     * @param RepositoryServerQuery RepositoryServerQuery
     */
    public List<RepositoryServerEntity> findRepositoryServerList(RepositoryServerQuery RepositoryServerQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RepositoryServerEntity.class)
                .eq("userId", RepositoryServerQuery.getUserId())
                .get();
        return jpaTemplate.findList(queryCondition, RepositoryServerEntity.class);
    }
    /**
     * 条件分页查询
     * @param RepositoryServerQuery  RepositoryServerQuery
     */
    public Pagination<RepositoryServerEntity> findRepositoryServerPage(RepositoryServerQuery RepositoryServerQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RepositoryServerEntity.class)
                .eq("userId", RepositoryServerQuery.getUserId())
                .pagination(RepositoryServerQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, RepositoryServerEntity.class);
    }


}