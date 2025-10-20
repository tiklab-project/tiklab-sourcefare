package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.ProjectCoverGo;
import io.tiklab.sourcefare.scan.model.ProjectCoverGoQuery;
import io.tiklab.sourcefare.scan.service.ProjectCoverGoService;
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
 * ProjectCoverGoController
 */
@RestController
@RequestMapping("/projectCoverGo")
//@Api(name = "ProjectCoverGoController",desc = "go项目覆盖率")
public class ProjectCoverGoController {

    private static Logger logger = LoggerFactory.getLogger(ProjectCoverGoController.class);

    @Autowired
    private ProjectCoverGoService projectCoverGoService;

    @RequestMapping(path="/createProjectCoverGo",method = RequestMethod.POST)
    @ApiMethod(name = "createProjectCoverGo",desc = "添加go项目覆盖率")
    @ApiParam(name = "projectCoverGo",desc = "projectCoverGo",required = true)
    public Result<String> createProjectCoverGo(@RequestBody @Valid @NotNull ProjectCoverGo projectCoverGo){
        String projectCoverGoId = projectCoverGoService.createProjectCoverGo(projectCoverGo);

        return Result.ok(projectCoverGoId);
    }

    @RequestMapping(path="/updateProjectCoverGo",method = RequestMethod.POST)
    @ApiMethod(name = "updateProjectCoverGo",desc = "更新go项目覆盖率")
    @ApiParam(name = "projectCoverGo",desc = "projectCoverGo",required = true)
    public Result<String> updateProjectCoverGo(@RequestBody @Valid @NotNull ProjectCoverGo projectCoverGo){
         projectCoverGoService.updateProjectCoverGo(projectCoverGo);

        return Result.ok();
    }


    @RequestMapping(path="/deleteProjectCoverGo",method = RequestMethod.POST)
    @ApiMethod(name = "deleteProjectCoverGo",desc = "删除go项目覆盖率")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteProjectCoverGo(@NotNull String id){
        projectCoverGoService.deleteProjectCoverGo(id);

        return Result.ok();
    }

    @RequestMapping(path="/findProjectCoverGo",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCoverGo",desc = "通过id查询go项目覆盖率")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ProjectCoverGo> findProjectCoverGo(@NotNull String id){
        ProjectCoverGo projectCoverGo = projectCoverGoService.findProjectCoverGo(id);

        return Result.ok(projectCoverGo);
    }


    @RequestMapping(path="/findAllProjectCoverGo",method = RequestMethod.POST)
    @ApiMethod(name = "findAllProjectCoverGo",desc = "查询所有go项目覆盖率")
    public Result<List<ProjectCoverGo>> findAllProjectCoverGo(){
        List<ProjectCoverGo> projectCoverGoList = projectCoverGoService.findAllProjectCoverGo();

        return Result.ok(projectCoverGoList);
    }

    @RequestMapping(path = "/findProjectCoverGoList",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCoverGoList",desc = "条件查询go项目覆盖率")
    @ApiParam(name = "projectCoverGoQuery",desc = "projectCoverGoQuery",required = true)
    public Result<List<ProjectCoverGo>> findProjectCoverGoList(@RequestBody @Valid @NotNull ProjectCoverGoQuery projectCoverGoQuery){
        List<ProjectCoverGo> projectCoverGoList = projectCoverGoService.findProjectCoverGoList(projectCoverGoQuery);

        return Result.ok(projectCoverGoList);
    }

    @RequestMapping(path = "/findProjectCoverGoPage",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCoverGoPage",desc = "条件分页查询go项目覆盖率")
    @ApiParam(name = "projectCoverGoQuery",desc = "projectCoverGoQuery",required = true)
    public Result<Pagination<ProjectCoverGo>> findProjectCoverGoPage(@RequestBody @Valid @NotNull ProjectCoverGoQuery projectCoverGoQuery){
        Pagination<ProjectCoverGo> pagination = projectCoverGoService.findProjectCoverGoPage(projectCoverGoQuery);

        return Result.ok(pagination);
    }


}
