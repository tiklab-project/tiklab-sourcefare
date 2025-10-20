package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.RecordInstance;
import io.tiklab.sourcefare.scan.model.RecordInstanceCondQuery;
import io.tiklab.sourcefare.scan.model.RecordInstanceQuery;
import io.tiklab.sourcefare.scan.service.RecordInstanceService;
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
@RequestMapping("/recordInstance")
//@Api(name = "ScanRecordInstanceController",desc = "扫描记录实例实例")
public class RecordInstanceController {

    private static Logger logger = LoggerFactory.getLogger(RecordInstanceController.class);

    @Autowired
    private RecordInstanceService scanRecordInstanceService;

    @RequestMapping(path="/createScanRecordInstance",method = RequestMethod.POST)
    @ApiMethod(name = "createScanRecordInstance",desc = "添加扫描制品记录实例")
    @ApiParam(name = "scanRecordInstance",desc = "scanRecordInstance",required = true)
    public Result<String> createScanRecordInstance(@RequestBody @Valid @NotNull RecordInstance scanRecordInstance){
        String scanRecordInstanceId = scanRecordInstanceService.createScanRecordInstance(scanRecordInstance);

        return Result.ok(scanRecordInstanceId);
    }

    @RequestMapping(path="/updateScanRecordInstance",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanRecordInstance",desc = "更新扫描制品记录实例")
    @ApiParam(name = "scanRecordInstance",desc = "scanRecordInstance",required = true)
    public Result<String> updateScanRecordInstance(@RequestBody @Valid @NotNull RecordInstance scanRecordInstance){
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
    public Result<RecordInstance> findScanRecordInstance(@NotNull String id){
        RecordInstance scanRecordInstance = scanRecordInstanceService.findScanRecordInstance(id);

        return Result.ok(scanRecordInstance);
    }

    @RequestMapping(path="/findAllScanRecordInstance",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanRecordInstance",desc = "查询所有扫描记录实例")
    public Result<List<RecordInstance>> findAllScanRecordInstance(){
        List<RecordInstance> scanRecordInstanceList = scanRecordInstanceService.findAllScanRecordInstance();

        return Result.ok(scanRecordInstanceList);
    }

    @RequestMapping(path = "/findScanRecordInstanceList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecordInstanceList",desc = "条件查询扫描记录实例")
    @ApiParam(name = "scanRecordInstanceQuery",desc = "scanRecordInstanceQuery",required = true)
    public Result<List<RecordInstance>> findScanRecordInstanceList(@RequestBody @Valid @NotNull RecordInstanceQuery scanRecordInstanceQuery){
        List<RecordInstance> scanRecordInstanceList = scanRecordInstanceService.findScanRecordInstanceList(scanRecordInstanceQuery);

        return Result.ok(scanRecordInstanceList);
    }

    @RequestMapping(path = "/findScanRecordInstancePage",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecordInstancePage",desc = "条件分页查询扫描记录实例")
    @ApiParam(name = "scanRecordInstanceQuery",desc = "scanRecordInstanceQuery",required = true)
    public Result<Pagination<RecordInstance>> findScanRecordInstancePage(@RequestBody @Valid @NotNull RecordInstanceQuery scanRecordInstanceQuery){
        Pagination<RecordInstance> pagination = scanRecordInstanceService.findScanRecordInstancePage(scanRecordInstanceQuery);

        return Result.ok(pagination);
    }


    @RequestMapping(path="/findRecordInstancePageByPlay",method = RequestMethod.POST)
    @ApiMethod(name = "通过扫描计划分页查询扫描问题",desc = "通过扫描计划分页查询扫描问题")
    @ApiParam(name = "scanRecordInstanceQuery",desc = "scanRecordInstanceQuery",required = true)
    public Result<Pagination<RecordInstance>> findScanIssuesBySonar(@RequestBody @Valid @NotNull RecordInstanceQuery scanRecordInstanceQuery){
        Pagination<RecordInstance> pagination =scanRecordInstanceService.findRecordInstancePageByPlay(scanRecordInstanceQuery);

        return Result.ok(pagination);
    }

    @RequestMapping(path = "/findProjectInstancePage",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectInstancePage",desc = "条件分页查询项目总的扫描记录")
    @ApiParam(name = "scanRecordInstanceQuery",desc = "scanRecordInstanceQuery",required = true)
    public Result<Pagination<RecordInstance>> findProjectInstancePage(@RequestBody @Valid @NotNull RecordInstanceQuery scanRecordInstanceQuery){
        Pagination<RecordInstance> pagination = scanRecordInstanceService.findProjectInstancePage(scanRecordInstanceQuery);

        return Result.ok(pagination);
    }

    @RequestMapping(path = "/findProjectInstanceNum",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectInstanceNum",desc = "条件分页查询项目总的扫描记录数量")
    @ApiParam(name = "scanRecordInstanceQuery",desc = "scanRecordInstanceQuery",required = true)
    public Result<Object> findProjectInstanceNum(@RequestBody @Valid @NotNull RecordInstanceQuery scanRecordInstanceQuery){
        Object instanceNum = scanRecordInstanceService.findProjectInstanceNum(scanRecordInstanceQuery);

        return Result.ok(instanceNum);
    }
}
