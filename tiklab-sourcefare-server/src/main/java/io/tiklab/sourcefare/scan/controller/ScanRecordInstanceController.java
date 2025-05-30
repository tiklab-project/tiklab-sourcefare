package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.ScanRecordInstance;
import io.tiklab.sourcefare.scan.model.ScanRecordInstanceQuery;
import io.tiklab.sourcefare.scan.service.ScanRecordInstanceService;
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
 * ScanRecordInstanceController
 */
@RestController
@RequestMapping("/scanRecordInstance")
@Api(name = "ScanRecordInstanceController",desc = "扫描记录实例实例")
public class ScanRecordInstanceController {

    private static Logger logger = LoggerFactory.getLogger(ScanRecordInstanceController.class);

    @Autowired
    private ScanRecordInstanceService scanRecordInstanceService;

    @RequestMapping(path="/createScanRecordInstance",method = RequestMethod.POST)
    @ApiMethod(name = "createScanRecordInstance",desc = "添加扫描制品记录实例")
    @ApiParam(name = "scanRecordInstance",desc = "scanRecordInstance",required = true)
    public Result<String> createScanRecordInstance(@RequestBody @Valid @NotNull ScanRecordInstance scanRecordInstance){
        String scanRecordInstanceId = scanRecordInstanceService.createScanRecordInstance(scanRecordInstance);

        return Result.ok(scanRecordInstanceId);
    }

    @RequestMapping(path="/updateScanRecordInstance",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanRecordInstance",desc = "更新扫描制品记录实例")
    @ApiParam(name = "scanRecordInstance",desc = "scanRecordInstance",required = true)
    public Result<String> updateScanRecordInstance(@RequestBody @Valid @NotNull ScanRecordInstance scanRecordInstance){
         scanRecordInstanceService.updateScanRecordInstance(scanRecordInstance);

        return Result.ok();
    }


    @RequestMapping(path="/deleteScanRecordInstance",method = RequestMethod.POST)
    @ApiMethod(name = "deleteScanRecordInstance",desc = "删除扫描记录实例")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteScanRecordInstance(@NotNull String id){
        scanRecordInstanceService.deleteScanRecordInstance(id);

        return Result.ok();
    }

    @RequestMapping(path="/findScanRecordInstance",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecordInstance",desc = "通过id查询扫描记录实例")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ScanRecordInstance> findScanRecordInstance(@NotNull String id){
        ScanRecordInstance scanRecordInstance = scanRecordInstanceService.findScanRecordInstance(id);

        return Result.ok(scanRecordInstance);
    }

    @RequestMapping(path="/findAllScanRecordInstance",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanRecordInstance",desc = "查询所有扫描记录实例")
    public Result<List<ScanRecordInstance>> findAllScanRecordInstance(){
        List<ScanRecordInstance> scanRecordInstanceList = scanRecordInstanceService.findAllScanRecordInstance();

        return Result.ok(scanRecordInstanceList);
    }

    @RequestMapping(path = "/findScanRecordInstanceList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecordInstanceList",desc = "条件查询扫描记录实例")
    @ApiParam(name = "scanRecordInstanceQuery",desc = "scanRecordInstanceQuery",required = true)
    public Result<List<ScanRecordInstance>> findScanRecordInstanceList(@RequestBody @Valid @NotNull ScanRecordInstanceQuery scanRecordInstanceQuery){
        List<ScanRecordInstance> scanRecordInstanceList = scanRecordInstanceService.findScanRecordInstanceList(scanRecordInstanceQuery);

        return Result.ok(scanRecordInstanceList);
    }

    @RequestMapping(path = "/findScanRecordInstancePage",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecordInstancePage",desc = "条件分页查询扫描记录实例")
    @ApiParam(name = "scanRecordInstanceQuery",desc = "scanRecordInstanceQuery",required = true)
    public Result<Pagination<ScanRecordInstance>> findScanRecordInstancePage(@RequestBody @Valid @NotNull ScanRecordInstanceQuery scanRecordInstanceQuery){
        Pagination<ScanRecordInstance> pagination = scanRecordInstanceService.findScanRecordInstancePage(scanRecordInstanceQuery);

        return Result.ok(pagination);
    }


    @RequestMapping(path="/findRecordInstancePageByPlay",method = RequestMethod.POST)
    @ApiMethod(name = "findScanIssuesBySonar",desc = "查询sonar执行的问题列表")
    @ApiParam(name = "scanRecordInstanceQuery",desc = "scanRecordInstanceQuery",required = true)
    public Result<Pagination<ScanRecordInstance>> findScanIssuesBySonar(@RequestBody @Valid @NotNull ScanRecordInstanceQuery scanRecordInstanceQuery){
        Pagination<ScanRecordInstance> pagination =scanRecordInstanceService.findRecordInstancePageByPlay(scanRecordInstanceQuery);

        return Result.ok(pagination);
    }
}
