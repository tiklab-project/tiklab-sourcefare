package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.service.OverviewService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.constraints.NotNull;

/**
 * DeployEnvController
 */
@RestController
@RequestMapping("/overview")
//@Api(name = "OverviewController",desc = "扫描概览")
public class OverviewController {

    @Autowired
    OverviewService overviewService;


    @RequestMapping(path="/findScanRecordStat",method = RequestMethod.POST)
    @ApiMethod(name = "findScanRecord",desc = "统计扫描记录")
    @ApiParam(name = "recordId",desc = "recordId",required = true)
    public Result<ScanRecord> findScanRecordStat(@NotNull String recordId){
        ScanRecord scanRecord = overviewService.findScanRecordStat(recordId);

        return Result.ok(scanRecord);
    }

    @RequestMapping(path="/findProjectCoverStat",method = RequestMethod.POST)
    @ApiMethod(name = "findProjectCoverStat",desc = "通过扫描记录id查询扫描覆盖率统计")
    @ApiParam(name = "recordId",desc = "recordId",required = true)
    public Result<Object> findProjectCoverStat(@NotNull String recordId){
        Object projectCover = overviewService.findProjectCoverStat(recordId);

        return Result.ok(projectCover);
    }

    @RequestMapping(path="/findMetricStat",method = RequestMethod.POST)
    @ApiMethod(name = "findMetricStat",desc = "通过扫描记录id查询扫描重复率、圈复杂度")
    @ApiParam(name = "recordId",desc = "recordId",required = true)
    public Result<Object> findMetricStat(@NotNull String recordId,@NotNull String projectId){
        Object duplicated = overviewService.findMetricStat(recordId,projectId);

        return Result.ok(duplicated);
    }
}
