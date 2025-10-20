package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.SystemCount;
import io.tiklab.sourcefare.project.service.SystemCountService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

//系统设置汇总
@RestController
@RequestMapping("/systemCount")
public class SystemCountController {

    @Autowired
    private SystemCountService systemCountService;

    @RequestMapping(path="/collectCount",method = RequestMethod.POST)
    @ApiMethod(name = "createAuth",desc = "系统设置汇总")
    @ApiParam(name = "auth",desc = "auth",required = true)
    public Result<SystemCount> collectCount(){

        SystemCount systemCount = systemCountService.collectCount();

        return Result.ok(systemCount);
    }
}
