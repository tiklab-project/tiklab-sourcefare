package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.project.model.ProjectEnv;
import io.tiklab.sourcefare.project.model.ProjectEnvQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ProjectEnvService-项目环境关联信息
*/
@JoinProvider(model = ProjectEnv.class)
public interface ProjectEnvService {

    /**
    * 创建
    * @param projectEnv
    * @return
    */
    String createProjectEnv(@NotNull @Valid ProjectEnv projectEnv);

    /**
     * 创建
     * @param projectId projectId
     * @param envId envId
     */
    String createProjectEnv(String projectId,String envId,String type);

    /**
    * 更新
    * @param projectEnv
    */
    void updateProjectEnv(@NotNull @Valid ProjectEnv projectEnv);

    /**
    * 删除
    * @param id
    */
    void deleteProjectEnv(@NotNull String id);

    /**
     * 条件删除
     * @param type
     */
    void deleteProjectEnvByRecord(String type,String data);

    @FindOne
    ProjectEnv findOne(@NotNull String id);
    @FindList
    List<ProjectEnv> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */
    ProjectEnv findProjectEnv(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ProjectEnv> findAllProjectEnv();

    /**
    * 查询列表
    * @param projectEnvQuery
    * @return
    */
    List<ProjectEnv> findProjectEnvList(ProjectEnvQuery projectEnvQuery);




}