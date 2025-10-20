package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.DeployEnv;
import io.tiklab.sourcefare.scan.model.DeployEnvQuery;
import io.tiklab.sourcefare.scan.model.IssueStatistic;
import io.tiklab.sourcefare.scan.model.IssueStatisticQuery;
import io.tiklab.sourcefare.scan.service.IssueStatisticService;
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
 * IssueStatisticController
 */
@RestController
@RequestMapping("/issueStatistic")
//@Api(name = "IssueStatisticController",desc = "项目问题统计")
public class IssueStatisticController {

    private static Logger logger = LoggerFactory.getLogger(IssueStatisticController.class);

    @Autowired
    private IssueStatisticService issueStatisticService;

    @RequestMapping(path="/createIssueStatistic",method = RequestMethod.POST)
    @ApiMethod(name = "createIssueStatistic",desc = "添加项目问题统计")
    @ApiParam(name = "issueStatistic",desc = "issueStatistic",required = true)
    public Result<String> createIssueStatistic(@RequestBody @Valid @NotNull IssueStatistic issueStatistic){
        String issueStatisticId = issueStatisticService.createIssueStatistic(issueStatistic);

        return Result.ok(issueStatisticId);
    }

    @RequestMapping(path="/updateIssueStatistic",method = RequestMethod.POST)
    @ApiMethod(name = "updateIssueStatistic",desc = "更新项目问题统计")
    @ApiParam(name = "issueStatistic",desc = "issueStatistic",required = true)
    public Result<String> updateIssueStatistic(@RequestBody @Valid @NotNull IssueStatistic issueStatistic){
         issueStatisticService.updateIssueStatistic(issueStatistic);

        return Result.ok();
    }


    @RequestMapping(path="/deleteIssueStatistic",method = RequestMethod.POST)
    @ApiMethod(name = "deleteIssueStatistic",desc = "删除项目问题统计")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteIssueStatistic(@NotNull String id){
        issueStatisticService.deleteIssueStatistic(id);

        return Result.ok();
    }

    @RequestMapping(path="/findIssueStatistic",method = RequestMethod.POST)
    @ApiMethod(name = "findIssueStatistic",desc = "通过id查询项目问题统计")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<IssueStatistic> findIssueStatistic(@NotNull String id){
        IssueStatistic issueStatistic = issueStatisticService.findIssueStatistic(id);

        return Result.ok(issueStatistic);
    }

    @RequestMapping(path="/findAllIssueStatistic",method = RequestMethod.POST)
    @ApiMethod(name = "findAllIssueStatistic",desc = "查询所有项目问题统计")
    public Result<List<IssueStatistic>> findAllIssueStatistic(){
        List<IssueStatistic> issueStatisticList = issueStatisticService.findAllIssueStatistic();

        return Result.ok(issueStatisticList);
    }

    @RequestMapping(path = "/findIssueStatisticList",method = RequestMethod.POST)
    @ApiMethod(name = "findIssueStatisticList",desc = "条件查询项目问题统计")
    @ApiParam(name = "issueStatisticQuery",desc = "issueStatisticQuery",required = true)
    public Result<List<IssueStatistic>> findIssueStatisticList(@RequestBody @Valid @NotNull IssueStatisticQuery issueStatisticQuery){
        List<IssueStatistic> issueStatisticList = issueStatisticService.findIssueStatisticList(issueStatisticQuery);

        return Result.ok(issueStatisticList);
    }

    @RequestMapping(path = "/findIssueStatisticPage",method = RequestMethod.POST)
    @ApiMethod(name = "findIssueStatisticPage",desc = "通过条件分页查询")
    @ApiParam(name = "issueStatisticQuery",desc = "issueStatisticQuery",required = true)
    public Result<Pagination<IssueStatistic>> findIssueStatisticPage(@RequestBody @Valid @NotNull IssueStatisticQuery issueStatisticQuery){
        Pagination<IssueStatistic> pagination = issueStatisticService.findIssueStatisticPage(issueStatisticQuery);

        return Result.ok(pagination);
    }

    @RequestMapping(path = "/findIssueStatisticCount",method = RequestMethod.POST)
    @ApiMethod(name = "findIssueStatisticCount",desc = "条件查询问题解决状态数量")
    @ApiParam(name = "issueStatisticQuery",desc = "issueStatisticQuery",required = true)
    public Result<Object> findIssueStatisticCount(@RequestBody @Valid @NotNull IssueStatisticQuery issueStatisticQuery){
        Object count = issueStatisticService.findIssueStatisticCount(issueStatisticQuery);

        return Result.ok(count);
    }

    @RequestMapping(path = "/findIssueTypeStatisticCount",method = RequestMethod.POST)
    @ApiMethod(name = "findIssueTypeStatisticCount",desc = "条件查询问题类型数量")
    @ApiParam(name = "recordId",desc = "扫描记录的id",required = true)
    public Result<Object> findIssueTypeStatisticCount(@NotNull String recordId){
        Object count = issueStatisticService.findIssueTypeStatisticCount(recordId);

        return Result.ok(count);
    }

}
