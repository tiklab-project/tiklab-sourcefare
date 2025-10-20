package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.ProjectRep;
import io.tiklab.sourcefare.project.model.ProjectRepQuery;
import io.tiklab.sourcefare.project.service.ProjectRepService;
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
 * ProjectRepController
 */
@RestController
@RequestMapping("/projectRep")
//@Api(name = "ProjectRepController",desc = "打开仓库的记录管理")
public class ProjectRepController {

    private static Logger logger = LoggerFactory.getLogger(ProjectRepController.class);

    @Autowired
    private ProjectRepService projectRepService;

    @RequestMapping(path="/createProjectRep",method = RequestMethod.POST)
    @ApiMethod(name = "createProjectRep",desc = "创建代码仓库信息")
    @ApiParam(name = "projectRep",desc = "projectRep",required = true)
    public Result<String> createProjectRep(@RequestBody @NotNull @Valid ProjectRep projectRep){
        String id = projectRepService.createProjectRep(projectRep);

        return Result.ok(id);
    }

    @RequestMapping(path="/updateProjectRep",method = RequestMethod.POST)
    @ApiMethod(name = "updateProjectRep",desc = "修改代码仓库信息")
    @ApiParam(name = "projectRep",desc = "projectRep",required = true)
    public Result<Void> updateProjectRep(@RequestBody @NotNull @Valid ProjectRep projectRep){
        projectRepService.updateProjectRep(projectRep);

        return Result.ok();
    }

    @RequestMapping(path="/deleteProjectRep",method = RequestMethod.POST)
    @ApiMethod(name = "deleteProjectRep",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteProjectRep(@NotNull String id){
        projectRepService.deleteProjectRep(id);

        return Result.ok();
    }

    @RequestMapping(path="/findProjectRep",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectRep",desc = "通过id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ProjectRep> findProjectRep(@NotNull String id){
        ProjectRep ProjectRep = projectRepService.findProjectRep(id);

        return Result.ok(ProjectRep);
    }

    @RequestMapping(path="/findProjectRepByProjectId",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectRepByProjectId",desc = "通过项目id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ProjectRep> findProjectRepByProjectId(@NotNull String projectId){
        ProjectRep ProjectRep = projectRepService.findProjectRepByProjectId(projectId);

        return Result.ok(ProjectRep);
    }


    @RequestMapping(path="/findAllProjectRep",method = RequestMethod.POST)
    @ApiMethod(name = "findAllProjectRep",desc = "查询所有查询")
    public Result<List<ProjectRep>> findAllProjectRep(){
        List<ProjectRep> artifactList = projectRepService.findAllProjectRep();

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findProjectRepList",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectRepList",desc = "通过条件查询")
    @ApiParam(name = "projectRepQuery",desc = "projectRepQuery",required = true)
    public Result<List<ProjectRep>> findProjectRepList(@RequestBody @Valid @NotNull ProjectRepQuery projectRepQuery){
        List<ProjectRep> artifactList = projectRepService.findProjectRepList(projectRepQuery);

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findProjectRepPage",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectRepPage",desc = "通过条件分页查询")
    @ApiParam(name = "projectRepQuery",desc = "projectRepQuery",required = true)
    public Result<Pagination<ProjectRep>> findProjectRepPage(@RequestBody @Valid @NotNull ProjectRepQuery projectRepQuery){
        Pagination<ProjectRep> pagination = projectRepService.findProjectRepPage(projectRepQuery);

        return Result.ok(pagination);
    }



}
