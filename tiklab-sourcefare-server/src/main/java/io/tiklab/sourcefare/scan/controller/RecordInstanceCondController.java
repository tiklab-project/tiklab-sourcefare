package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.RecordInstanceCond;
import io.tiklab.sourcefare.scan.model.RecordInstanceCondQuery;
import io.tiklab.sourcefare.scan.service.RecordInstanceCondService;
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
 * RecordInstanceCondController
 */
@RestController
@RequestMapping("/recordInstanceCond")
//@Api(name = "RecordInstanceCondController",desc = "扫描记录实例的动态")
public class RecordInstanceCondController {

    private static Logger logger = LoggerFactory.getLogger(RecordInstanceCondController.class);

    @Autowired
    private RecordInstanceCondService scanRecordInstanceCondService;

    @RequestMapping(path="/createRecordInstanceCond",method = RequestMethod.POST)
    @ApiMethod(name = "createRecordInstanceCond",desc = "添加扫描记录实例的动态")
    @ApiParam(name = "scanRecordInstanceCond",desc = "scanRecordInstanceCond",required = true)
    public Result<String> createRecordInstanceCond(@RequestBody @Valid @NotNull RecordInstanceCond scanRecordInstanceCond){
        String scanRecordInstanceCondId = scanRecordInstanceCondService.createRecordInstanceCond(scanRecordInstanceCond);

        return Result.ok(scanRecordInstanceCondId);
    }

    @RequestMapping(path="/updateRecordInstanceCond",method = RequestMethod.POST)
    @ApiMethod(name = "updateRecordInstanceCond",desc = "更新扫描记录实例的动态")
    @ApiParam(name = "scanRecordInstanceCond",desc = "scanRecordInstanceCond",required = true)
    public Result<String> updateRecordInstanceCond(@RequestBody @Valid @NotNull RecordInstanceCond scanRecordInstanceCond){
         scanRecordInstanceCondService.updateRecordInstanceCond(scanRecordInstanceCond);

        return Result.ok();
    }


    @RequestMapping(path="/deleteRecordInstanceCond",method = RequestMethod.POST)
    @ApiMethod(name = "deleteRecordInstanceCond",desc = "删除扫描记录实例的动态")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteRecordInstanceCond(@NotNull String id){
        scanRecordInstanceCondService.deleteRecordInstanceCond(id);

        return Result.ok();
    }

    @RequestMapping(path="/findRecordInstanceCond",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordInstanceCond",desc = "通过id查询扫描记录实例的动态")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<RecordInstanceCond> findRecordInstanceCond(@NotNull String id){
        RecordInstanceCond scanRecordInstanceCond = scanRecordInstanceCondService.findRecordInstanceCond(id);

        return Result.ok(scanRecordInstanceCond);
    }

    @RequestMapping(path="/findAllRecordInstanceCond",method = RequestMethod.POST)
    @ApiMethod(name = "findAllRecordInstanceCond",desc = "查询所有扫描记录实例的动态")
    public Result<List<RecordInstanceCond>> findAllRecordInstanceCond(){
        List<RecordInstanceCond> scanRecordInstanceCondList = scanRecordInstanceCondService.findAllRecordInstanceCond();

        return Result.ok(scanRecordInstanceCondList);
    }

    @RequestMapping(path = "/findRecordInstanceCondList",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordInstanceCondList",desc = "条件查询扫描记录实例的动态")
    @ApiParam(name = "scanRecordInstanceCondQuery",desc = "scanRecordInstanceCondQuery",required = true)
    public Result<List<RecordInstanceCond>> findRecordInstanceCondList(@RequestBody @Valid @NotNull RecordInstanceCondQuery scanRecordInstanceCondQuery){
        List<RecordInstanceCond> scanRecordInstanceCondList = scanRecordInstanceCondService.findRecordInstanceCondList(scanRecordInstanceCondQuery);

        return Result.ok(scanRecordInstanceCondList);
    }

    @RequestMapping(path = "/findRecordInstanceCondPage",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordInstanceCondPage",desc = "条件分页查询扫描记录实例的动态")
    @ApiParam(name = "scanRecordInstanceCondQuery",desc = "scanRecordInstanceCondQuery",required = true)
    public Result<Pagination<RecordInstanceCond>> findRecordInstanceCondPage(@RequestBody @Valid @NotNull RecordInstanceCondQuery scanRecordInstanceCondQuery){
        Pagination<RecordInstanceCond> pagination = scanRecordInstanceCondService.findRecordInstanceCondPage(scanRecordInstanceCondQuery);

        return Result.ok(pagination);
    }



}
