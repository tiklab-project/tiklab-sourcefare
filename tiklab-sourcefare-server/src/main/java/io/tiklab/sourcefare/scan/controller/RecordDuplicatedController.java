package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.RecordDuplicated;
import io.tiklab.sourcefare.scan.model.RecordDuplicatedQuery;
import io.tiklab.sourcefare.scan.service.RecordDuplicatedService;
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
 * RecordDuplicatedController
 */
@RestController
@RequestMapping("/recordDuplicated")
//@Api(name = "RecordDuplicatedController",desc = "扫描记录扫描重复度")
public class RecordDuplicatedController {

    private static Logger logger = LoggerFactory.getLogger(RecordDuplicatedController.class);

    @Autowired
    private RecordDuplicatedService recordDuplicatedService;

    @RequestMapping(path="/createRecordDuplicated",method = RequestMethod.POST)
    @ApiMethod(name = "createRecordDuplicated",desc = "添加扫描记录扫描重复度")
    @ApiParam(name = "recordDuplicated",desc = "recordDuplicated",required = true)
    public Result<String> createRecordDuplicated(@RequestBody @Valid @NotNull RecordDuplicated recordDuplicated){
        String recordDuplicatedId = recordDuplicatedService.createRecordDuplicated(recordDuplicated);

        return Result.ok(recordDuplicatedId);
    }

    @RequestMapping(path="/updateRecordDuplicated",method = RequestMethod.POST)
    @ApiMethod(name = "updateRecordDuplicated",desc = "更新扫描记录扫描重复度")
    @ApiParam(name = "recordDuplicated",desc = "recordDuplicated",required = true)
    public Result<String> updateRecordDuplicated(@RequestBody @Valid @NotNull RecordDuplicated recordDuplicated){
         recordDuplicatedService.updateRecordDuplicated(recordDuplicated);

        return Result.ok();
    }


    @RequestMapping(path="/deleteRecordDuplicated",method = RequestMethod.POST)
    @ApiMethod(name = "deleteRecordDuplicated",desc = "删除扫描记录扫描重复度")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteRecordDuplicated(@NotNull String id){
        recordDuplicatedService.deleteRecordDuplicated(id);

        return Result.ok();
    }

    @RequestMapping(path="/findRecordDuplicated",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordDuplicated",desc = "通过id查询扫描记录扫描重复度")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<RecordDuplicated> findRecordDuplicated(@NotNull String id){
        RecordDuplicated recordDuplicated = recordDuplicatedService.findRecordDuplicated(id);

        return Result.ok(recordDuplicated);
    }


    @RequestMapping(path="/findAllRecordDuplicated",method = RequestMethod.POST)
    @ApiMethod(name = "findAllRecordDuplicated",desc = "查询所有扫描记录扫描重复度")
    public Result<List<RecordDuplicated>> findAllRecordDuplicated(){
        List<RecordDuplicated> recordDuplicatedList = recordDuplicatedService.findAllRecordDuplicated();

        return Result.ok(recordDuplicatedList);
    }

    @RequestMapping(path = "/findRecordDuplicatedList",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordDuplicatedList",desc = "条件查询扫描记录扫描重复度")
    @ApiParam(name = "recordDuplicatedQuery",desc = "recordDuplicatedQuery",required = true)
    public Result<List<RecordDuplicated>> findRecordDuplicatedList(@RequestBody @Valid @NotNull RecordDuplicatedQuery recordDuplicatedQuery){
        List<RecordDuplicated> recordDuplicatedList = recordDuplicatedService.findRecordDuplicatedList(recordDuplicatedQuery);

        return Result.ok(recordDuplicatedList);
    }

    @RequestMapping(path = "/findRecordDuplicatedPage",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordDuplicatedPage",desc = "条件分页查询扫描记录扫描重复度")
    @ApiParam(name = "recordDuplicatedQuery",desc = "recordDuplicatedQuery",required = true)
    public Result<Pagination<RecordDuplicated>> findRecordDuplicatedPage(@RequestBody @Valid @NotNull RecordDuplicatedQuery recordDuplicatedQuery){
        Pagination<RecordDuplicated> pagination = recordDuplicatedService.findRecordDuplicatedPage(recordDuplicatedQuery);

        return Result.ok(pagination);
    }
}
