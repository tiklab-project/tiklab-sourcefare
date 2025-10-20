package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ProjectCoverGo;
import io.tiklab.sourcefare.scan.model.ProjectCoverGoQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ProjectCoverGoService-go项目覆盖率
*/
@JoinProvider(model = ProjectCoverGo.class)
public interface ProjectCoverGoService {

    /**
    * 创建
    * @param projectCoverGo
    * @return
    */
    String createProjectCoverGo(@NotNull @Valid ProjectCoverGo projectCoverGo);

    /**
    * 更新
    * @param projectCoverGo
    */
    void updateProjectCoverGo(@NotNull @Valid ProjectCoverGo projectCoverGo);

    /**
    * 删除
    * @param id
    */
    void deleteProjectCoverGo(@NotNull String id);

    /**
     * 条件删除go项目覆盖率
     * @param  key  删除条件字段
     * @param value
     */
    void deleteProjectCoverGoByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    ProjectCoverGo findOne(@NotNull String id);

    @FindList
    List<ProjectCoverGo> findList(List<String> idList);

    /**
    * 查找
    * @param id
    */

    ProjectCoverGo findProjectCoverGo(@NotNull String id);

    /**
    * 查找所有
    */
    @FindAll
    List<ProjectCoverGo> findAllProjectCoverGo();

    /**
    * 查询列表
    * @param projectCoverGoQuery  projectCoverGoQuery
    */
    List<ProjectCoverGo> findProjectCoverGoList(ProjectCoverGoQuery projectCoverGoQuery);

    /**
    * 按分页查询
    * @param projectCoverGoQuery projectCoverGoQuery
    */
    Pagination<ProjectCoverGo> findProjectCoverGoPage(ProjectCoverGoQuery projectCoverGoQuery);


}