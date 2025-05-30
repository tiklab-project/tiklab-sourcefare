package io.tiklab.sourcefare.project.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.project.entity.ProjectEntity;
import io.tiklab.sourcefare.project.model.ProjectQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ProjectDao-项目
 */
@Repository
public class ProjectDao {

    private static Logger logger = LoggerFactory.getLogger(ProjectDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param projectEntity
     * @return
     */
    public String createProject(ProjectEntity projectEntity) {
        return jpaTemplate.save(projectEntity,String.class);
    }

    /**
     * 更新
     * @param projectEntity
     */
    public void updateProject(ProjectEntity projectEntity){
        jpaTemplate.update(projectEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteProject(String id){
        jpaTemplate.delete(ProjectEntity.class,id);
    }

    public void deleteProject(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     */
    public ProjectEntity findProject(String id){
        return jpaTemplate.findOne(ProjectEntity.class,id);
    }

    /**
    * findAllProject
    */
    public List<ProjectEntity> findAllProject() {
        return jpaTemplate.findAll(ProjectEntity.class);
    }

    /**
     * 通过ids查询
     * @param idList
     * @return
     */
    public List<ProjectEntity> findProjectList(List<String> idList) {
        return jpaTemplate.findList(ProjectEntity.class,idList);
    }

    /**
     * 条件查询
     * @param projectQuery projectQuery
     */
    public List<ProjectEntity> findProjectList(ProjectQuery projectQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectEntity.class)
                .eq("userId", projectQuery.getUserId())
                .get();
        return jpaTemplate.findList(queryCondition, ProjectEntity.class);
    }
    /**
     * 条件分页查询
     * @param projectQuery  projectQuery
     */
    public Pagination<ProjectEntity> findProjectPage(ProjectQuery projectQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectEntity.class)
                .eq("userId", projectQuery.getUserId())
                .pagination(projectQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ProjectEntity.class);
    }


}