package io.tiklab.sourcefare.scan.controller;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.core.Result;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.service.AcceptClientService;
import io.tiklab.sourcefare.scan.service.AcceptClientServiceImpl;
import io.tiklab.sourcefare.scanner.model.ScanResult;
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

import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;


@RestController
@RequestMapping("/acceptClient")
@Api(name = "CodeScanController",desc = "接受客户端信息")
@JsonIgnoreProperties(ignoreUnknown = true)
public class AcceptClientController {

    private static Logger logger = LoggerFactory.getLogger(AcceptClientController.class);

    @Autowired
    AcceptClientServiceImpl acceptClient;

    @RequestMapping(path="/acceptScanResult",method = RequestMethod.POST)
    @ApiMethod(name = "acceptScanResult",desc = "接收扫描结果")
    @ApiParam(name = "scanPlay",desc = "scanPlay",required = true)
    public Result<ScanRecord> acceptScanResult(HttpServletRequest request, HttpServletResponse response){
        logger.info("接受到客户端消息");
        try {

            ServletInputStream inputStream = request.getInputStream();

            ObjectMapper mapper = new ObjectMapper();
            ScanResult scanResult = mapper.readValue(inputStream, ScanResult.class);// 转换为对象
            acceptClient.acceptClient(scanResult);
            logger.info("完成消息发送消息给客户端");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        return Result.ok(null);
    }

    @RequestMapping(path="/acceptScanCode",method = RequestMethod.POST)
    @ApiMethod(name = "acceptScanResult",desc = "接收代码")
    @ApiParam(name = "request",desc = "request",required = true)
    public Result<ScanRecord> acceptScanCode(@RequestParam("file") MultipartFile file){
        logger.info("接受到客户端提交的代码");
        acceptClient.acceptScanCode(file);
        return Result.ok(null);
    }
}
