package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.ScanPlay;
import io.tiklab.sourcefare.scan.model.ScanPlayQuery;
import io.tiklab.sourcefare.scan.service.ScanPlayService;
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
 * ScanPlayController
 */
@RestController
@RequestMapping("/scanPlay")
@Api(name = "ScanPlayController",desc = "扫描计划")
public class ScanPlayController {

    private static Logger logger = LoggerFactory.getLogger(ScanPlayController.class);

    @Autowired
    private ScanPlayService scanPlayService;

    @RequestMapping(path="/createScanPlay",method = RequestMethod.POST)
    @ApiMethod(name = "createScanPlay",desc = "添加扫描制品计划")
    @ApiParam(name = "scanPlay",desc = "scanPlay",required = true)
    public Result<String> createScanPlay(@RequestBody @Valid @NotNull ScanPlay scanPlay){
        String scanPlayId = scanPlayService.createScanPlay(scanPlay);

        return Result.ok(scanPlayId);
    }

    @RequestMapping(path="/updateScanPlay",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanPlay",desc = "更新扫描制品计划")
    @ApiParam(name = "scanPlay",desc = "scanPlay",required = true)
    public Result<String> updateScanPlay(@RequestBody @Valid @NotNull ScanPlay scanPlay){
         scanPlayService.updateScanPlay(scanPlay);

        return Result.ok();
    }


    @RequestMapping(path="/deleteScanPlay",method = RequestMethod.POST)
    @ApiMethod(name = "deleteScanPlay",desc = "删除扫描计划")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteScanPlay(@NotNull String id){
        scanPlayService.deleteScanPlay(id);

        return Result.ok();
    }

    @RequestMapping(path="/findScanPlay",method = RequestMethod.POST)
    @ApiMethod(name = "findScanPlay",desc = "通过id查询扫描计划")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ScanPlay> findScanPlay(@NotNull String id){
        ScanPlay scanPlay = scanPlayService.findScanPlay(id);

        return Result.ok(scanPlay);
    }

    @RequestMapping(path="/findAllScanPlay",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanPlay",desc = "查询所有扫描计划")
    public Result<List<ScanPlay>> findAllScanPlay(){
        List<ScanPlay> scanPlayList = scanPlayService.findAllScanPlay();

        return Result.ok(scanPlayList);
    }

    @RequestMapping(path = "/findScanPlayList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanPlayList",desc = "条件查询扫描计划")
    @ApiParam(name = "scanPlayQuery",desc = "scanPlayQuery",required = true)
    public Result<List<ScanPlay>> findScanPlayList(@RequestBody @Valid @NotNull ScanPlayQuery scanPlayQuery){
        List<ScanPlay> scanPlayList = scanPlayService.findScanPlayList(scanPlayQuery);

        return Result.ok(scanPlayList);
    }

    @RequestMapping(path = "/findScanPlayPage",method = RequestMethod.POST)
    @ApiMethod(name = "findScanPlayPage",desc = "条件分页查询扫描计划")
    @ApiParam(name = "scanPlayQuery",desc = "scanPlayQuery",required = true)
    public Result<Pagination<ScanPlay>> findScanPlayPage(@RequestBody @Valid @NotNull ScanPlayQuery scanPlayQuery){
        Pagination<ScanPlay> pagination = scanPlayService.findScanPlayPage(scanPlayQuery);

        return Result.ok(pagination);
    }

}
