package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanRuleSet;
import io.tiklab.sourcefare.scan.model.ScanRuleSetQuery;
import io.tiklab.sourcefare.scan.service.ScanRuleSetService;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
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
 * ScanRuleSetController
 */
@RestController
@RequestMapping("/scanRuleSet")
//@Api(name = "ScanRuleSetController",desc = "扫描规则集")
public class ScanRuleSetController {

    private static Logger logger = LoggerFactory.getLogger(ScanRuleSetController.class);

    @Autowired
    private ScanRuleSetService scanRuleSetService;

    @RequestMapping(path="/createScanRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "createScanRuleSet",desc = "添加扫描制品计划")
    @ApiParam(name = "scanRuleSet",desc = "scanRuleSet",required = true)
    public Result<String> createScanRuleSet(@RequestBody @Valid @NotNull ScanRuleSet scanRuleSet){
        String scanRuleSetId = scanRuleSetService.createScanRuleSet(scanRuleSet);

        return Result.ok(scanRuleSetId);
    }

    @RequestMapping(path="/updateScanRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanRuleSet",desc = "更新扫描制品计划")
    @ApiParam(name = "scanRuleSet",desc = "scanRuleSet",required = true)
    public Result<String> updateScanRuleSet(@RequestBody @Valid @NotNull ScanRuleSet scanRuleSet){
         scanRuleSetService.updateScanRuleSet(scanRuleSet);

        return Result.ok();
    }


    @RequestMapping(path="/deleteScanRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "deleteScanRuleSet",desc = "删除扫描规则集")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteScanRuleSet(@NotNull String id){
        scanRuleSetService.deleteScanRuleSet(id);

        return Result.ok();
    }

    @RequestMapping(path="/findScanRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRuleSet",desc = "通过id查询扫描规则集")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ScanRuleSet> findScanRuleSet(@NotNull String id){
        ScanRuleSet scanRuleSet = scanRuleSetService.findScanRuleSet(id);

        return Result.ok(scanRuleSet);
    }

    @RequestMapping(path="/findAllScanRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanRuleSet",desc = "查询所有扫描规则集")
    public Result<List<ScanRuleSet>> findAllScanRuleSet(){
        List<ScanRuleSet> scanRuleSetList = scanRuleSetService.findAllScanRuleSet();

        return Result.ok(scanRuleSetList);
    }

    @RequestMapping(path = "/findScanRuleSetList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRuleSetList",desc = "条件查询扫描规则集")
    @ApiParam(name = "scanRuleSetQuery",desc = "scanRuleSetQuery",required = true)
    public Result<List<ScanRuleSet>> findScanRuleSetList(@RequestBody @Valid @NotNull ScanRuleSetQuery scanRuleSetQuery){
        List<ScanRuleSet> scanRuleSetList = scanRuleSetService.findScanRuleSetList(scanRuleSetQuery);

        return Result.ok(scanRuleSetList);
    }

    @RequestMapping(path = "/findScanRuleSetPage",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRuleSetPage",desc = "条件分页查询扫描规则集")
    @ApiParam(name = "scanRuleSetQuery",desc = "scanRuleSetQuery",required = true)
    public Result<Pagination<ScanRuleSet>> findScanRuleSetPage(@RequestBody @Valid @NotNull ScanRuleSetQuery scanRuleSetQuery){
        Pagination<ScanRuleSet> pagination = scanRuleSetService.findScanRuleSetPage(scanRuleSetQuery);

        return Result.ok(pagination);
    }

    @RequestMapping(path = "/findScanRuleSetBySchemeId",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRuleSetBySchemeId",desc = "通过方案查询规则集")
    @ApiParam(name = "schemeId",desc = "scanRuleSetQuery",required = true)
    public Result<List<ScanRuleSet>> findScanRuleSetBySchemeId( @NotNull String schemeId){
        List<ScanRuleSet> scanRuleSetList = scanRuleSetService.findScanRuleSetBySchemeId(schemeId);

        return Result.ok(scanRuleSetList);
    }


    @RequestMapping(path = "/findScanRuleSetNotScheme",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRuleSetNotScheme",desc = "查询没有添加到当前方案的规则集")
    @ApiParam(name = "schemeId",desc = "scanRuleSetQuery",required = true)
    public Result<List<ScanRuleSet>> findScanRuleSetNotScheme( @NotNull String schemeId){
        List<ScanRuleSet> scanRuleSetList = scanRuleSetService.findScanRuleSetNotScheme(schemeId);

        return Result.ok(scanRuleSetList);
    }
}
