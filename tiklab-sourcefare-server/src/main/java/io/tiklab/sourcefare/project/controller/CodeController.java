package io.tiklab.sourcefare.project.controller;

import io.tiklab.core.Result;
import io.tiklab.core.page.Pagination;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.project.service.CodeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.constraints.NotNull;

@RestController
@RequestMapping("/code")
@Api(name = "CodeController",desc = "代码")
public class CodeController {

    @Autowired
    CodeService codeService;


    @RequestMapping(path = "/findCodeData",method = RequestMethod.POST)
    @ApiMethod(name = "findCodeData",desc = "查询代码内容")
    @ApiParam(name = "filePath",desc = "filePath",required = true)
    public Result<String> findCodeData(@NotNull  String filePath){
        String code = codeService.findCodeData(filePath);

        return Result.ok(code);
    }
}
