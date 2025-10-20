package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ProjectCoverGoEntity;
import io.tiklab.sourcefare.scan.model.ProjectCoverGoQuery;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ProjectCoverGoDao-go项目覆盖率
 */
@Repository
public class ProjectCoverGoDao {

    private static Logger logger = LoggerFactory.getLogger(ProjectCoverGoDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param projectCoverGoEntity
     * @return
     */
    public String createProjectCoverGo(ProjectCoverGoEntity projectCoverGoEntity) {
        return jpaTemplate.save(projectCoverGoEntity,String.class);
    }

    /**
     * 更新
     * @param projectCoverGoEntity
     */
    public void updateProjectCoverGo(ProjectCoverGoEntity projectCoverGoEntity){
        jpaTemplate.update(projectCoverGoEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteProjectCoverGo(String id){
        jpaTemplate.delete(ProjectCoverGoEntity.class,id);
    }

    /**
     * 条件删除项目覆盖率
     * @param deleteCondition
     */
    public void deleteProjectCoverGo(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ProjectCoverGoEntity findProjectCoverGo(String id){
        return jpaTemplate.findOne(ProjectCoverGoEntity.class,id);
    }

    /**
    * 查询所有项目覆盖率
    * @return
    */
    public List<ProjectCoverGoEntity> findAllProjectCoverGo() {
        return jpaTemplate.findAll(ProjectCoverGoEntity.class);
    }

    /**
     * 通过ids项目覆盖率
     * @param idList
     * @return List <ProjectCoverGoEntity>
     */
    public List<ProjectCoverGoEntity> findProjectCoverGoList(List<String> idList) {
        return jpaTemplate.findList(ProjectCoverGoEntity.class,idList);
    }

    /**
     * 条件查询项目覆盖率
     * @param projectCoverGoQuery
     * @return List <ProjectCoverGoEntity>
     */
    public List<ProjectCoverGoEntity> findProjectCoverGoList(ProjectCoverGoQuery projectCoverGoQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectCoverGoEntity.class)
                .eq("scanRecordId",projectCoverGoQuery.getScanRecordId())
                .eq("projectId",projectCoverGoQuery.getProjectId())
                .orders(projectCoverGoQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ProjectCoverGoEntity.class);
    }

    /**
     * 条件分页查询项目覆盖率
     * @param coverQuery
     * @return Pagination <ProjectCoverGoEntity>
     */
    public Pagination<ProjectCoverGoEntity> findProjectCoverGoPage(ProjectCoverGoQuery coverQuery) {
        QueryCondition queryCondition =  QueryBuilders.createQuery(ProjectCoverGoEntity.class)
                .eq("scanRecordId", coverQuery.getScanRecordId())
                .eq("projectId", coverQuery.getProjectId())
                .orders(coverQuery.getOrderParams())
                .pagination(coverQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ProjectCoverGoEntity.class);
    }


}