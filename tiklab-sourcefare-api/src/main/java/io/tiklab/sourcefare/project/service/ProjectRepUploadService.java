package io.tiklab.sourcefare.project.service;

import io.tiklab.sourcefare.project.model.ProjectRepUpload;
import io.tiklab.sourcefare.project.model.ProjectRepUploadQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.io.InputStream;
import java.util.List;

/**
* ProjectRepUploadService-扫描项目上传代码信息
*/
@JoinProvider(model = ProjectRepUpload.class)
public interface ProjectRepUploadService {

    /**
    * 创建
    * @param projectRepUpload
    * @return
    */
    String createProjectRepUpload(@NotNull @Valid ProjectRepUpload projectRepUpload);


    /**
    * 更新
    * @param projectRepUpload
    */
    void updateProjectRepUpload(@NotNull @Valid ProjectRepUpload projectRepUpload);

    /**
    * 删除
    * @param id
    */
    void deleteProjectRepUpload(@NotNull String id);

    /**
     * 条件删除
     * @param type
     */
    void deleteProjectRepUploadByRecord(String type,String data);

    @FindOne
    ProjectRepUpload findOne(@NotNull String id);
    @FindList
    List<ProjectRepUpload> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */
    ProjectRepUpload findProjectRepUpload(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ProjectRepUpload> findAllProjectRepUpload();

    /**
    * 查询列表
    * @param projectRepUploadQuery
    * @return
    */
    List<ProjectRepUpload> findProjectRepUploadList(ProjectRepUploadQuery projectRepUploadQuery);

    /**
     * 通过项目id查询上传的代码信息
     * @param projectId 项目id
     * @return
     */
    ProjectRepUpload findProjectRepUploadByRepId(String projectId);

    /**
     * 通过项目id查询上传的代码信息
     * @param uploadFile uploadFile
     * @param  projectId  项目id
     */
    String upload(MultipartFile uploadFile, String projectId);
}