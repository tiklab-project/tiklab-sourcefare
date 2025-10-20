package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ProjectCover;
import io.tiklab.sourcefare.scan.model.ProjectCoverQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ProjectCoverService-项目覆盖率
*/
@JoinProvider(model = ProjectCover.class)
public interface ProjectCoverService {

    /**
    * 创建
    * @param projectCover
    * @return
    */
    String createProjectCover(@NotNull @Valid ProjectCover projectCover);

    /**
    * 更新
    * @param projectCover
    */
    void updateProjectCover(@NotNull @Valid ProjectCover projectCover);

    /**
    * 删除
    * @param id
    */
    void deleteProjectCover(@NotNull String id);

    /**
     * 条件删除项目覆盖率
     * @param  key  删除条件字段
     * @param value
     */
    void deleteProjectCoverByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    ProjectCover findOne(@NotNull String id);

    @FindList
    List<ProjectCover> findList(List<String> idList);

    /**
    * 查找
    * @param id
    */

    ProjectCover findProjectCover(@NotNull String id);

    /**
    * 查找所有
    */
    @FindAll
    List<ProjectCover> findAllProjectCover();

    /**
    * 查询列表
    * @param projectCoverQuery  projectCoverQuery
    */
    List<ProjectCover> findProjectCoverList(ProjectCoverQuery projectCoverQuery);

    /**
    * 按分页查询
    * @param projectCoverQuery projectCoverQuery
    */
    Pagination<ProjectCover> findProjectCoverPage(ProjectCoverQuery projectCoverQuery);


}