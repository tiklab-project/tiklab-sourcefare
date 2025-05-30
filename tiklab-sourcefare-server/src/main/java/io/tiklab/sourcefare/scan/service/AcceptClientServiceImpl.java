package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.common.CodeScanCommon;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.sourcefare.scanner.common.ScanCommon;
import io.tiklab.sourcefare.scanner.model.ScanResult;
import org.apache.commons.io.FileUtils;
import org.eclipse.jgit.util.IO;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.ObjectUtils;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.ServletInputStream;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardCopyOption;
import java.util.List;

import static org.springframework.beans.BeanUtils.copyProperties;

@Service
public class AcceptClientServiceImpl {

    @Autowired
    ScanPlayService scanPlayService;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    CodeScanService codeScanService;

    @Autowired
    ScanSchemeRuleService schemeRuleService;

    @Autowired
    ScanRecordInstanceService recordInstanceService;

    @Autowired
    PathSetService pathSetService;


    public void acceptClient(ScanResult scanResult) {
        String scanObjectId = scanResult.getScanObjectId();
        ScanPlay scanPlay = scanPlayService.findOne(scanObjectId);
        ScanScheme scanScheme = scanPlay.getScanScheme();

        //初始化扫描记录
        ScanRecord scanRecord = CodeScanCommon.initScanRecord(scanRecordService,scanPlay);
        scanRecord.setExecLog(scanResult.getLog());

        //扫描成功创建扫描文件信息
        if (!ObjectUtils.isEmpty(scanResult)){
            if (("success").equals(scanResult.getResult())){

                //查询扫描方案关联的扫描规则
                List<ScanSchemeRule> schemeRuleList = schemeRuleService.findScanSchemeRuleList(new ScanSchemeRuleQuery().setScanSchemeId(scanScheme.getId()));
                List<ScanSchemeRule> scanSchemeRules = schemeRuleList.stream().filter(a -> a.getIsDisable() == 0).toList();

             /*   io.tiklab.sourcefare.scanner.model.ScanResult result = new io.tiklab.sourcefare.scanner.model.ScanResult();
                copyProperties(scanResult, result);*/


                //创建扫描结果文件
                CodeScanCommon.createRecordInstance(scanSchemeRules,recordInstanceService,scanRecord,scanResult);
            }
        }
        String data = ("0秒").equals(scanResult.getScanTime()) ? "1秒" : scanResult.getScanTime();
        scanRecord.setScanTime(data);
        scanRecord.setScanResult(scanResult.getResult());
        scanRecord.setExecLog(scanResult.getLog());
        scanRecordService.updateScanRecord(scanRecord);
    }


    public void acceptScanCode(MultipartFile file) {
        try {
            String codePath = pathSetService.codePath() +"/"+ file.getOriginalFilename() ;
            file.transferTo(new File(codePath));




        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        /*
        // 自动创建父目录（如果不存在）
        try {
            String codePath = pathSetService.codePath() + "/test11213" ;

            Path targetPath = Paths.get(codePath);
            Files.createDirectories(targetPath.getParent());
            // 写入文件（覆盖已存在文件）
            Files.copy(inputStream, targetPath, StandardCopyOption.REPLACE_EXISTING);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }*/
    }
}
