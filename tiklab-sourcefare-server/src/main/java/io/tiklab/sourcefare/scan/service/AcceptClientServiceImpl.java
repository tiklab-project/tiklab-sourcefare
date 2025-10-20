package io.tiklab.sourcefare.scan.service;

import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.core.exception.ApplicationException;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.project.service.ProjectService;
import io.tiklab.sourcefare.scan.common.CodeScanCommon;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.sourcefare.scanner.model.ScanResult;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;
import org.springframework.util.ObjectUtils;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.ServletInputStream;
import javax.servlet.http.HttpServletRequest;
import java.io.File;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

import static org.springframework.beans.BeanUtils.copyProperties;

@Service
public class AcceptClientServiceImpl implements AcceptClientService {
    private static Logger logger = LoggerFactory.getLogger(AcceptClientServiceImpl.class);
    @Autowired
    ProjectService  projectService;

    @Autowired
    ScanRecordService recordService;

    @Autowired
    ScanRecordLogService recordLogService;

    @Autowired
    CodeScanService codeScanService;

    @Autowired
    ScanSchemeRuleService schemeRuleService;

    @Autowired
    RecordInstanceService recordInstanceService;

    @Autowired
    PathSetService pathSetService;

    @Autowired
    ProjectCoverService coverService;

    @Autowired
    RecordDuplicatedService recordDuplicatedService;

    @Autowired
    RecordComplexityService recordComplexityService;

    @Autowired
    ScanDoorService scanDoorService;


    @Autowired
    IssueStatisticService issueStatisticService;


    @Override
    public String acceptMessage(HttpServletRequest request) {
        logger.info("接受到客户端消息-初始化扫描记录");
        try {
            ServletInputStream  inputStream = request.getInputStream();
            ObjectMapper mapper = new ObjectMapper();
            String projectId = mapper.readValue(inputStream, String.class);// 转换为对象

            Project project = projectService.findOne(projectId);
            if (ObjectUtils.isEmpty(project)){
                throw new ApplicationException("服务端projectKey不存在");
            }
            ScanRecord scanRecord = CodeScanCommon.initScanRecord(recordService, projectId,"client");
            logger.info("初始化扫描记录完成发送消息给客户端-初始化扫描记录");
            return scanRecord.getId();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }




   @Override
    public void acceptScanCode(MultipartFile file) {
       logger.info("接受到客户端提交的代码");
        try {
            String originalFilename = file.getOriginalFilename();
            String codePath = pathSetService.codePath() +"/"+ originalFilename;
            file.transferTo(new File(codePath));

            //解压
            String name = StringUtils.substringBefore(originalFilename, ".zip");
            String outputFolderPath = pathSetService.codePath() +"/"+ name;
            ProjectUtil.decompressionZip(codePath,outputFolderPath);
            new File(codePath).delete();

            String lastName = StringUtils.substringBefore(originalFilename, "-scanner");
            String lastCodePath = pathSetService.codePath() +"/"+ lastName;
            File repositoryFile = new File(lastCodePath);
            if (repositoryFile.exists() ){
                FileUtils.deleteDirectory(repositoryFile);
            }

          SourceFareUtil.updateDirName(outputFolderPath, lastCodePath, 1);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
}
