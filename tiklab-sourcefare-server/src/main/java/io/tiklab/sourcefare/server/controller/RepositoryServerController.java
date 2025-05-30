package io.tiklab.sourcefare.server.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.sourcefare.server.model.RepositoryServerQuery;
import io.tiklab.sourcefare.server.service.RepositoryServerService;
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
 * RepositoryServerController
 */
@RestController
@RequestMapping("/RepositoryServer")
@Api(name = "RepositoryServerController",desc = "仓库服务")
public class RepositoryServerController {

    private static Logger logger = LoggerFactory.getLogger(RepositoryServerController.class);

    @Autowired
   RepositoryServerService repositoryServerService;


    @RequestMapping(path="/createRepositoryServer",method = RequestMethod.POST)
    @ApiMethod(name = "createRepositoryServer",desc = "创建仓库服务")
    @ApiParam(name = "RepositoryServer",desc = "RepositoryServer",required = true)
    public Result<String> createRepositoryServer(@RequestBody @NotNull @Valid RepositoryServer RepositoryServer){
        String id = repositoryServerService.createRepositoryServer(RepositoryServer);

        return Result.ok(id);
    }




    @RequestMapping(path="/updateRepositoryServer",method = RequestMethod.POST)
    @ApiMethod(name = "updateRepositoryServer",desc = "修改仓库服务")
    @ApiParam(name = "RepositoryServer",desc = "RepositoryServer",required = true)
    public Result<Void> updateRepositoryServer(@RequestBody @NotNull @Valid RepositoryServer RepositoryServer){
        repositoryServerService.updateRepositoryServer(RepositoryServer);

        return Result.ok();
    }

    @RequestMapping(path="/deleteRepositoryServer",method = RequestMethod.POST)
    @ApiMethod(name = "deleteRepositoryServer",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteRepositoryServer(@NotNull String id){
        repositoryServerService.deleteRepositoryServer(id);

        return Result.ok();
    }

    @RequestMapping(path="/findRepositoryServer",method = RequestMethod.POST)
    @ApiMethod(name = "findRepositoryServer",desc = "通过id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<RepositoryServer> findRepositoryServer(@NotNull String id){
        RepositoryServer RepositoryServer = repositoryServerService.findRepositoryServer(id);

        return Result.ok(RepositoryServer);
    }

    @RequestMapping(path="/findAllRepositoryServer",method = RequestMethod.POST)
    @ApiMethod(name = "findAllRepositoryServer",desc = "查询所有查询")
    public Result<List<RepositoryServer>> findAllRepositoryServer(){
        List<RepositoryServer> artifactList = repositoryServerService.findAllRepositoryServer();

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findRepositoryServerList",method = RequestMethod.POST)
    @ApiMethod(name = "findRepositoryServerList",desc = "通过条件查询")
    @ApiParam(name = "repositoryServerQuery",desc = "repositoryServerQuery",required = true)
    public Result<List<RepositoryServer>> findRepositoryServerList(@RequestBody @Valid @NotNull RepositoryServerQuery repositoryServerQuery){
        List<RepositoryServer> artifactList = repositoryServerService.findRepositoryServerList(repositoryServerQuery);

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findRepositoryServerPage",method = RequestMethod.POST)
    @ApiMethod(name = "findRepositoryServerPage",desc = "通过条件分页查询")
    @ApiParam(name = "repositoryServerQuery",desc = "repositoryServerQuery",required = true)
    public Result<List<Pagination<RepositoryServer>>> findRepositoryServerPage(@RequestBody @Valid @NotNull RepositoryServerQuery repositoryServerQuery){
        Pagination<RepositoryServer> RepositoryServerPage = repositoryServerService.findRepositoryServerPage(repositoryServerQuery);

        return Result.ok(RepositoryServerPage);
    }


}
