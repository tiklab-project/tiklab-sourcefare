package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.project.model.ProjectQuery;
import io.tiklab.sourcefare.project.service.ProjectService;
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
 * ProjectController
 */
@RestController
@RequestMapping("/project")
@Api(name = "ProjectController",desc = "项目")
public class ProjectController {

    private static Logger logger = LoggerFactory.getLogger(ProjectController.class);

    @Autowired
    private ProjectService projectService;


    @RequestMapping(path="/createProject",method = RequestMethod.POST)
    @ApiMethod(name = "createProject",desc = "创建项目")
    @ApiParam(name = "project",desc = "project",required = true)
    public Result<String> createProject(@RequestBody @NotNull @Valid Project project){
        String id = projectService.createProject(project);

        return Result.ok(id);
    }




    @RequestMapping(path="/updateProject",method = RequestMethod.POST)
    @ApiMethod(name = "updateProject",desc = "修改项目")
    @ApiParam(name = "project",desc = "project",required = true)
    public Result<Void> updateProject(@RequestBody @NotNull @Valid Project project){
        projectService.updateProject(project);

        return Result.ok();
    }

    @RequestMapping(path="/deleteProject",method = RequestMethod.POST)
    @ApiMethod(name = "deleteProject",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteProject(@NotNull String id){
        projectService.deleteProject(id);

        return Result.ok();
    }

    @RequestMapping(path="/findProject",method = RequestMethod.POST)
    @ApiMethod(name = "findProject",desc = "通过id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Project> findProject(@NotNull String id){
        Project Project = projectService.findProject(id);

        return Result.ok(Project);
    }

    @RequestMapping(path="/findAllProject",method = RequestMethod.POST)
    @ApiMethod(name = "findAllProject",desc = "查询所有查询")
    public Result<List<Project>> findAllProject(){
        List<Project> artifactList = projectService.findAllProject();

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findProjectList",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectList",desc = "通过条件查询")
    @ApiParam(name = "projectQuery",desc = "projectQuery",required = true)
    public Result<List<Project>> findProjectList(@RequestBody @Valid @NotNull ProjectQuery projectQuery){
        List<Project> artifactList = projectService.findProjectList(projectQuery);

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findProjectPage",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectPage",desc = "通过条件分页查询")
    @ApiParam(name = "projectQuery",desc = "projectQuery",required = true)
    public Result<List<Pagination<Project>>> findProjectPage(@RequestBody @Valid @NotNull ProjectQuery projectQuery){
        Pagination<Project> projectPage = projectService.findProjectPage(projectQuery);

        return Result.ok(projectPage);
    }



}
