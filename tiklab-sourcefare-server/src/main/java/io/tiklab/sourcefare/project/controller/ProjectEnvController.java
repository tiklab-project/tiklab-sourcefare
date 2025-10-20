package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.ProjectEnv;
import io.tiklab.sourcefare.project.model.ProjectEnvQuery;
import io.tiklab.sourcefare.project.service.ProjectEnvService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
 * ProjectEnvController
 */
@RestController
@RequestMapping("/projectEnv")
//@Api(name = "ProjectEnvController",desc = "项目环境关联信息")
public class ProjectEnvController {

    private static Logger logger = LoggerFactory.getLogger(ProjectEnvController.class);

    @Autowired
    private ProjectEnvService projectEnvService;


    @RequestMapping(path="/createProjectEnv",method = RequestMethod.POST)
    @ApiMethod(name = "createProjectEnv",desc = "创建项目环境关联信息")
    @ApiParam(name = "projectEnv",desc = "projectEnv",required = true)
    public Result<String> createProjectEnv(@RequestBody @NotNull @Valid ProjectEnv projectEnv){
        String id = projectEnvService.createProjectEnv(projectEnv);

        return Result.ok(id);
    }

    @RequestMapping(path="/updateProjectEnv",method = RequestMethod.POST)
    @ApiMethod(name = "updateProjectEnv",desc = "修改项目环境关联信息")
    @ApiParam(name = "projectEnv",desc = "projectEnv",required = true)
    public Result<Void> updateProjectEnv(@RequestBody @NotNull @Valid ProjectEnv projectEnv){
        projectEnvService.updateProjectEnv(projectEnv);

        return Result.ok();
    }

    @RequestMapping(path="/deleteProjectEnv",method = RequestMethod.POST)
    @ApiMethod(name = "deleteProjectEnv",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteProjectEnv(@NotNull String id){
        projectEnvService.deleteProjectEnv(id);

        return Result.ok();
    }

    @RequestMapping(path="/findProjectEnv",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectEnv",desc = "通过id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ProjectEnv> findProjectEnv(@NotNull String id){
        ProjectEnv ProjectEnv = projectEnvService.findProjectEnv(id);

        return Result.ok(ProjectEnv);
    }



    @RequestMapping(path="/findAllProjectEnv",method = RequestMethod.POST)
    @ApiMethod(name = "findAllProjectEnv",desc = "查询所有查询")
    public Result<List<ProjectEnv>> findAllProjectEnv(){
        List<ProjectEnv> artifactList = projectEnvService.findAllProjectEnv();

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findProjectEnvList",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectEnvList",desc = "通过条件查询")
    @ApiParam(name = "projectEnvQuery",desc = "projectEnvQuery",required = true)
    public Result<List<ProjectEnv>> findProjectEnvList(@RequestBody @Valid @NotNull ProjectEnvQuery projectEnvQuery){
        List<ProjectEnv> artifactList = projectEnvService.findProjectEnvList(projectEnvQuery);

        return Result.ok(artifactList);
    }

}