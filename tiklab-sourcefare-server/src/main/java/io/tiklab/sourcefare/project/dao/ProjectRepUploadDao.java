package io.tiklab.sourcefare.project.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.project.entity.ProjectRepUploadEntity;
import io.tiklab.sourcefare.project.model.ProjectRepUploadQuery;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * ProjectRepUploadDao-扫描项目上传代码信息
 */
@Repository
public class ProjectRepUploadDao {

    private static Logger logger = LoggerFactory.getLogger(ProjectRepUploadDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param projectRepUploadEntity
     * @return
     */
    public String createProjectRepUpload(ProjectRepUploadEntity projectRepUploadEntity) {
        return jpaTemplate.save(projectRepUploadEntity,String.class);
    }

    /**
     * 更新
     * @param projectRepUploadEntity
     */
    public void updateProjectRepUpload(ProjectRepUploadEntity projectRepUploadEntity){
        jpaTemplate.update(projectRepUploadEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteProjectRepUpload(String id){
        jpaTemplate.delete(ProjectRepUploadEntity.class,id);
    }

    public void deleteProjectRepUpload(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public ProjectRepUploadEntity findProjectRepUpload(String id){
        return jpaTemplate.findOne(ProjectRepUploadEntity.class,id);
    }

    /**
    * findAllProjectRepUpload
    * @return
    */
    public List<ProjectRepUploadEntity> findAllProjectRepUpload() {
        return jpaTemplate.findAll(ProjectRepUploadEntity.class);
    }

    /**
     * 通过ids查询
     * @param idList
     * @return
     */
    public List<ProjectRepUploadEntity> findProjectRepUploadList(List<String> idList) {
        return jpaTemplate.findList(ProjectRepUploadEntity.class,idList);
    }

    /**
     * 条件查询扫描项目上传代码信息
     * @param projectRepUploadQuery
     * @return
     */
    public List<ProjectRepUploadEntity> findProjectRepUploadList(ProjectRepUploadQuery projectRepUploadQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectRepUploadEntity.class)
                .eq("projectId", projectRepUploadQuery.getProjectId())
                .get();
        return jpaTemplate.findList(queryCondition, ProjectRepUploadEntity.class);
    }

    /**
     * 条件分页查询扫描项目上传代码信息
     * @param projectRepUploadQuery
     * @return
     */
    public Pagination<ProjectRepUploadEntity> findProjectRepUploadPage(ProjectRepUploadQuery projectRepUploadQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(ProjectRepUploadEntity.class)
                .eq("projectId", projectRepUploadQuery.getProjectId())
                .get();
        return jpaTemplate.findPage(queryCondition, ProjectRepUploadEntity.class);
    }

}