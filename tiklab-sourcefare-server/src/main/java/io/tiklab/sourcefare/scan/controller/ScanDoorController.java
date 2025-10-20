package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.ScanDoor;
import io.tiklab.sourcefare.scan.model.ScanDoorQuery;
import io.tiklab.sourcefare.scan.service.ScanDoorService;
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
 * ScanDoorController
 */
@RestController
@RequestMapping("/scanDoor")
//@Api(name = "ScanDoorController",desc = "扫描门禁")
public class ScanDoorController {

    private static Logger logger = LoggerFactory.getLogger(ScanDoorController.class);

    @Autowired
    private ScanDoorService scanDoorService;

    @RequestMapping(path="/createScanDoor",method = RequestMethod.POST)
    @ApiMethod(name = "createScanDoor",desc = "添加扫描门禁")
    @ApiParam(name = "scanDoor",desc = "scanDoor",required = true)
    public Result<String> createScanDoor(@RequestBody @Valid @NotNull ScanDoor scanDoor){
        String scanDoorId = scanDoorService.createScanDoor(scanDoor);

        return Result.ok(scanDoorId);
    }

    @RequestMapping(path="/updateScanDoor",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanDoor",desc = "更新扫描门禁")
    @ApiParam(name = "scanDoor",desc = "scanDoor",required = true)
    public Result<String> updateScanDoor(@RequestBody @Valid @NotNull ScanDoor scanDoor){
         scanDoorService.updateScanDoor(scanDoor);

        return Result.ok();
    }


    @RequestMapping(path="/deleteScanDoor",method = RequestMethod.POST)
    @ApiMethod(name = "deleteScanDoor",desc = "删除扫描门禁")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteScanDoor(@NotNull String id){
        scanDoorService.deleteScanDoor(id);

        return Result.ok();
    }

    @RequestMapping(path="/findScanDoor",method = RequestMethod.POST)
    @ApiMethod(name = "findScanDoor",desc = "通过id查询扫描门禁")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ScanDoor> findScanDoor(@NotNull String id){
        ScanDoor scanDoor = scanDoorService.findScanDoor(id);

        return Result.ok(scanDoor);
    }

    @RequestMapping(path="/findAllScanDoor",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanDoor",desc = "查询所有扫描门禁")
    public Result<List<ScanDoor>> findAllScanDoor(){
        List<ScanDoor> scanDoorList = scanDoorService.findAllScanDoor();

        return Result.ok(scanDoorList);
    }

    @RequestMapping(path = "/findScanDoorList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanDoorList",desc = "条件查询扫描门禁")
    @ApiParam(name = "scanDoorQuery",desc = "scanDoorQuery",required = true)
    public Result<List<ScanDoor>> findScanDoorList(@RequestBody @Valid @NotNull ScanDoorQuery scanDoorQuery){
        List<ScanDoor> scanDoorList = scanDoorService.findScanDoorList(scanDoorQuery);

        return Result.ok(scanDoorList);
    }

    @RequestMapping(path = "/findScanDoorByProjectId",method = RequestMethod.POST)
    @ApiMethod(name = "findScanDoorByProjectId",desc = "查询项目的扫描门禁")
    @ApiParam(name = "projectId",desc = "projectId",required = true)
    public Result<ScanDoor> findScanDoorByProjectId(@NotNull String projectId){
        ScanDoor scanDoor = scanDoorService.findScanDoorByProjectId(projectId);

        return Result.ok(scanDoor);
    }
}
