package io.tiklab.sourcefare.project.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.project.entity.ProjectEnvEntity;
import io.tiklab.sourcefare.project.model.ProjectEnvQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ProjectEnvDao-项目环境关联信息
 */
@Repository
public class ProjectEnvDao {

    private static Logger logger = LoggerFactory.getLogger(ProjectEnvDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param projectEnvEntity
     * @return
     */
    public String createProjectEnv(ProjectEnvEntity projectEnvEntity) {
        return jpaTemplate.save(projectEnvEntity,String.class);
    }

    /**
     * 更新
     * @param projectEnvEntity
     */
    public void updateProjectEnv(ProjectEnvEntity projectEnvEntity){
        jpaTemplate.update(projectEnvEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteProjectEnv(String id){
        jpaTemplate.delete(ProjectEnvEntity.class,id);
    }

    public void deleteProjectEnv(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ProjectEnvEntity findProjectEnv(String id){
        return jpaTemplate.findOne(ProjectEnvEntity.class,id);
    }

    /**
    * findAllProjectEnv
    * @return
    */
    public List<ProjectEnvEntity> findAllProjectEnv() {
        return jpaTemplate.findAll(ProjectEnvEntity.class);
    }

    /**
     * 通过ids查询
     * @param idList
     * @return
     */
    public List<ProjectEnvEntity> findProjectEnvList(List<String> idList) {
        return jpaTemplate.findList(ProjectEnvEntity.class,idList);
    }

    /**
     * 条件查询项目环境关联信息
     * @param projectEnvQuery
     * @return
     */
    public List<ProjectEnvEntity> findProjectEnvList(ProjectEnvQuery projectEnvQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectEnvEntity.class)
                .eq("projectId", projectEnvQuery.getProjectId())
                .get();
        return jpaTemplate.findList(queryCondition, ProjectEnvEntity.class);
    }

    /**
     * 条件分页查询项目环境关联信息
     * @param projectEnvQuery
     * @return
     */
    public Pagination<ProjectEnvEntity> findProjectEnvPage(ProjectEnvQuery projectEnvQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectEnvEntity.class)
                .eq("projectId", projectEnvQuery.getProjectId())
                .get();
        return jpaTemplate.findPage(queryCondition, ProjectEnvEntity.class);
    }

}