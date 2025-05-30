package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanSchemeRuleSet;
import io.tiklab.sourcefare.scan.model.ScanSchemeRuleSetQuery;
import io.tiklab.sourcefare.scan.service.ScanSchemeRuleSetService;
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
 * ScanSchemeRuleSetController
 */
@RestController
@RequestMapping("/scanSchemeRuleSet")
@Api(name = "ScanSchemeRuleSetController",desc = "扫描方案规则集关系")
public class ScanSchemeRuleSetController {

    private static Logger logger = LoggerFactory.getLogger(ScanSchemeRuleSetController.class);

    @Autowired
    private ScanSchemeRuleSetService scanSchemeRuleSetService;

    @RequestMapping(path="/createScanSchemeRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "createScanSchemeRuleSet",desc = "添加扫方案规则集关系")
    @ApiParam(name = "scanSchemeRuleSet",desc = "scanSchemeRuleSet",required = true)
    public Result<String> createScanSchemeRuleSet(@RequestBody @Valid @NotNull ScanSchemeRuleSet scanSchemeRuleSet){
        String scanSchemeRuleSetId = scanSchemeRuleSetService.createScanSchemeRuleSet(scanSchemeRuleSet);

        return Result.ok(scanSchemeRuleSetId);
    }

    @RequestMapping(path="/updateScanSchemeRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanSchemeRuleSet",desc = "更新扫描方案规则集关系")
    @ApiParam(name = "scanSchemeRuleSet",desc = "scanSchemeRuleSet",required = true)
    public Result<String> updateScanSchemeRuleSet(@RequestBody @Valid @NotNull ScanSchemeRuleSet scanSchemeRuleSet){
         scanSchemeRuleSetService.updateScanSchemeRuleSet(scanSchemeRuleSet);

        return Result.ok();
    }


    @RequestMapping(path="/deleteScanSchemeRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "deleteScanSchemeRuleSet",desc = "删除扫描方案规则集关系")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteScanSchemeRuleSet(@NotNull String id){
        scanSchemeRuleSetService.deleteScanSchemeRuleSet(id);

        return Result.ok();
    }

    @RequestMapping(path="/findScanSchemeRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "findScanSchemeRuleSet",desc = "通过id查询扫描方案规则集关系")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ScanSchemeRuleSet> findScanSchemeRuleSet(@NotNull String id){
        ScanSchemeRuleSet scanSchemeRuleSet = scanSchemeRuleSetService.findScanSchemeRuleSet(id);

        return Result.ok(scanSchemeRuleSet);
    }

    @RequestMapping(path="/findAllScanSchemeRuleSet",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanSchemeRuleSet",desc = "查询所有扫描方案规则集关系")
    public Result<List<ScanSchemeRuleSet>> findAllScanSchemeRuleSet(){
        List<ScanSchemeRuleSet> scanSchemeRuleSetList = scanSchemeRuleSetService.findAllScanSchemeRuleSet();

        return Result.ok(scanSchemeRuleSetList);
    }

    @RequestMapping(path = "/findScanSchemeRuleSetList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanSchemeRuleSetList",desc = "条件查询扫描方案规则集关系")
    @ApiParam(name = "scanSchemeRuleSetQuery",desc = "scanSchemeRuleSetQuery",required = true)
    public Result<List<ScanSchemeRuleSet>> findScanSchemeRuleSetList(@RequestBody @Valid @NotNull ScanSchemeRuleSetQuery scanSchemeRuleSetQuery){
        List<ScanSchemeRuleSet> scanSchemeRuleSetList = scanSchemeRuleSetService.findScanSchemeRuleSetList(scanSchemeRuleSetQuery);

        return Result.ok(scanSchemeRuleSetList);
    }

    @RequestMapping(path = "/findScanSchemeRuleSetPage",method = RequestMethod.POST)
    @ApiMethod(name = "findScanSchemeRuleSetPage",desc = "条件分页查询扫描方案规则集关系")
    @ApiParam(name = "scanSchemeRuleSetQuery",desc = "scanSchemeRuleSetQuery",required = true)
    public Result<Pagination<ScanSchemeRuleSet>> findScanSchemeRuleSetPage(@RequestBody @Valid @NotNull ScanSchemeRuleSetQuery scanSchemeRuleSetQuery){
        Pagination<ScanSchemeRuleSet> pagination = scanSchemeRuleSetService.findScanSchemeRuleSetPage(scanSchemeRuleSetQuery);

        return Result.ok(pagination);
    }

}
