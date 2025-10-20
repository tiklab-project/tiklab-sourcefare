package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.core.exception.SystemException;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.ProjectRepUpload;
import io.tiklab.sourcefare.project.model.ProjectRepUploadQuery;
import io.tiklab.sourcefare.project.service.ProjectRepUploadService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.io.IOException;
import java.io.InputStream;
import java.util.List;

/**
 * ProjectRepUploadController
 */
@RestController
@RequestMapping("/projectRepUpload")
//@Api(name = "ProjectRepUploadController",desc = "扫描项目上传代码信息")
public class ProjectRepUploadController {

    private static Logger logger = LoggerFactory.getLogger(ProjectRepUploadController.class);

    @Autowired
    private ProjectRepUploadService projectRepUploadService;


    @RequestMapping(path="/createProjectRepUpload",method = RequestMethod.POST)
    @ApiMethod(name = "createProjectRepUpload",desc = "创建扫描项目上传代码信息")
    @ApiParam(name = "projectRepUpload",desc = "projectRepUpload",required = true)
    public Result<String> createProjectRepUpload(@RequestBody @NotNull @Valid ProjectRepUpload projectRepUpload){
        String id = projectRepUploadService.createProjectRepUpload(projectRepUpload);

        return Result.ok(id);
    }

    @RequestMapping(path="/updateProjectRepUpload",method = RequestMethod.POST)
    @ApiMethod(name = "updateProjectRepUpload",desc = "修改扫描项目上传代码信息")
    @ApiParam(name = "projectRepUpload",desc = "projectRepUpload",required = true)
    public Result<Void> updateProjectRepUpload(@RequestBody @NotNull @Valid ProjectRepUpload projectRepUpload){
        projectRepUploadService.updateProjectRepUpload(projectRepUpload);

        return Result.ok();
    }

    @RequestMapping(path="/deleteProjectRepUpload",method = RequestMethod.POST)
    @ApiMethod(name = "deleteProjectRepUpload",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteProjectRepUpload(@NotNull String id){
        projectRepUploadService.deleteProjectRepUpload(id);

        return Result.ok();
    }

    @RequestMapping(path="/findProjectRepUpload",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectRepUpload",desc = "通过id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ProjectRepUpload> findProjectRepUpload(@NotNull String id){
        ProjectRepUpload ProjectRepUpload = projectRepUploadService.findProjectRepUpload(id);

        return Result.ok(ProjectRepUpload);
    }



    @RequestMapping(path="/findAllProjectRepUpload",method = RequestMethod.POST)
    @ApiMethod(name = "findAllProjectRepUpload",desc = "查询所有查询")
    public Result<List<ProjectRepUpload>> findAllProjectRepUpload(){
        List<ProjectRepUpload> artifactList = projectRepUploadService.findAllProjectRepUpload();

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findProjectRepUploadList",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectRepUploadList",desc = "通过条件查询")
    @ApiParam(name = "projectRepUploadQuery",desc = "projectRepUploadQuery",required = true)
    public Result<List<ProjectRepUpload>> findProjectRepUploadList(@RequestBody @Valid @NotNull ProjectRepUploadQuery projectRepUploadQuery){
        List<ProjectRepUpload> artifactList = projectRepUploadService.findProjectRepUploadList(projectRepUploadQuery);

        return Result.ok(artifactList);
    }


    @RequestMapping(path = "/findProjectRepUploadByRepId",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectRepUploadByRepId",desc = "通过项目id查询")
    @ApiParam(name = "projectId",desc = "projectId",required = true)
    public Result<ProjectRepUpload> findProjectRepUploadByRepId( @NotNull String projectId){
        ProjectRepUpload artifactList = projectRepUploadService.findProjectRepUploadByRepId(projectId);

        return Result.ok(artifactList);
    }

    @RequestMapping(path="/upload/**",method = RequestMethod.POST)
    @ApiMethod(name = "upload",desc = "文件上传")
    public Result<String> upload(@RequestParam("uploadFile") MultipartFile uploadFile,String projectId){
        String result = projectRepUploadService.upload(uploadFile,projectId);
        return Result.ok(result);
    }
}