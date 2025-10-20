package io.tiklab.sourcefare.scan.controller;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.core.Result;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.sourcefare.scan.service.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.ServletInputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;


@RestController
@RequestMapping("/acceptClient")
//@Api(name = "CodeScanController",desc = "接受客户端信息")
@JsonIgnoreProperties(ignoreUnknown = true)
public class AcceptClientController {

    private static Logger logger = LoggerFactory.getLogger(AcceptClientController.class);

    @Autowired
    AcceptClientService acceptClientService;

    @Autowired
    CodeScanService codeScanService;

    @Autowired
    ScanSchemeRuleService schemeRuleService;

    @Autowired
    ScanRuleService scanRuleService;
    @RequestMapping(path="/acceptMessage",method = RequestMethod.POST)
    @ApiMethod(name = "acceptMessage",desc = "接收扫描信息")
    @ApiParam(name = "request",desc = "request",required = true)
    public Result<String> acceptMessage(HttpServletRequest request, HttpServletResponse response){

        String data = acceptClientService.acceptMessage(request);
        return Result.ok(data);
    }


    @RequestMapping(path="/acceptScanResult",method = RequestMethod.POST)
    @ApiMethod(name = "acceptScanResult",desc = "接收扫描结果")
    @ApiParam(name = "request",desc = "request",required = true)
    public Result<ScanRecord> acceptScanResult(HttpServletRequest request, HttpServletResponse response){

        codeScanService.acceptScanResult(request);
        return Result.ok(null);
    }

    @RequestMapping(path="/acceptScanCode",method = RequestMethod.POST)
    @ApiMethod(name = "acceptScanCode",desc = "接收代码")
    @ApiParam(name = "file",desc = "file",required = true)
    public Result<ScanRecord> acceptScanCode(@RequestParam("file") MultipartFile file){

        acceptClientService.acceptScanCode(file);
        return Result.ok(null);
    }

}
