package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanRule;
import io.tiklab.sourcefare.scan.model.ScanRuleQuery;
import io.tiklab.sourcefare.scan.service.ScanRuleService;
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
 * ScanRuleController
 */
@RestController
@RequestMapping("/scanRule")
//@Api(name = "ScanRuleController",desc = "扫描规则")
public class ScanRuleController {

    private static Logger logger = LoggerFactory.getLogger(ScanRuleController.class);

    @Autowired
    private ScanRuleService scanRuleService;

    @RequestMapping(path="/createScanRule",method = RequestMethod.POST)
    @ApiMethod(name = "createScanRule",desc = "添加扫描规则")
    @ApiParam(name = "scanRule",desc = "scanRule",required = true)
    public Result<String> createScanRule(@RequestBody @Valid @NotNull ScanRule scanRule){
        String scanRuleId = scanRuleService.createScanRule(scanRule);

        return Result.ok(scanRuleId);
    }

    @RequestMapping(path="/updateScanRule",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanRule",desc = "更新扫描规则")
    @ApiParam(name = "scanRule",desc = "scanRule",required = true)
    public Result<String> updateScanRule(@RequestBody @Valid @NotNull ScanRule scanRule){
         scanRuleService.updateScanRule(scanRule);

        return Result.ok();
    }


    @RequestMapping(path="/deleteScanRule",method = RequestMethod.POST)
    @ApiMethod(name = "deleteScanRule",desc = "删除扫描规则")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteScanRule(@NotNull String id){
        scanRuleService.deleteScanRule(id);

        return Result.ok();
    }

    @RequestMapping(path="/findScanRule",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRule",desc = "通过id查询扫描规则")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ScanRule> findScanRule(@NotNull String id){
        ScanRule scanRule = scanRuleService.findScanRule(id);

        return Result.ok(scanRule);
    }

    @RequestMapping(path="/findAllScanRule",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanRule",desc = "查询所有扫描规则")
    public Result<List<ScanRule>> findAllScanRule(){
        List<ScanRule> scanRuleList = scanRuleService.findAllScanRule();

        return Result.ok(scanRuleList);
    }

    @RequestMapping(path = "/findScanRuleList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRuleList",desc = "条件查询扫描规则")
    @ApiParam(name = "scanRuleQuery",desc = "scanRuleQuery",required = true)
    public Result<List<ScanRule>> findScanRuleList(@RequestBody @Valid @NotNull ScanRuleQuery scanRuleQuery){
        List<ScanRule> scanRuleList = scanRuleService.findScanRuleList(scanRuleQuery);

        return Result.ok(scanRuleList);
    }

    @RequestMapping(path = "/findScanRulePage",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRulePage",desc = "条件分页查询扫描规则")
    @ApiParam(name = "scanRuleQuery",desc = "scanRuleQuery",required = true)
    public Result<Pagination<ScanRule>> findScanRulePage(@RequestBody @Valid @NotNull ScanRuleQuery scanRuleQuery){
        Pagination<ScanRule> pagination = scanRuleService.findScanRulePage(scanRuleQuery);

        return Result.ok(pagination);
    }

}
