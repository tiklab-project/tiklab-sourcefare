package io.tiklab.sourcefare.common;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.sourcefare.scan.model.ScanRule;
import io.tiklab.sourcefare.scan.model.ScanRuleSet;
import io.tiklab.sourcefare.scan.service.ScanRuleService;
import io.tiklab.sourcefare.scan.service.ScanRuleSetService;
import io.tiklab.toolkit.context.AppContext;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.ObjectUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.constraints.NotNull;
import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.sql.Timestamp;
import java.util.*;
import java.util.stream.Collectors;

@Service
public class InitializeServiceImpl implements InitializeService{

    @Autowired
    ScanRuleSetService ruleSetService;

    @Autowired
    ScanRuleService ruleService;

    @Override
    public void addScanRule() {
        List<String> arrayList = new ArrayList<>();
        arrayList.add("/file/eslint.json");
        arrayList.add("/file/spotbugs.json");
        for (String fileName:arrayList){
            File file = new File(AppContext.getAppHome() + fileName);
            try {

                String content = Files.readString(file.toPath(), StandardCharsets.UTF_8);
                // JSONArray resourcesNode = JSON.parseArray(content);

                ObjectMapper objectMapper = new ObjectMapper();
                JsonNode jsonNode = objectMapper.readTree(content);
                List<Map> ruleSetList = objectMapper.convertValue(jsonNode, List.class);

                List<ScanRuleSet> allScanRuleSet = ruleSetService.findAllScanRuleSet();
                for (Map ruleSet:ruleSetList){
                    String ruleSetName = ruleSet.get("ruleSetName").toString();
                    if (CollectionUtils.isNotEmpty(allScanRuleSet)){
                        List<ScanRuleSet> list = allScanRuleSet.stream().filter(a -> a.getRuleSetName().equals(ruleSetName)).collect(Collectors.toList());
                        if (CollectionUtils.isNotEmpty(list)){
                            continue;
                        }
                    }

                    ScanRuleSet scanRuleSet = new ScanRuleSet();
                    scanRuleSet.setRuleSetName(ruleSetName);
                    scanRuleSet.setLanguage(ruleSet.get("language").toString());
                    scanRuleSet.setDescribe(ruleSet.get("describe").toString());

                    String ruleSetId = ruleSetService.createScanRuleSet(scanRuleSet);

                    List<ScanRule> rules = new ArrayList<>();
                    List<Map> ruleList = objectMapper.convertValue(ruleSet.get("ruleList"), List.class);
                    for (Map rule:ruleList){
                        ScanRule scanRule = new ScanRule();
                        scanRule.setId(SourceFareUtil.getRandom(12));
                        scanRule.setRuleSetId(ruleSetId);
                        scanRule.setCreateTime(new Timestamp(System.currentTimeMillis()));
                        scanRule.setRuleName(rule.get("ruleName").toString());
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
                        rules.add(scanRule);
                    }

                    //  String ruleSql = getRuleSql(rules);
                    ruleService.createScanRule(rules);
                }


            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }

}
