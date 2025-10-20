package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.RecordComplexity;
import io.tiklab.sourcefare.scan.model.RecordComplexityQuery;
import io.tiklab.sourcefare.scan.service.RecordComplexityService;
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
 * RecordComplexityController
 */
@RestController
@RequestMapping("/recordComplexity")
//@Api(name = "RecordComplexityController",desc = "扫描记录扫描复杂度")
public class RecordComplexityController {

    private static Logger logger = LoggerFactory.getLogger(RecordComplexityController.class);

    @Autowired
    private RecordComplexityService recordComplexityService;

    @RequestMapping(path="/createRecordComplexity",method = RequestMethod.POST)
    @ApiMethod(name = "createRecordComplexity",desc = "添加扫描记录扫描复杂度")
    @ApiParam(name = "recordComplexity",desc = "recordComplexity",required = true)
    public Result<String> createRecordComplexity(@RequestBody @Valid @NotNull RecordComplexity recordComplexity){
        String recordComplexityId = recordComplexityService.createRecordComplexity(recordComplexity);

        return Result.ok(recordComplexityId);
    }

    @RequestMapping(path="/updateRecordComplexity",method = RequestMethod.POST)
    @ApiMethod(name = "updateRecordComplexity",desc = "更新扫描记录扫描复杂度")
    @ApiParam(name = "recordComplexity",desc = "recordComplexity",required = true)
    public Result<String> updateRecordComplexity(@RequestBody @Valid @NotNull RecordComplexity recordComplexity){
         recordComplexityService.updateRecordComplexity(recordComplexity);

        return Result.ok();
    }


    @RequestMapping(path="/deleteRecordComplexity",method = RequestMethod.POST)
    @ApiMethod(name = "deleteRecordComplexity",desc = "删除扫描记录扫描复杂度")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteRecordComplexity(@NotNull String id){
        recordComplexityService.deleteRecordComplexity(id);

        return Result.ok();
    }

    @RequestMapping(path="/findRecordComplexity",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordComplexity",desc = "通过id查询扫描记录扫描复杂度")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<RecordComplexity> findRecordComplexity(@NotNull String id){
        RecordComplexity recordComplexity = recordComplexityService.findRecordComplexity(id);

        return Result.ok(recordComplexity);
    }


    @RequestMapping(path="/findAllRecordComplexity",method = RequestMethod.POST)
    @ApiMethod(name = "findAllRecordComplexity",desc = "查询所有扫描记录扫描复杂度")
    public Result<List<RecordComplexity>> findAllRecordComplexity(){
        List<RecordComplexity> recordComplexityList = recordComplexityService.findAllRecordComplexity();

        return Result.ok(recordComplexityList);
    }

    @RequestMapping(path = "/findRecordComplexityList",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordComplexityList",desc = "条件查询扫描记录扫描复杂度")
    @ApiParam(name = "recordComplexityQuery",desc = "recordComplexityQuery",required = true)
    public Result<List<RecordComplexity>> findRecordComplexityList(@RequestBody @Valid @NotNull RecordComplexityQuery recordComplexityQuery){
        List<RecordComplexity> recordComplexityList = recordComplexityService.findRecordComplexityList(recordComplexityQuery);

        return Result.ok(recordComplexityList);
    }

    @RequestMapping(path = "/findRecordComplexityPage",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordComplexityPage",desc = "条件分页查询扫描记录扫描复杂度")
    @ApiParam(name = "recordComplexityQuery",desc = "recordComplexityQuery",required = true)
    public Result<Pagination<RecordComplexity>> findRecordComplexityPage(@RequestBody @Valid @NotNull RecordComplexityQuery recordComplexityQuery){
        Pagination<RecordComplexity> pagination = recordComplexityService.findRecordComplexityPage(recordComplexityQuery);

        return Result.ok(pagination);
    }
}
