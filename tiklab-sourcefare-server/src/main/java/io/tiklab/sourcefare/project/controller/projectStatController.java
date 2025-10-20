package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.ProjectStat;
import io.tiklab.sourcefare.project.model.ScanPlayStat;
import io.tiklab.sourcefare.project.service.ProjectStatService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.constraints.NotNull;

@RestController
@RequestMapping("/projectStat")
//@Api(name = "projectStatController",desc = "项目统计")
public class projectStatController {

    @Autowired
    ProjectStatService projectStatService;

    @RequestMapping(path="/findScanPlayStat",method = RequestMethod.POST)
    @ApiMethod(name = "scanPlayStat",desc = "通过项目的id统计扫描计划相关数据")
    @ApiParam(name = "projectId",desc = "projectId",required = true)
    public Result<ScanPlayStat> findScanPlayStat(@NotNull String projectId){
        ScanPlayStat data= projectStatService.scanPlayStat(projectId);

        return Result.ok(data);
    }

    @RequestMapping(path="/findProjectStat",method = RequestMethod.POST)
    @ApiMethod(name = "scanPlayStat",desc = "查询项目的统计")
    @ApiParam(name = "projectId",desc = "projectId",required = true)
    public Result<ProjectStat> findProjectStat(){
        ProjectStat data= projectStatService.findProjectStat();

        return Result.ok(data);
    }

}
