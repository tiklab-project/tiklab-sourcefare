package io.tiklab.sourcefare.server.controller;

import io.tiklab.core.Result;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.sourcefare.server.model.RepositoryServerQuery;
import io.tiklab.sourcefare.server.model.ThirdBranch;
import io.tiklab.sourcefare.server.model.ThirdRepository;
import io.tiklab.sourcefare.server.service.ServerGitPukService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

@RestController
@RequestMapping("/serverGitPuk")
@Api(name = "ServerGitPukController",desc = "gitpuk仓库服务")
public class ServerGitPukController {

    @Autowired
    ServerGitPukService serverGitPukService;



    @RequestMapping(path = "/findRepositoryList",method = RequestMethod.POST)
    @ApiMethod(name = "findRepositoryList",desc = "通过仓库服务的id查询仓库")
    @ApiParam(name = "repositoryServer",desc = "repositoryServer",required = true)
    public Result<List<ThirdRepository>> findRepositoryList(@RequestBody @NotNull @Valid RepositoryServer repositoryServer){
        List<ThirdRepository> repositoryList= serverGitPukService.findRepositoryList(repositoryServer);

        return Result.ok(repositoryList);
    }

    @RequestMapping(path = "/findRepositoryBranchList",method = RequestMethod.POST)
    @ApiMethod(name = "findRepositoryBranchList",desc = "查询仓库的分支")
    @ApiParam(name = "serverQuery",desc = "serverQuery",required = true)
    public Result<List<ThirdBranch>> findRepositoryBranchList(@RequestBody @NotNull @Valid RepositoryServerQuery serverQuery){
        List<ThirdBranch> branchList = serverGitPukService.findRepositoryBranchList(serverQuery);

        return Result.ok(branchList);
    }
}
