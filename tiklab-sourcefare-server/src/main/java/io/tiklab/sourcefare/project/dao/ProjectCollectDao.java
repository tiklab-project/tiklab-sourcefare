package io.tiklab.sourcefare.project.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.project.entity.ProjectCollectEntity;
import io.tiklab.sourcefare.project.entity.ProjectEnvEntity;
import io.tiklab.sourcefare.project.model.ProjectCollectQuery;
import org.apache.commons.lang3.ObjectUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ProjectCollectDao-项目收藏信息
 */
@Repository
public class ProjectCollectDao {

    private static Logger logger = LoggerFactory.getLogger(ProjectCollectDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param projectCollectEntity
     * @return
     */
    public String createProjectCollect(ProjectCollectEntity projectCollectEntity) {
        return jpaTemplate.save(projectCollectEntity,String.class);
    }

    /**
     * 更新
     * @param projectCollectEntity
     */
    public void updateProjectCollect(ProjectCollectEntity projectCollectEntity){
        jpaTemplate.update(projectCollectEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteProjectCollect(String id){
        jpaTemplate.delete(ProjectCollectEntity.class,id);
    }

    /**
     * 删除
     * @param projectId 项目id
     * @param userId userId
     */
    public void deleteCollect(String projectId, String userId){
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ProjectCollectEntity.class)
                .eq("projectId", projectId)
                .eq("userId",userId)
                .get();
        jpaTemplate.delete(deleteCondition);
    }

    public void deleteProjectCollect(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ProjectCollectEntity findProjectCollect(String id){
        return jpaTemplate.findOne(ProjectCollectEntity.class,id);
    }

    /**
    * findAllProjectCollect
    * @return
    */
    public List<ProjectCollectEntity> findAllProjectCollect() {
        return jpaTemplate.findAll(ProjectCollectEntity.class);
    }

    /**
     * 通过ids查询
     * @param idList
     * @return
     */
    public List<ProjectCollectEntity> findProjectCollectList(List<String> idList) {
        return jpaTemplate.findList(ProjectCollectEntity.class,idList);
    }

    /**
     * 条件查询项目收藏信息
     * @param projectCollectQuery
     * @return
     */
    public List<ProjectCollectEntity> findProjectCollectList(ProjectCollectQuery projectCollectQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectCollectEntity.class)
                .eq("projectId", projectCollectQuery.getProjectId())
                .eq("userId",projectCollectQuery.getUserId())
                .get();
        return jpaTemplate.findList(queryCondition, ProjectCollectEntity.class);
    }

    /**
     * 条件分页查询项目收藏信息
     * @param projectCollectQuery
     * @return
     */
    public Pagination<ProjectCollectEntity> findProjectCollectPage(ProjectCollectQuery projectCollectQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectCollectEntity.class)
                .eq("projectId", projectCollectQuery.getProjectId())
                .eq("userId",projectCollectQuery.getUserId())
                .get();
        return jpaTemplate.findPage(queryCondition, ProjectCollectEntity.class);
    }


    /**
     * 通过projectIds查询
     * @param projectIds 项目ids
     * @param userId 用户id
     */
    public List<ProjectCollectEntity> findProjectCollectList(String[] projectIds,String userId) {
        QueryBuilders queryBuilders = QueryBuilders.createQuery(ProjectCollectEntity.class)
                .eq("userId", userId);
        if (ObjectUtils.isNotEmpty(projectIds)){
            queryBuilders.in("projectId", projectIds);
        }
        QueryCondition queryCondition = queryBuilders.get();
        return jpaTemplate.findList(queryCondition, ProjectCollectEntity.class);
    }

}