package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.ProjectCoverEntity;
import io.tiklab.sourcefare.scan.model.ProjectCoverQuery;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ProjectCoverDao-项目覆盖率
 */
@Repository
public class ProjectCoverDao {

    private static Logger logger = LoggerFactory.getLogger(ProjectCoverDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param projectCoverEntity
     * @return
     */
    public String createProjectCover(ProjectCoverEntity projectCoverEntity) {
        return jpaTemplate.save(projectCoverEntity,String.class);
    }

    /**
     * 更新
     * @param projectCoverEntity
     */
    public void updateProjectCover(ProjectCoverEntity projectCoverEntity){
        jpaTemplate.update(projectCoverEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteProjectCover(String id){
        jpaTemplate.delete(ProjectCoverEntity.class,id);
    }

    /**
     * 条件删除项目覆盖率
     * @param deleteCondition
     */
    public void deleteProjectCover(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ProjectCoverEntity findProjectCover(String id){
        return jpaTemplate.findOne(ProjectCoverEntity.class,id);
    }

    /**
    * 查询所有项目覆盖率
    * @return
    */
    public List<ProjectCoverEntity> findAllProjectCover() {
        return jpaTemplate.findAll(ProjectCoverEntity.class);
    }

    /**
     * 通过ids项目覆盖率
     * @param idList
     * @return List <ProjectCoverEntity>
     */
    public List<ProjectCoverEntity> findProjectCoverList(List<String> idList) {
        return jpaTemplate.findList(ProjectCoverEntity.class,idList);
    }

    /**
     * 条件查询项目覆盖率
     * @param projectCoverQuery
     * @return List <ProjectCoverEntity>
     */
    public List<ProjectCoverEntity> findProjectCoverList(ProjectCoverQuery projectCoverQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectCoverEntity.class)
                .eq("scanRecordId",projectCoverQuery.getScanRecordId())
                .eq("projectId",projectCoverQuery.getProjectId())
                .eq("name",projectCoverQuery.getName())
                .eq("type",projectCoverQuery.getType())
                .eq("parentPath",projectCoverQuery.getParentPath())
                .orders(projectCoverQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, ProjectCoverEntity.class);
    }

    /**
     * 条件分页查询项目覆盖率
     * @param coverQuery
     * @return Pagination <ProjectCoverEntity>
     */
    public Pagination<ProjectCoverEntity> findProjectCoverPage(ProjectCoverQuery coverQuery) {
        QueryBuilders builders = QueryBuilders.createQuery(ProjectCoverEntity.class)
                .eq("scanRecordId", coverQuery.getScanRecordId())
                .eq("projectId", coverQuery.getProjectId())
                .eq("name", coverQuery.getName());

        //如果父级的路径为空，查询第一级数据
        if (StringUtils.isBlank(coverQuery.getParentPath())){
            builders.eq("type","package");
        }else {
            builders.eq("parentPath",coverQuery.getParentPath());
        }

        QueryCondition queryCondition = builders.orders(coverQuery.getOrderParams())
                .pagination(coverQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, ProjectCoverEntity.class);
    }


}