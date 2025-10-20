package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.service.CodeScanService;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.constraints.NotNull;
import java.util.Map;

@RestController
@RequestMapping("/codeScan")
//@Api(name = "CodeScanController",desc = "代码扫描管理")
public class CodeScanController {

    @Autowired
    CodeScanService codeScanService;

    @RequestMapping(path="/codeScanExec",method = RequestMethod.POST)
    @ApiMethod(name = "CodeScanExec",desc = "执行代码扫描")
    @ApiParam(name = "projectId",desc = "projectId",required = true)
    public Result<ScanRecord> codeScanExec( @NotNull String  projectId){
        ScanRecord scanExec = codeScanService.codeScanExec(projectId);

        return Result.ok(scanExec);
    }

    @RequestMapping(path="/findScanState",method = RequestMethod.POST)
    @ApiMethod(name = "findScanState",desc = "查询扫描日志")
    @ApiParam(name = "projectId",desc = "projectId",required = true)
    public Result<Map<String,Object>> findScanState( @NotNull String  projectId,@NotNull String recordId){
        Map<String,Object> scanExec = codeScanService.findScanState(projectId,recordId);

        return Result.ok(scanExec);
    }

}
