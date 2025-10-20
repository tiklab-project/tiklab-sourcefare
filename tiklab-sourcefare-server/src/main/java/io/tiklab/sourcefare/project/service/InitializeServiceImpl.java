



package io.tiklab.sourcefare.project.service;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.privilege.dmRole.model.DmRole;
import io.tiklab.privilege.dmRole.model.DmRoleQuery;
import io.tiklab.privilege.dmRole.service.DmRoleService;
import io.tiklab.privilege.role.model.Role;
import io.tiklab.privilege.role.service.RoleService;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.sourcefare.scan.service.*;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.toolkit.context.AppContext;
import io.tiklab.user.user.model.User;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.ObjectUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.Timestamp;
import java.util.*;
import java.util.stream.Collectors;

@Service
public class InitializeServiceImpl implements InitializeService {

    @Autowired
    ProjectService projectService;


    @Autowired
    ScanRuleSetService ruleSetService;

    @Autowired
    ScanSchemeService schemeService;

    @Autowired
    ScanSchemeRuleSetService schemeRuleSetService;

    @Autowired
    ScanSchemeRuleService scanSchemeRuleService;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    ScanRecordLogService scanRecordLogService;

    @Autowired
    RecordInstanceService scanRecordInstanceService;

    @Autowired
    RecordDuplicatedService duplicatedService;

    @Autowired
    RecordComplexityService complexityService;

    @Autowired
    IssueStatisticService issueStatisticService;

    @Autowired
    ProjectCoverService coverService;

    @Autowired
    ScanRuleService ruleService;

    @Autowired
    RoleService roleService;

    @Autowired
    DmRoleService dmRoleService;

    @Autowired
    PathSetService pathSetService;

    @Autowired
    ScanDoorService scanDoorService;

    @Override
    public void initData(){
        Thread thread = new Thread() {
            public void run() {
                addScanRule();
                createSampleData();
            }};

        thread.start();
    }

