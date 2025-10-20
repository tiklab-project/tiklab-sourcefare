package io.tiklab.sourcefare.project.controller;

import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.scan.model.ScanRule;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.toolkit.context.AppContext;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class test {

    public static void main(String[] args) throws Exception {
        String spotbugsFilePath= "/Users/limingliang/work/work-project/tiklab-sourcefare/tiklab-sourcefare-starter/file/spotbugs.json";
        File file = new File(spotbugsFilePath);
        String content = Files.readString(file.toPath(), StandardCharsets.UTF_8);
        // JSONArray resourcesNode = JSON.parseArray(content);

        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode jsonNode = objectMapper.readTree(content);
        List<Map> ruleSetList = objectMapper.convertValue(jsonNode, List.class);

        List<Map> arrayList = new ArrayList<>();
        for (Map ruleSet:ruleSetList){

            List<ScanRule> rules = new ArrayList<>();
            List<Map> ruleList = objectMapper.convertValue(ruleSet.get("ruleList"), List.class);
            for (Map rule:ruleList){

                Map<String, String> hashMap = new HashMap<>();
                String realName = rule.get("ruleName").toString();
                String severity = rule.get("problemLevel").toString();

                if (("0").equals(severity)){
                    hashMap.put("realName",realName);
                    hashMap.put("severity",severity);
                    arrayList.add(hashMap);
                }
            }
        }
        System.out.println("");
    }

}
