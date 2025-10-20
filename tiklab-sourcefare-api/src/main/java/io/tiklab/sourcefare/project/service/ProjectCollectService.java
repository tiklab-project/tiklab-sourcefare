package io.tiklab.sourcefare.project.service;

import io.tiklab.sourcefare.project.model.ProjectCollect;
import io.tiklab.sourcefare.project.model.ProjectCollectQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ProjectCollectService-项目收藏信息
*/
@JoinProvider(model = ProjectCollect.class)
public interface ProjectCollectService {

    /**
    * 创建
    * @param projectCollect
    * @return
    */
    String createProjectCollect(@NotNull @Valid ProjectCollect projectCollect);


    /**
    * 更新
    * @param projectCollect
    */
    void updateProjectCollect(@NotNull @Valid ProjectCollect projectCollect);

    /**
    * 删除
    * @param id
    */
    void deleteProjectCollect(@NotNull String id);

    /**
     * 删除
     * @param projectId 项目id
     * @param userId 用户id
     */
    void deleteCollect(@NotNull String projectId,@NotNull String userId);

    /**
     * 条件删除
     * @param type
     */
    void deleteProjectCollectByRecord(String type,String data);

    @FindOne
    ProjectCollect findOne(@NotNull String id);
    @FindList
    List<ProjectCollect> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */
    ProjectCollect findProjectCollect(@NotNull String id);

    /**
     * 通过仓库的ids查询收藏
     * @param projectIds 项目ids
     * @param  userId 用户
     */
    List<ProjectCollect> findRepositoryCollectList(String[] projectIds,String userId);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ProjectCollect> findAllProjectCollect();

    /**
    * 查询列表
    * @param projectCollectQuery
    * @return
    */
    List<ProjectCollect> findProjectCollectList(ProjectCollectQuery projectCollectQuery);




}