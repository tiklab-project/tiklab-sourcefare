package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.ScanRecordLog;
import io.tiklab.sourcefare.scan.model.ScanRecordLogQuery;
import io.tiklab.sourcefare.scan.service.ScanRecordLogService;
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
 * ScanRecordLogController
 */
@RestController
@RequestMapping("/scanRecordLog")
//@Api(name = "ScanRecordLogController",desc = "扫描记录日志")
public class ScanRecordLogController {

    private static Logger logger = LoggerFactory.getLogger(ScanRecordLogController.class);

    @Autowired
    private ScanRecordLogService scanRecordLogService;

    @RequestMapping(path="/createScanRecordLog",method = RequestMethod.POST)
    @ApiMethod(name = "createScanRecordLog",desc = "添加扫描记录日志")
    @ApiParam(name = "scanRecordLog",desc = "scanRecordLog",required = true)
    public Result<String> createScanRecordLog(@RequestBody @Valid @NotNull ScanRecordLog scanRecordLog){
        String scanRecordLogId = scanRecordLogService.createScanRecordLog(scanRecordLog);

        return Result.ok(scanRecordLogId);
    }

    @RequestMapping(path="/updateScanRecordLog",method = RequestMethod.POST)
    @ApiMethod(name = "updateScanRecordLog",desc = "更新扫描记录日志")
    @ApiParam(name = "scanRecordLog",desc = "scanRecordLog",required = true)
    public Result<String> updateScanRecordLog(@RequestBody @Valid @NotNull ScanRecordLog scanRecordLog){
         scanRecordLogService.updateScanRecordLog(scanRecordLog);

        return Result.ok();
    }


    @RequestMapping(path="/deleteScanRecordLog",method = RequestMethod.POST)
    @ApiMethod(name = "deleteScanRecordLog",desc = "删除扫描记录日志")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteScanRecordLog(@NotNull String id){
        scanRecordLogService.deleteScanRecordLog(id);

        return Result.ok();
    }

    @RequestMapping(path="/findScanRecordLog",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecordLog",desc = "通过id查询扫描记录日志")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<ScanRecordLog> findScanRecordLog(@NotNull String id){
        ScanRecordLog scanRecordLog = scanRecordLogService.findScanRecordLog(id);

        return Result.ok(scanRecordLog);
    }

    @RequestMapping(path="/findAllScanRecordLog",method = RequestMethod.POST)
    @ApiMethod(name = "findAllScanRecordLog",desc = "查询所有扫描记录日志")
    public Result<List<ScanRecordLog>> findAllScanRecordLog(){
        List<ScanRecordLog> scanRecordLogList = scanRecordLogService.findAllScanRecordLog();

        return Result.ok(scanRecordLogList);
    }

    @RequestMapping(path = "/findScanRecordLogList",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecordLogList",desc = "条件查询扫描记录日志")
    @ApiParam(name = "scanRecordLogQuery",desc = "scanRecordLogQuery",required = true)
    public Result<List<ScanRecordLog>> findScanRecordLogList(@RequestBody @Valid @NotNull ScanRecordLogQuery scanRecordLogQuery){
        List<ScanRecordLog> scanRecordLogList = scanRecordLogService.findScanRecordLogList(scanRecordLogQuery);

        return Result.ok(scanRecordLogList);
    }

    @RequestMapping(path = "/findScanRecordLogPage",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecordLogPage",desc = "条件分页查询扫描记录日志")
    @ApiParam(name = "scanRecordLogQuery",desc = "scanRecordLogQuery",required = true)
    public Result<Pagination<ScanRecordLog>> findScanRecordLogPage(@RequestBody @Valid @NotNull ScanRecordLogQuery scanRecordLogQuery){
        Pagination<ScanRecordLog> pagination = scanRecordLogService.findScanRecordLogPage(scanRecordLogQuery);

        return Result.ok(pagination);
    }

}
