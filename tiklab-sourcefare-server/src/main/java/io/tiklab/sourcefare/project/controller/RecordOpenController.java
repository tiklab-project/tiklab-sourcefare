package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.RecordOpen;
import io.tiklab.sourcefare.project.model.RecordOpenQuery;
import io.tiklab.sourcefare.project.service.RecordOpenService;
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
 * RecordOpenController
 */
@RestController
@RequestMapping("/recordOpen")
//@Api(name = "RecordOpenController",desc = "打开仓库的记录管理")
public class RecordOpenController {

    private static Logger logger = LoggerFactory.getLogger(RecordOpenController.class);

    @Autowired
    private RecordOpenService recordOpenService;

    @RequestMapping(path="/createRecordOpen",method = RequestMethod.POST)
    @ApiMethod(name = "createRecordOpen",desc = "创建打开仓库记录管理")
    @ApiParam(name = "recordOpen",desc = "recordOpen",required = true)
    public Result<String> createRecordOpen(@RequestBody @NotNull @Valid RecordOpen recordOpen){
        String id = recordOpenService.createRecordOpen(recordOpen);

        return Result.ok(id);
    }

    @RequestMapping(path="/updateRecordOpen",method = RequestMethod.POST)
    @ApiMethod(name = "updateRecordOpen",desc = "修改打开仓库记录管理")
    @ApiParam(name = "recordOpen",desc = "recordOpen",required = true)
    public Result<Void> updateRecordOpen(@RequestBody @NotNull @Valid RecordOpen recordOpen){
        recordOpenService.updateRecordOpen(recordOpen);

        return Result.ok();
    }

    @RequestMapping(path="/deleteRecordOpen",method = RequestMethod.POST)
    @ApiMethod(name = "deleteRecordOpen",desc = "删除")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<Void> deleteRecordOpen(@NotNull String id){
        recordOpenService.deleteRecordOpen(id);

        return Result.ok();
    }

    @RequestMapping(path="/findRecordOpen",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordOpen",desc = "通过id 查询")
    @ApiParam(name = "id",desc = "id",required = true)
    public Result<RecordOpen> findRecordOpen(@NotNull String id){
        RecordOpen RecordOpen = recordOpenService.findRecordOpen(id);

        return Result.ok(RecordOpen);
    }

    @RequestMapping(path="/findAllRecordOpen",method = RequestMethod.POST)
    @ApiMethod(name = "findAllRecordOpen",desc = "查询所有查询")
    public Result<List<RecordOpen>> findAllRecordOpen(){
        List<RecordOpen> artifactList = recordOpenService.findAllRecordOpen();

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findRecordOpenList",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordOpenList",desc = "通过条件查询")
    @ApiParam(name = "recordOpenQuery",desc = "recordOpenQuery",required = true)
    public Result<List<RecordOpen>> findRecordOpenList(@RequestBody @Valid @NotNull RecordOpenQuery recordOpenQuery){
        List<RecordOpen> artifactList = recordOpenService.findRecordOpenList(recordOpenQuery);

        return Result.ok(artifactList);
    }

    @RequestMapping(path = "/findRecordOpenPage",method = RequestMethod.POST)
    @ApiMethod(name = "findRecordOpenPage",desc = "通过条件分页查询")
    @ApiParam(name = "recordOpenQuery",desc = "recordOpenQuery",required = true)
    public Result<Pagination<RecordOpen>> findRecordOpenPage(@RequestBody @Valid @NotNull RecordOpenQuery recordOpenQuery){
        Pagination<RecordOpen> pagination = recordOpenService.findRecordOpenPage(recordOpenQuery);

        return Result.ok(pagination);
    }


}
