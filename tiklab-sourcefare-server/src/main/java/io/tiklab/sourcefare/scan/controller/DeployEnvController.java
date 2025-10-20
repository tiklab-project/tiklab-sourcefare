package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.DeployEnv;
import io.tiklab.sourcefare.scan.model.DeployEnvQuery;
import io.tiklab.sourcefare.scan.service.DeployEnvService;
import org.apache.commons.lang3.StringUtils;
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
 * DeployEnvController
 */
@RestController
@RequestMapping("/deployEnv")
//@Api(name = "DeployEnvController",desc = "环境管理")
public class DeployEnvController {

    private static Logger logger = LoggerFactory.getLogger(DeployEnvController.class);

    @Autowired
    private DeployEnvService deployEnvService;

    @RequestMapping(path="/createDeployEnv",method = RequestMethod.POST)
    @ApiMethod(name = "createDeployEnv",desc = "创建环境管理")
    @ApiParam(name = "deployEnv",desc = "deployEnv",required = true)
    public Result<String> createDeployEnv(@RequestBody @NotNull @Valid DeployEnv deployEnv){
        String id = deployEnvService.createDeployEnv(deployEnv);

        return Result.ok(id);
    }

    @RequestMapping(path="/updateDeployEnv",method = RequestMethod.POST)
    @ApiMethod(name = "updateDeployEnv",desc = "修改环境管理")
    @ApiParam(name = "deployEnv",desc = "deployEnv",required = true)
    public Result<Void> updateDeployEnv(@RequestBody @NotNull @Valid DeployEnv deployEnv){
        deployEnvService.updateDeployEnv(deployEnv);

        return Result.ok();
    }

    @RequestMapping(path="/deleteDeployEnv",method = RequestMethod.POST)
    @ApiMethod(name = "deleteDeployEnv",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteDeployEnv(@NotNull String id){
        deployEnvService.deleteDeployEnv(id);

        return Result.ok();
    }

    @RequestMapping(path="/findDeployEnv",method = RequestMethod.POST)
    @ApiMethod(name = "findDeployEnv",desc = "通过id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<DeployEnv> findDeployEnv(@NotNull String id){
        DeployEnv DeployEnv = deployEnvService.findDeployEnv(id);

        return Result.ok(DeployEnv);
    }

    @RequestMapping(path="/findAllDeployEnv",method = RequestMethod.POST)
    @ApiMethod(name = "findAllDeployEnv",desc = "查询所有查询")
    public Result<List<DeployEnv>> findAllDeployEnv(){
        List<DeployEnv> artifactList = deployEnvService.findAllDeployEnv();

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findDeployEnvList",method = RequestMethod.POST)
    @ApiMethod(name = "findDeployEnvList",desc = "通过条件查询")
    @ApiParam(name = "deployEnvQuery",desc = "deployEnvQuery",required = true)
    public Result<List<DeployEnv>> findDeployEnvList(@RequestBody @Valid @NotNull DeployEnvQuery deployEnvQuery){
        List<DeployEnv> artifactList = deployEnvService.findDeployEnvList(deployEnvQuery);

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findDeployEnvPage",method = RequestMethod.POST)
    @ApiMethod(name = "findDeployEnvPage",desc = "通过条件分页查询")
    @ApiParam(name = "deployEnvQuery",desc = "deployEnvQuery",required = true)
    public Result<Pagination<DeployEnv>> findDeployEnvPage(@RequestBody @Valid @NotNull DeployEnvQuery deployEnvQuery){
        Pagination<DeployEnv> pagination = deployEnvService.findDeployEnvPage(deployEnvQuery);

        return Result.ok(pagination);
    }

    @RequestMapping(path = "/detectionEnv",method = RequestMethod.POST)
    @ApiMethod(name = "detectionEnv",desc = "检测全局环境")
    @ApiParam(name = "deployEnvQuery",desc = "deployEnvQuery",required = true)
    public Result<String> detectionEnv(@NotNull String type){
        String data = deployEnvService.detectionEnv(type);

        return Result.ok(data);
    }

}