    public void createSampleData() {
        List<Project> demoProjectList = projectService.findDemoProjectList();
        if (CollectionUtils.isEmpty(demoProjectList)){
            Project project = new Project();
            project.setCategory("demo");
            project.setName("演示项目");

            User user = new User();
            user.setId("111111");
            project.setUser(user);
            project.setRules("public");
            project.setScanWay("client");
            project.setScanResult("success");
            project.setScanTime(new Timestamp(System.currentTimeMillis()));

            List<ScanScheme> scanSchemeList = schemeService.findScanSchemeList(new ScanSchemeQuery()
                    .setCategory(1)
                    .setLanguage("Java"));
            ScanScheme scanScheme = new ScanScheme();
            scanScheme.setId(scanSchemeList.get(0).getId());
            project.setScanScheme(scanScheme);

            String projectId = projectService.createProject(project);
            project.setId(projectId);
            //创建扫描记录
            ScanRecord scanRecord = new ScanRecord();

            scanRecord.setProjectId(projectId);
            scanRecord.setScanUser(user);
            scanRecord.setScanResult("success");
            scanRecord.setScanWay("client");
            scanRecord.setAllTrouble(3);
            scanRecord.setSeverityTrouble(1);
            scanRecord.setNoticeTrouble(1);
            scanRecord.setSuggestTrouble(1);


            scanRecord.setScanTime("1分7秒");
            String scanRecordId = scanRecordService.createScanRecord(scanRecord);
            try {
                //创建扫描日志
                String[] logTypes={"compile","scan","duplicated","complexity"};
                for (String logType:logTypes){
                    ScanRecordLog recordLog = new ScanRecordLog();
                    recordLog.setType(logType);
                    recordLog.setScanRecordId(scanRecordId);
                    recordLog.setProjectId(projectId);
                    if (("compile").equals(logType)){
                        String path=AppContext.getAppHome()+"/file/demo-compile-log.text";
                        String s = ProjectUtil.SystemTypeAddress(path);
                        String s1 = Files.readString(Paths.get(s));
                        recordLog.setTitle("项目构建");
                        recordLog.setTime("7秒");
                        recordLog.setSort(1);
                        recordLog.setExecLog(s1);
                    }
                    if (("scan").equals(logType)){
                        String path=AppContext.getAppHome()+"/file/demo-scan-log.text";
                        String s = ProjectUtil.SystemTypeAddress(path);
                        String s1 = Files.readString(Paths.get(s));
                        recordLog.setTitle("问题扫描");
                        recordLog.setTime("19秒");
                        recordLog.setSort(2);
                        recordLog.setExecLog(s1);
                    }

                    if (("duplicated").equals(logType)){
                        String path=AppContext.getAppHome()+"/file/demo-duplicated-log.text";
                        String s = ProjectUtil.SystemTypeAddress(path);
                        String s1 = Files.readString(Paths.get(s));
                        recordLog.setTitle("重复度扫描");
                        recordLog.setTime("20秒");
                        recordLog.setSort(3);
                        recordLog.setExecLog(s1);
                    }
                    if (("complexity").equals(logType)){
                        String path=AppContext.getAppHome()+"/file/demo-complexity-log.text";
                        String s = ProjectUtil.SystemTypeAddress(path);
                        String s1 = Files.readString(Paths.get(s));
                        recordLog.setTitle("复杂度扫描");
                        recordLog.setTime("21秒");
                        recordLog.setSort(4);
                        recordLog.setExecLog(s1);
                    }

                    scanRecordLogService.createScanRecordLog(recordLog);
                }

                //创建记录实例
                createRecordInstance(project,scanRecordId);

                //创建问题统计
                createIssueStatistic (project.getId(),scanRecordId);

                //创建重复率
                createDuplicated(project.getId(),scanRecordId);

                //创建复杂度
                createComplexity(project.getId(),scanRecordId);

                createCover(project.getId(),scanRecordId);

                String zipPath = ProjectUtil.SystemTypeAddress(AppContext.getAppHome()+"/file/706aef7e9fb6.zip");

                File zipFile = new File(zipPath);

                String s2 = pathSetService.codePath();
                String address = ProjectUtil.SystemTypeAddress(s2);

                //将zip 拷贝到租户存储仓库文件下面
                FileUtils.copyFileToDirectory(zipFile,new File(address));
                ProjectUtil.decompressionZip(address+"/706aef7e9fb6.zip",s2);

                //修改名字
                FileUtils.moveDirectory(new File(s2+"/706aef7e9fb6"), new File(s2+"/"+projectId));

                FileUtils.delete(new File(s2+"/706aef7e9fb6.zip"));
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }


    public void addScanRule() {
        List<ScanScheme> allScanScheme = schemeService.findAllScanScheme();
        List<ScanRuleSet> allScanRuleSet = ruleSetService.findAllScanRuleSet();

        List<String> arrayList = new ArrayList<>();
        arrayList.add("/file/eslint.json");
        arrayList.add("/file/spotbugs.json");
        arrayList.add("/file/golangci.json");
        arrayList.add("/file/pylint.json");
        //arrayList.add("/file/cpplint.json");
        arrayList.add("/file/semgrep.json");
        arrayList.add("/file/cppCheck.json");
        arrayList.add("/file/pmd.json");
        for (String fileName:arrayList){
            //创建扫描方案
            String schemeId = createScheme(allScanScheme, fileName);

            //创建快速扫描方案
            String startSchemeId = createQuickStartScheme(allScanScheme, fileName);

            File file = new File(AppContext.getAppHome() + fileName);
            try {

                String content = Files.readString(file.toPath(), StandardCharsets.UTF_8);
                // JSONArray resourcesNode = JSON.parseArray(content);

                ObjectMapper objectMapper = new ObjectMapper();
                JsonNode jsonNode = objectMapper.readTree(content);
                List<Map> ruleSetList = objectMapper.convertValue(jsonNode, List.class);
                for (Map ruleSet:ruleSetList){
                    Object ruleSetName1 = ruleSet.get("ruleSetName");
                    String ruleSetName = ruleSetName1.toString();
                    if (CollectionUtils.isNotEmpty(allScanRuleSet)){
                        List<ScanRuleSet> list = allScanRuleSet.stream().filter(a -> a.getRuleSetName().equals(ruleSetName)).collect(Collectors.toList());
                        if (CollectionUtils.isNotEmpty(list)){
                            String id = list.get(0).getId();
                            List<ScanSchemeRuleSet> schemeRuleSetList = schemeRuleSetService.findScanSchemeRuleSetList(new ScanSchemeRuleSetQuery()
                                    .setRuleSetId(id)
                                    .setScanSchemeId(schemeId));
                            if (CollectionUtils.isEmpty(schemeRuleSetList)) {
                                createSchemeSet(list.get(0),schemeId,ruleSet.get("language").toString());
                            }
                            continue;
                        }
                    }

                    //添加扫描规则集
                    ScanRuleSet scanRuleSet = new ScanRuleSet();
                    scanRuleSet.setRuleSetName(ruleSetName);
                    scanRuleSet.setLanguage(ruleSet.get("language").toString());
                    scanRuleSet.setDescribe(ruleSet.get("describe").toString());
                    String ruleSetId = ruleSetService.createScanRuleSet(scanRuleSet);
                    scanRuleSet.setId(ruleSetId);
                    //String schemeRuleSetId = createSchemeSet(scanRuleSet, schemeId, ruleSet.get("language").toString());


                    List<ScanRule> rules = new ArrayList<>();
                    List<Map> ruleList = objectMapper.convertValue(ruleSet.get("ruleList"), List.class);
                    for (Map rule:ruleList){
                        ScanRule scanRule = new ScanRule();
                        scanRule.setId(SourceFareUtil.getRandom(12));
                        scanRule.setRuleSetId(ruleSetId);
                        scanRule.setCreateTime(new Timestamp(System.currentTimeMillis()));
                        scanRule.setRuleName(rule.get("ruleName").toString().trim());
                        scanRule.setScanTool(rule.get("scanTool").toString());
                        scanRule.setProblemLevel(Integer.parseInt(rule.get("problemLevel").toString()));
                        scanRule.setRuleType(rule.get("ruleType").toString());
                        scanRule.setRuleOverview(rule.get("ruleOverview").toString());
                        /* String dsc = rule.get("desc").toString();*/
                        if (("Eslint").equals(rule.get("scanTool").toString())){
                            scanRule.setDescription("可参考官网："+rule.get("href").toString());
                        }
                        if (("SpotBugs").equals(rule.get("scanTool").toString())){
                            if (ObjectUtils.isNotEmpty(rule.get("desc"))){
                                scanRule.setDescription(rule.get("desc").toString());
                            }
                        }
                        if (("C++").equals(rule.get("scanTool").toString())){
                            if (ObjectUtils.isNotEmpty(rule.get("desc"))){
                                scanRule.setDescription(rule.get("desc").toString());
                            }
                        }
                        rules.add(scanRule);
                    }
                    ruleService.createScanRule(rules);



                    createSchemeSet(scanRuleSet,schemeId,ruleSet.get("language").toString());

                    if (StringUtils.isNotBlank(startSchemeId)){
                        //创建快速扫描规则
                        createQuickStartSchemeSet(scanRuleSet,startSchemeId,ruleSet.get("language").toString(),rules);
                    }
                }
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

    }

    @Override
    public void updateRepRole() {
        List<Role> allRole = roleService.findAllRole();


        if (CollectionUtils.isNotEmpty(allRole)) {
            for (Role role : allRole) {
                //移除项目管理员
                if ((("3").equals(role.getParentId())) || ("3").equals(role.getId())) {
                    roleService.deleteRole(role.getId());

                    DmRoleQuery dmRoleQuery = new DmRoleQuery();
                    dmRoleQuery.setRoleId(role.getId());
                    List<DmRole> dmRoleList = dmRoleService.findDmRoleListByQuery(dmRoleQuery);
                    if (CollectionUtils.isNotEmpty(dmRoleList)) {
                        for (DmRole dmRole : dmRoleList) {
                            dmRoleService.deleteDmRole(dmRole.getId());
                        }
                    }
                }

                //修改项目超级管理员
                if (("pro_111111").equals(role.getParentId()) || ("pro_111111").equals(role.getId())) {
                    role.setName("项目管理员");
                    roleService.updateRole(role);
                }

                if (("管理员角色").equals(role.getName())) {
                    role.setName("管理员");
                    roleService.updateRole(role);
                }
                if (("普通角色").equals(role.getName())) {
                    role.setName("普通用户");
                    roleService.updateRole(role);
                }
            }
        }
    }



    //创建扫描方案
    public String createScheme(List<ScanScheme> allScanScheme,String fileName){
        ScanScheme scanScheme = new ScanScheme();
        scanScheme.setScanWay("rule");
        scanScheme.setCategory(1);
        if (fileName.endsWith("spotbugs.json")){
            scanScheme.setSchemeName("Java推荐扫描方案");
            scanScheme.setDescribe("java推荐的扫描方案");
            scanScheme.setLanguage("Java");
        }
        if (fileName.endsWith("pmd.json")){
            scanScheme.setSchemeName("Java静态扫描推荐方案(深入扫描)");
            scanScheme.setDescribe("Java静态扫描推荐方案(深入扫描)");
            scanScheme.setLanguage("Java");
        }
        if (fileName.endsWith("eslint.json")){
            scanScheme.setSchemeName("JavaScript推荐扫描方案");
            scanScheme.setDescribe("JavaScript推荐的扫描方案");
            scanScheme.setLanguage("JavaScript");
        }
        if (fileName.endsWith("golangci.json")){
            scanScheme.setSchemeName("Go推荐扫描方案");
            scanScheme.setDescribe("Go推荐的扫描方案");
            scanScheme.setLanguage("Go");
        }
        if (fileName.endsWith("pylint.json")){
            scanScheme.setSchemeName("python推荐扫描方案");
            scanScheme.setDescribe("python推荐的扫描方案");
            scanScheme.setLanguage("Python");
        }
        if (fileName.endsWith("cppCheck.json")){
            scanScheme.setSchemeName("c++、c推荐扫描方案");
            scanScheme.setDescribe("c++、c推荐的扫描方案");
            scanScheme.setLanguage("c++");
        }
        if (fileName.endsWith("semgrep.json")){
            scanScheme.setSchemeName("c#推荐扫描方案");
            scanScheme.setDescribe("c#推荐的扫描方案");
            scanScheme.setLanguage("c#");
        }

        List<ScanScheme> collect=null;
        if (CollectionUtils.isNotEmpty(allScanScheme)){
             collect = allScanScheme.stream().filter(a -> scanScheme.getSchemeName().equals(a.getSchemeName())).collect(Collectors.toList());
        }

        //为空则创建
        if (CollectionUtils.isEmpty(collect)){
            return schemeService.createScanScheme(scanScheme);
        }
        return collect.get(0).getId();
    }

    //创建快速扫描方案
    public String createQuickStartScheme(List<ScanScheme> allScanScheme,String fileName){
        ScanScheme scanScheme = new ScanScheme();
        scanScheme.setScanWay("rule");
        scanScheme.setCategory(1);

        if (fileName.endsWith("pmd.json")){
            scanScheme.setSchemeName("Java静态扫描推荐方案(快速扫描)");
            scanScheme.setDescribe("Java静态扫描推荐方案(快速扫描)");
            scanScheme.setLanguage("Java");

            List<ScanScheme> collect=null;
            if (CollectionUtils.isNotEmpty(allScanScheme)){
                collect = allScanScheme.stream().filter(a -> scanScheme.getSchemeName().equals(a.getSchemeName())).collect(Collectors.toList());
            }

            //为空则创建
            if (CollectionUtils.isEmpty(collect)){
                return schemeService.createScanScheme(scanScheme);
            }
            return collect.get(0).getId();
        }

        return null;

    }


    //添加扫描方案规则集
    public String createSchemeSet(ScanRuleSet scanRuleSet,String schemeId,String language){
        if (ObjectUtils.isNotEmpty(schemeId)){
            //添加扫描规则方案
            ScanSchemeRuleSet scanSchemeRuleSet = new ScanSchemeRuleSet();
            scanSchemeRuleSet.setScanSchemeId(schemeId);
            scanSchemeRuleSet.setLanguage(language);
            scanSchemeRuleSet.setScanRuleSet(scanRuleSet);
            String schemeRuleSetId = schemeRuleSetService.createScanSchemeRuleSet(scanSchemeRuleSet);
            return schemeRuleSetId;
        }
        return null;
    }

    public void   createQuickStartSchemeSet(ScanRuleSet scanRuleSet,String schemeId,String language,List<ScanRule> rules) throws IOException {
        File file = new File(AppContext.getAppHome() + "/file/pmd-quickstart.json");
        String content = Files.readString(file.toPath(), StandardCharsets.UTF_8);
        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode jsonNode = objectMapper.readTree(content);
        List<String> ruleSetList = objectMapper.convertValue(jsonNode, List.class);

        if (CollectionUtils.isNotEmpty(ruleSetList)){
            //添加扫描规则方案
            ScanSchemeRuleSet scanSchemeRuleSet = new ScanSchemeRuleSet();
            scanSchemeRuleSet.setScanSchemeId(schemeId);
            scanSchemeRuleSet.setLanguage(language);
            scanSchemeRuleSet.setScanRuleSet(scanRuleSet);
            String schemeRuleSetId = schemeRuleSetService.createSchemeRuleSet(scanSchemeRuleSet);

            List<ScanRule> scanRuleList;
            if (ObjectUtils.isEmpty(rules)){
                 scanRuleList = ruleService.findScanRuleList(new ScanRuleQuery().setRuleSetId(scanSchemeRuleSet.getScanRuleSet().getId()));
            }else {
                scanRuleList=rules;
            }
            for (String rule:ruleSetList){
                List<ScanRule> scanRules = scanRuleList.stream().filter(a -> rule.equals(a.getRuleName())).collect(Collectors.toList());
                if (CollectionUtils.isNotEmpty(scanRules)){
                    ScanRule scanRule = scanRules.get(0);

                    ScanSchemeRule scanSchemeRule = new ScanSchemeRule();
                    scanSchemeRule.setScanSchemeId(schemeId);
                    scanSchemeRule.setSchemeRulesetId(schemeRuleSetId);
                    scanSchemeRule.setScanRule(scanRule);
                    scanSchemeRule.setProblemLevel(scanRule.getProblemLevel());
                    scanSchemeRuleService.createScanSchemeRule(scanSchemeRule);
                }
            }
        }
    }

    //创建记录实例
    public void createRecordInstance(Project project,String scanRecordId){
        Integer[] integers = {1, 2, 3,4};
        for (Integer leve:integers){
            RecordInstance recordInstance = new RecordInstance();
            recordInstance.setScanRecordId(scanRecordId);
            recordInstance.setProjectId(project.getId());
            recordInstance.setProblemLevel(leve);
            if (leve==1){
                recordInstance.setRuleType("function");
                recordInstance.setProblemLine(17);
                recordInstance.setFileName("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/UuidGenerator.java");
                recordInstance.setFilePath("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/UuidGenerator.java");
                recordInstance.setRuleName("RV_ABSOLUTE_VALUE_OF_HASHCODE");
                recordInstance.setProblemDesc("Bad attempt to compute absolute value of signed 32-bit hashcode in io.tiklab.hadess.common.UuidGenerator.<static initializer for UuidGenerator>()");
                recordInstance.setProblemOverview("Bad attempt to compute absolute value of signed 32-bit hashcode");
            }
            if (leve==2){
                recordInstance.setRuleType("function");
                recordInstance.setProblemLine(105);
                recordInstance.setFileName("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/RepositoryUtil.java");
                recordInstance.setFilePath("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/RepositoryUtil.java");
                recordInstance.setRuleName("RV_RETURN_VALUE_IGNORED_BAD_PRACTICE");
                recordInstance.setProblemDesc("Exceptional return value of java.io.File.createNewFile() ignored in io.tiklab.hadess.common.RepositoryUtil.initHelmIndexFile(String)");
                recordInstance.setProblemOverview("Method ignores exceptional return value");
            }
            if (leve==3){
                recordInstance.setRuleType("norm");
                recordInstance.setProblemLine(477);
                recordInstance.setFileName("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/RepositoryUtil.java");
                recordInstance.setFilePath("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/RepositoryUtil.java");
                recordInstance.setRuleName("REC_CATCH_EXCEPTION");
                recordInstance.setProblemDesc("Exception is caught when Exception is not thrown in io.tiklab.hadess.common.RepositoryUtil.getServerIp()");
                recordInstance.setProblemOverview("Exception is caught when Exception is not thrown");
            }
            if (leve==4){
                recordInstance.setRuleType("security");
                recordInstance.setProblemLevel(3);
                recordInstance.setProblemLine(1030);
                recordInstance.setFileName("tiklab-hadess-server/src/main/java/io/tiklab/hadess/upload/service/DockerUploadServiceImpl.java");
                recordInstance.setFilePath("tiklab-hadess-server/src/main/java/io/tiklab/hadess/upload/service/DockerUploadServiceImpl.java");
                recordInstance.setRuleName("OS_OPEN_STREAM");
                recordInstance.setProblemDesc("The method creates an IO stream object, does not assign it to any fields, pass it to other methods that might close it, or return it, and does not appear to close the stream on all paths out of the method. This may result in a file descriptor leak. It is generally a good idea to use a finally block to ensure that streams are closed.");
                recordInstance.setProblemOverview("Method may fail to close stream");
            }

           scanRecordInstanceService.createScanRecordInstance(recordInstance);
        }
    }

    //创建问题统计数据
    public void createIssueStatistic(String projectId,String scanRecordId){
        IssueStatistic issueStatistic = new IssueStatistic();
        issueStatistic.setProjectId(projectId);
        issueStatistic.setProblemState(0);

        issueStatistic.setRuleType("function");
        issueStatistic.setRuleName("RV_ABSOLUTE_VALUE_OF_HASHCODE");
        issueStatistic.setFilePath("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/UuidGenerator.java");
        issueStatistic.setProblemLevel(1);
        issueStatistic.setProblemLine(17);
        issueStatistic.setProblemDesc("Bad attempt to compute absolute value of signed 32-bit hashcode in io.tiklab.hadess.common.UuidGenerator.<static initializer for UuidGenerator>()");
        issueStatisticService.createIssueStatistic(issueStatistic);

        issueStatistic.setRuleType("function");
        issueStatistic.setRuleName("RV_RETURN_VALUE_IGNORED_BAD_PRACTICE");
        issueStatistic.setFilePath("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/RepositoryUtil.java");
        issueStatistic.setProblemLevel(2);
        issueStatistic.setProblemLine(105);
        issueStatistic.setProblemDesc("Exceptional return value of java.io.File.createNewFile() ignored in io.tiklab.hadess.common.RepositoryUtil.initHelmIndexFile(String)");
        issueStatisticService.createIssueStatistic(issueStatistic);

        issueStatistic.setRuleType("norm");
        issueStatistic.setRuleName("REC_CATCH_EXCEPTION");
        issueStatistic.setFilePath("tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/RepositoryUtil.java");
        issueStatistic.setProblemLevel(3);
        issueStatistic.setProblemLine(477);
        issueStatistic.setProblemDesc("Exception is caught when Exception is not thrown in io.tiklab.hadess.common.RepositoryUtil.getServerIp()");
        issueStatisticService.createIssueStatistic(issueStatistic);

        issueStatistic.setRuleType("security");
        issueStatistic.setRuleName("OS_OPEN_STREAM");
        issueStatistic.setFilePath("tiklab-hadess-server/src/main/java/io/tiklab/hadess/upload/service/DockerUploadServiceImpl.java");
        issueStatistic.setProblemLevel(3);
        issueStatistic.setProblemLine(1030);
        issueStatistic.setProblemDesc("Method may fail to close stream");
        issueStatisticService.createIssueStatistic(issueStatistic);
    }

    //创建覆盖率数据
    public void createDuplicated(String projectId,String scanRecordId){
        RecordDuplicated recordDuplicated = new RecordDuplicated();
        recordDuplicated.setProjectId(projectId);
        recordDuplicated.setRecordId(scanRecordId);
        recordDuplicated.setGroup("10119");
        recordDuplicated.setStartLine(21);
        recordDuplicated.setEndLine(33);
        recordDuplicated.setLines(13);
        recordDuplicated.setPath(projectId+"/tiklab-hadess-server/src/main/java/io/tiklab/hadess/upload/common/UploadTool.java");
        duplicatedService.createRecordDuplicated(recordDuplicated);

        recordDuplicated.setStartLine(43);
        recordDuplicated.setEndLine(57);
        recordDuplicated.setLines(13);
        recordDuplicated.setPath(projectId+"/tiklab-hadess-server/src/main/java/io/tiklab/hadess/upload/service/HandUploadServiceImpl.java");
        duplicatedService.createRecordDuplicated(recordDuplicated);

        recordDuplicated.setGroup("1901");
        recordDuplicated.setStartLine(132);
        recordDuplicated.setEndLine(147);
        recordDuplicated.setLines(16);
        recordDuplicated.setPath(projectId+"/tiklab-hadess-server/src/main/java/io/tiklab/hadess/pushcentral/entity/PushCenWarehouseImpl.java");
        duplicatedService.createRecordDuplicated(recordDuplicated);

        recordDuplicated.setStartLine(303);
        recordDuplicated.setEndLine(318);
        recordDuplicated.setLines(16);
        recordDuplicated.setPath(projectId+"/tiklab-hadess-server/src/main/java/io/tiklab/hadess/upload/service/HandUploadServiceImpl.java");
        duplicatedService.createRecordDuplicated(recordDuplicated);

    }

    //创建复杂度
    public void createComplexity(String projectId,String scanRecordId){
        RecordComplexity recordComplexity = new RecordComplexity();
        recordComplexity.setProjectId(projectId);
        recordComplexity.setRecordId(scanRecordId);
        recordComplexity.setMethod("RepositoryUtil");
        recordComplexity.setType("class");
        recordComplexity.setComplexityNum(107);
        recordComplexity.setPath(projectId+"/tiklab-hadess-server/src/main/java/io/tiklab/hadess/common/RepositoryUtil.java");
        complexityService.createRecordComplexity(recordComplexity);

        recordComplexity.setMethod("hadessPush");
        recordComplexity.setType("method");
        recordComplexity.setComplexityNum(13);
        recordComplexity.setPath(projectId+"/tiklab-hadess-server/src/main/java/io/tiklab/hadess/pushcentral/service/PushOperationServiceImpl.java");
        complexityService.createRecordComplexity(recordComplexity);

        recordComplexity.setMethod("npmPush");
        recordComplexity.setType("method");
        recordComplexity.setComplexityNum(10);
        recordComplexity.setPath(projectId+"/tiklab-hadess-server/src/main/java/io/tiklab/hadess/pushcentral/service/PushOperationServiceImpl.java");
        complexityService.createRecordComplexity(recordComplexity);

        recordComplexity.setMethod("updateRepRole");
        recordComplexity.setType("method");
        recordComplexity.setComplexityNum(11);
        recordComplexity.setPath(projectId+"/tiklab-hadess-server/src/main/java/io/tiklab/hadess/repository/service/InitializeSampleServiceImpl.java");
        complexityService.createRecordComplexity(recordComplexity);
    }

    //创建覆盖率
    public void createCover(String projectId,String scanRecordId){
        ProjectCover projectCover = new ProjectCover();
        projectCover.setProjectId(projectId);
        projectCover.setScanRecordId(scanRecordId);
        projectCover.setType("package");
        projectCover.setName("io.tiklab.hadess.pushcentral.dao");
        projectCover.setPath("io/tiklab/hadess/pushcentral/dao");
        projectCover.setInstructions(340);
        projectCover.setInstructionsMissed(330);
        projectCover.setInstructionsPercent("1%");
        projectCover.setBranch(14);
        projectCover.setBranchMissed(14);
        projectCover.setBranchPercent("0%");
        projectCover.setComplexity(32);
        projectCover.setComplexityMissed(31);
        projectCover.setLine(81);
        projectCover.setLineMissed(60);
        projectCover.setMethods(25);
        projectCover.setMethodsMissed(10);
        projectCover.setClasses(2);
        projectCover.setClassesMissed(0);
        coverService.createProjectCover(projectCover);

        projectCover.setType("class");
        projectCover.setName("PushLibraryDao");
        projectCover.setPath("io/tiklab/hadess/pushcentral/dao/PushLibraryDao");
        projectCover.setParentPath("io/tiklab/hadess/pushcentral/dao");
        projectCover.setInstructions(255);
        projectCover.setInstructionsMissed(250);
        projectCover.setInstructionsPercent("1%");
        projectCover.setBranch(14);
        projectCover.setBranchMissed(14);
        projectCover.setBranchPercent("0%");
        projectCover.setComplexity(21);
        projectCover.setComplexityMissed(18);
        projectCover.setLine(58);
        projectCover.setLineMissed(50);
        projectCover.setMethods(14);
        projectCover.setMethodsMissed(14);
        projectCover.setClasses(1);
        projectCover.setClassesMissed(1);
        coverService.createProjectCover(projectCover);

        projectCover.setType("method");
        projectCover.setName("PushLibraryDao()");
        projectCover.setPath("io/tiklab/hadess/pushcentral/dao/PushLibraryDao");
        projectCover.setParentPath("io/tiklab/hadess/pushcentral/dao/PushLibraryDao");
        projectCover.setComplexity(1);
        projectCover.setComplexityMissed(1);
        projectCover.setLine(1);
        projectCover.setLineMissed(1);
        projectCover.setMethods(1);
        projectCover.setMethodsMissed(1);
        coverService.createProjectCover(projectCover);

    }
}
