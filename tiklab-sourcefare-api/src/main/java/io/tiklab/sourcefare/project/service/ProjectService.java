package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.project.model.ProjectQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.constraints.NotNull;
import java.util.List;

@JoinProvider(model = Project.class)
public interface ProjectService {


    /**
     * 创建项目
     * @param project 信息
     * @return 项目id
     */
    String createProject(Project project);

    /**
     * 删除项目
     * @param codeGroupId 项目id
     */
    void deleteProject(String codeGroupId);

    /**
     * 更新项目
     * @param project 项目信息
     */
    void updateProject(Project project);

    @FindOne
    Project findOne(@NotNull String id);


    /**
     * 查询单个项目
     * @param id id
     * @return 项目信息
     */
    Project findProject(@NotNull String id);

    /**
     * 查询所有项目
     * @return 项目信息列表
     */
    @FindAll
    List<Project> findAllProject();


    @FindList
    List<Project> findList(List<String> idList);

    /**
     * 分页查询项目
     * @param projectQuery projectQuery
     */
    Pagination<Project> findProjectPage(ProjectQuery projectQuery);

    /**
     * 查询项目
     * @param projectQuery projectQuery
     */
    List<Project> findProjectList(ProjectQuery projectQuery);

}





















