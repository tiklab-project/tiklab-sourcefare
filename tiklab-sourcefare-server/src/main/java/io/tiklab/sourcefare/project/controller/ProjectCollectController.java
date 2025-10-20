package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.ProjectCollect;
import io.tiklab.sourcefare.project.model.ProjectCollectQuery;
import io.tiklab.sourcefare.project.service.ProjectCollectService;
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
 * ProjectCollectController
 */
@RestController
@RequestMapping("/projectCollect")
//@Api(name = "ProjectCollectController",desc = "项目收藏信息")
public class ProjectCollectController {

    private static Logger logger = LoggerFactory.getLogger(ProjectCollectController.class);

    @Autowired
    private ProjectCollectService projectCollectService;


    @RequestMapping(path="/createProjectCollect",method = RequestMethod.POST)
    @ApiMethod(name = "createProjectCollect",desc = "创建项目收藏信息")
    @ApiParam(name = "projectCollect",desc = "projectCollect",required = true)
    public Result<String> createProjectCollect(@RequestBody @NotNull @Valid ProjectCollect projectCollect){
        String id = projectCollectService.createProjectCollect(projectCollect);

        return Result.ok(id);
    }

    @RequestMapping(path="/updateProjectCollect",method = RequestMethod.POST)
    @ApiMethod(name = "updateProjectCollect",desc = "修改项目收藏信息")
    @ApiParam(name = "projectCollect",desc = "projectCollect",required = true)
    public Result<Void> updateProjectCollect(@RequestBody @NotNull @Valid ProjectCollect projectCollect){
        projectCollectService.updateProjectCollect(projectCollect);

        return Result.ok();
    }

    @RequestMapping(path="/deleteProjectCollect",method = RequestMethod.POST)
    @ApiMethod(name = "deleteProjectCollect",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteProjectCollect(@NotNull String id){
        projectCollectService.deleteProjectCollect(id);

        return Result.ok();
    }

    @RequestMapping(path="/deleteCollect",method = RequestMethod.POST)
    @ApiMethod(name = "deleteCollect",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteCollect(@NotNull String projectId,@NotNull String userId){
        projectCollectService.deleteCollect(projectId,userId);

        return Result.ok();
    }

    @RequestMapping(path="/findProjectCollect",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCollect",desc = "通过id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ProjectCollect> findProjectCollect(@NotNull String id){
        ProjectCollect ProjectCollect = projectCollectService.findProjectCollect(id);

        return Result.ok(ProjectCollect);
    }



    @RequestMapping(path="/findAllProjectCollect",method = RequestMethod.POST)
    @ApiMethod(name = "findAllProjectCollect",desc = "查询所有查询")
    public Result<List<ProjectCollect>> findAllProjectCollect(){
        List<ProjectCollect> artifactList = projectCollectService.findAllProjectCollect();

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findProjectCollectList",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCollectList",desc = "通过条件查询")
    @ApiParam(name = "projectCollectQuery",desc = "projectCollectQuery",required = true)
    public Result<List<ProjectCollect>> findProjectCollectList(@RequestBody @Valid @NotNull ProjectCollectQuery projectCollectQuery){
        List<ProjectCollect> artifactList = projectCollectService.findProjectCollectList(projectCollectQuery);

        return Result.ok(artifactList);
    }

}