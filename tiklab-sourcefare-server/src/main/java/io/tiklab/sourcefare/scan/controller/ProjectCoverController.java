package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.ProjectCover;
import io.tiklab.sourcefare.scan.model.ProjectCoverQuery;
import io.tiklab.sourcefare.scan.service.ProjectCoverService;
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
 * ProjectCoverController
 */
@RestController
@RequestMapping("/projectCover")
//@Api(name = "ProjectCoverController",desc = "项目覆盖率")
public class ProjectCoverController {

    private static Logger logger = LoggerFactory.getLogger(ProjectCoverController.class);

    @Autowired
    private ProjectCoverService projectCoverService;

    @RequestMapping(path="/createProjectCover",method = RequestMethod.POST)
    @ApiMethod(name = "createProjectCover",desc = "添加项目覆盖率")
    @ApiParam(name = "projectCover",desc = "projectCover",required = true)
    public Result<String> createProjectCover(@RequestBody @Valid @NotNull ProjectCover projectCover){
        String projectCoverId = projectCoverService.createProjectCover(projectCover);

        return Result.ok(projectCoverId);
    }

    @RequestMapping(path="/updateProjectCover",method = RequestMethod.POST)
    @ApiMethod(name = "updateProjectCover",desc = "更新项目覆盖率")
    @ApiParam(name = "projectCover",desc = "projectCover",required = true)
    public Result<String> updateProjectCover(@RequestBody @Valid @NotNull ProjectCover projectCover){
         projectCoverService.updateProjectCover(projectCover);

        return Result.ok();
    }


    @RequestMapping(path="/deleteProjectCover",method = RequestMethod.POST)
    @ApiMethod(name = "deleteProjectCover",desc = "删除项目覆盖率")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteProjectCover(@NotNull String id){
        projectCoverService.deleteProjectCover(id);

        return Result.ok();
    }

    @RequestMapping(path="/findProjectCover",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCover",desc = "通过id查询项目覆盖率")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ProjectCover> findProjectCover(@NotNull String id){
        ProjectCover projectCover = projectCoverService.findProjectCover(id);

        return Result.ok(projectCover);
    }


    @RequestMapping(path="/findAllProjectCover",method = RequestMethod.POST)
    @ApiMethod(name = "findAllProjectCover",desc = "查询所有项目覆盖率")
    public Result<List<ProjectCover>> findAllProjectCover(){
        List<ProjectCover> projectCoverList = projectCoverService.findAllProjectCover();

        return Result.ok(projectCoverList);
    }

    @RequestMapping(path = "/findProjectCoverList",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCoverList",desc = "条件查询项目覆盖率")
    @ApiParam(name = "projectCoverQuery",desc = "projectCoverQuery",required = true)
    public Result<List<ProjectCover>> findProjectCoverList(@RequestBody @Valid @NotNull ProjectCoverQuery projectCoverQuery){
        List<ProjectCover> projectCoverList = projectCoverService.findProjectCoverList(projectCoverQuery);

        return Result.ok(projectCoverList);
    }

    @RequestMapping(path = "/findProjectCoverPage",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCoverPage",desc = "条件分页查询项目覆盖率")
    @ApiParam(name = "projectCoverQuery",desc = "projectCoverQuery",required = true)
    public Result<Pagination<ProjectCover>> findProjectCoverPage(@RequestBody @Valid @NotNull ProjectCoverQuery projectCoverQuery){
        Pagination<ProjectCover> pagination = projectCoverService.findProjectCoverPage(projectCoverQuery);

        return Result.ok(pagination);
    }
}
