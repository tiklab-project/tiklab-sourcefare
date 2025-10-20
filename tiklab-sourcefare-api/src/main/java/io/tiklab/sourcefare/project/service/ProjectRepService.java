package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.project.model.ProjectRep;
import io.tiklab.sourcefare.project.model.ProjectRepQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ProjectRepService-扫描项目 代码仓库信息
*/
@JoinProvider(model = ProjectRep.class)
public interface ProjectRepService {

    /**
    * 创建
    * @param recordCommit
    * @return
    */
    String createProjectRep(@NotNull @Valid ProjectRep recordCommit);

    /**
    * 更新
    * @param recordCommit
    */
    void updateProjectRep(@NotNull @Valid ProjectRep recordCommit);

    /**
    * 删除
    * @param id
    */
    void deleteProjectRep(@NotNull String id);

    /**
     * 条件删除
     * @param type
     */
    void deleteProjectRepByRecord(String type,String data);

    @FindOne
    ProjectRep findOne(@NotNull String id);
    @FindList
    List<ProjectRep> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */
    ProjectRep findProjectRep(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ProjectRep> findAllProjectRep();

    /**
    * 查询列表
    * @param projectRepQuery
    * @return
    */
    List<ProjectRep> findProjectRepList(ProjectRepQuery projectRepQuery);

    /**
    * 按分页查询
    * @param projectRepQuery
    * @return
    */
    Pagination<ProjectRep> findProjectRepPage(ProjectRepQuery projectRepQuery);

    /**
     * 通过项目id 查询
     * @param projectId
     * @return
     */
    ProjectRep findProjectRepByProjectId(String projectId);
}