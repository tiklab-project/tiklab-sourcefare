package io.tiklab.sourcefare.project.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.project.entity.ProjectRepEntity;
import io.tiklab.sourcefare.project.model.ProjectRepQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ProjectRepDao-代码仓库信息
 */
@Repository
public class ProjectRepDao {

    private static Logger logger = LoggerFactory.getLogger(ProjectRepDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param projectRepEntity
     * @return
     */
    public String createProjectRep(ProjectRepEntity projectRepEntity) {
        return jpaTemplate.save(projectRepEntity,String.class);
    }

    /**
     * 更新
     * @param projectRepEntity
     */
    public void updateProjectRep(ProjectRepEntity projectRepEntity){
        jpaTemplate.update(projectRepEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteProjectRep(String id){
        jpaTemplate.delete(ProjectRepEntity.class,id);
    }

    public void deleteProjectRep(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ProjectRepEntity findProjectRep(String id){
        return jpaTemplate.findOne(ProjectRepEntity.class,id);
    }

    /**
    * findAllProjectRep
    * @return
    */
    public List<ProjectRepEntity> findAllProjectRep() {
        return jpaTemplate.findAll(ProjectRepEntity.class);
    }

    /**
     * 通过ids查询
     * @param idList
     * @return
     */
    public List<ProjectRepEntity> findProjectRepList(List<String> idList) {
        return jpaTemplate.findList(ProjectRepEntity.class,idList);
    }

    /**
     * 条件查询代码仓库信息
     * @param projectRepQuery
     * @return
     */
    public List<ProjectRepEntity> findProjectRepList(ProjectRepQuery projectRepQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectRepEntity.class)
                .eq("projectId", projectRepQuery.getProjectId())
                .get();
        return jpaTemplate.findList(queryCondition, ProjectRepEntity.class);
    }

    /**
     * 条件分页查询代码仓库信息
     * @param projectRepQuery
     * @return
     */
    public Pagination<ProjectRepEntity> findProjectRepPage(ProjectRepQuery projectRepQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectRepEntity.class)
                .eq("projectId", projectRepQuery.getProjectId())
                .get();
        return jpaTemplate.findPage(queryCondition, ProjectRepEntity.class);
    }

}