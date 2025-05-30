package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanScheme;
import io.tiklab.sourcefare.scan.model.ScanSchemeQuery;
import io.tiklab.sourcefare.scan.service.ScanSchemeService;
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
 * ScanSchemeController
 */
@RestController
@RequestMapping("/scanScheme")
@Api(name = "ScanSchemeController",desc = "扫描方案")
public class ScanSchemeController {

    private static Logger logger = LoggerFactory.getLogger(ScanSchemeController.class);

    @Autowired
    private ScanSchemeService scanSchemeService;

    @RequestMapping(path="/createScanScheme",method = RequestMethod.POST)
    @ApiMethod(name = "createScanScheme",desc = "添加扫描制品方案")
    @ApiParam(name = "scanScheme",desc = "scanScheme",required = true)
    public Result<String> createScanScheme(@RequestBody @Valid @NotNull ScanScheme scanScheme){
        String scanSchemeId = scanSchemeService.createScanScheme(scanScheme);

        return Result.ok(scanSchemeId);
    }

    @RequestMapping(path="/updateScanScheme",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanScheme",desc = "更新扫描制品方案")
    @ApiParam(name = "scanScheme",desc = "scanScheme",required = true)
    public Result<String> updateScanScheme(@RequestBody @Valid @NotNull ScanScheme scanScheme){
         scanSchemeService.updateScanScheme(scanScheme);

        return Result.ok();
    }


    @RequestMapping(path="/deleteScanScheme",method = RequestMethod.POST)
    @ApiMethod(name = "deleteScanScheme",desc = "删除扫描方案")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteScanScheme(@NotNull String id){
        scanSchemeService.deleteScanScheme(id);

        return Result.ok();
    }

    @RequestMapping(path="/findScanScheme",method = RequestMethod.POST)
    @ApiMethod(name = "findScanScheme",desc = "通过id查询扫描方案")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ScanScheme> findScanScheme(@NotNull String id){
        ScanScheme scanScheme = scanSchemeService.findScanScheme(id);

        return Result.ok(scanScheme);
    }

    @RequestMapping(path="/findAllScanScheme",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanScheme",desc = "查询所有扫描方案")
    public Result<List<ScanScheme>> findAllScanScheme(){
        List<ScanScheme> scanSchemeList = scanSchemeService.findAllScanScheme();

        return Result.ok(scanSchemeList);
    }

    @RequestMapping(path = "/findScanSchemeList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanSchemeList",desc = "条件查询扫描方案")
    @ApiParam(name = "scanSchemeQuery",desc = "scanSchemeQuery",required = true)
    public Result<List<ScanScheme>> findScanSchemeList(@RequestBody @Valid @NotNull ScanSchemeQuery scanSchemeQuery){
        List<ScanScheme> scanSchemeList = scanSchemeService.findScanSchemeList(scanSchemeQuery);

        return Result.ok(scanSchemeList);
    }

    @RequestMapping(path = "/findScanSchemePage",method = RequestMethod.POST)
    @ApiMethod(name = "findScanSchemePage",desc = "条件分页查询扫描方案")
    @ApiParam(name = "scanSchemeQuery",desc = "scanSchemeQuery",required = true)
    public Result<Pagination<ScanScheme>> findScanSchemePage(@RequestBody @Valid @NotNull ScanSchemeQuery scanSchemeQuery){
        Pagination<ScanScheme> pagination = scanSchemeService.findScanSchemePage(scanSchemeQuery);

        return Result.ok(pagination);
    }

}
