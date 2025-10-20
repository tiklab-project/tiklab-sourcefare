package io.tiklab.sourcefare.common;

import com.alibaba.fastjson.JSONObject;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.sun.tools.javac.Main;
import org.apache.commons.lang3.ObjectUtils;
import org.apache.commons.lang3.StringUtils;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import org.springframework.util.CollectionUtils;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.logging.Level;
import java.util.stream.Collectors;

public class PullRule {
    public static void main(String[] args) throws IOException {

       // eslint();

        //spotbugs();

        //golangci();

       // pylint();

        //semgrep();

        //cppCheck();

        pmd();

    }


    public static void spotbugs() throws IOException {

       String url="https://spotbugs.readthedocs.io/en/stable/bugDescriptions.html" ;
        String filePath = getDirPath("spotbugs.html");
        File file = new File(filePath + "/file/spotbugs.html");
        Path path = Paths.get(file.getPath());

      /*  // 如果文件不存在则创建文件
        if (Files.exists(path)) {
            Files.delete(path);
        }

        String jsonObject = SourceFareUtil.restTemplateGet(url);
        Files.write(path, jsonObject.getBytes());*/

        analysisSpotBugsXml(path);
    }


    public static void analysisSpotBugsXml(Path path) throws IOException {
        List<Map> leaveData = getLeaveData("java");

        String s = Files.readString(path);
        // 解析 HTML
        Document document = Jsoup.parse(s);

        Elements docsDivs = document.select("section");
        List<Map> arrayList = new ArrayList<>();
        String h2Text=null;
        for (Element docsDiv : docsDivs) {
            String  section1 = docsDiv.attr("id");

            //开发规范
            if (section1.equals("bad-practice-bad-practice")||     //不良写法
                section1.equals("experimental-experimental")||     //实验性规则
                section1.equals("internationalization-i18n")||       // 国际化
                section1.equals("dodgy-code-style")) {  //可疑代码
                Integer grade=0;


                Elements allElements = docsDiv.children();
                analysisElement(arrayList,leaveData,allElements,grade,"norm");
            }

            //安全
            if (section1.equals("malicious-code-vulnerability-malicious-code")||     //恶意代码漏洞
                section1.equals("security-security")  ){  //安全

                Integer grade=0;


                Elements allElements = docsDiv.children();
                analysisElement(arrayList,leaveData,allElements,grade,"security");
            }

            //功能
            if (section1.equals("multithreaded-correctness-mt-correctness")|| //多线程正确性
                section1.equals("performance-performance")||
                section1.equals("correctness-correctness")||
                section1.equals("bogus-random-noise-noise")){

                //性能
                Integer grade=0;

                Elements allElements = docsDiv.children();
                analysisElement(arrayList,leaveData,allElements,grade,"function");
            }
        }
        addDataFile(arrayList,"Java");
    }

    //解析子集Element
    public static void analysisElement(List<Map> arrayList,
                                       List<Map> leaveDataList,
                                       Elements allElements,
                                       Integer grade,String type){
        for (int i = 0; i < allElements.size(); i++) {
            Element element = allElements.get(i);
            String tagName = element.tagName();
            if (tagName.equals("section")){
                Elements children = element.children();

                Map<String, String> hashMap=null;
                for (int a = 0; a < children.size(); a++) {
                    Element element1 = children.get(a);
                    String tagName1 = element1.tagName();

                    if (!ObjectUtils.isEmpty(hashMap)){
                        Element element2 = element1.selectFirst("p");
                        if (ObjectUtils.isNotEmpty(element2)){
                            hashMap.put("desc",element2.text());
                            break;
                        }
                    }

                    if (tagName1.equals("h3")){
                        String text = element1.select("h3").text();
                        if (StringUtils.isNotBlank(text)){
                            hashMap = new HashMap<>();
                            String s1 = StringUtils.substringAfterLast(text, "(");
                            String rule = StringUtils.substringBeforeLast(s1, ")");
                            String ruleOverview = StringUtils.substringBeforeLast(text, "(");
                            String attr = element1.select("a").attr("href");
                            List<Map> collected = leaveDataList.stream().filter(b -> b.get("real_name").equals(rule)).collect(Collectors.toList());
                            Object severity="0";
                            if (!CollectionUtils.isEmpty(collected)){
                                 severity = collected.get(0).get("severity");
                            }


                            hashMap.put("problemLevel",severity.toString());
                            hashMap.put("ruleType",type);

                            hashMap.put("ruleName",rule);
                            hashMap.put("ruleOverview",ruleOverview);
                            hashMap.put("scanTool","SpotBugs");
                            hashMap.put("href",attr);
                            arrayList.add(hashMap);
                        }
                    }
                }
            }
        }
    }



    //拉取eslint  的规则
    public static void eslint(){
        String a="https://zh-hans.eslint.org/docs/latest/rules";
        try {
            String filePath = getDirPath("eslint.html");
            File file = new File(filePath);
            Path path = Paths.get(file.getPath());

            // 如果文件不存在则创建文件
          /*  if (Files.exists(path)) {
                Files.delete(path);
            }

            String jsonObject = SourceFareUtil.restTemplateGet(a);
            Files.write(path, jsonObject.getBytes());*/

            analysisEslintXml(path);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }


    //解析eslint的xml
    public static void analysisEslintXml(Path path) throws IOException {
        List<Map> leaveData = getLeaveData("javascript");


        String s = Files.readString(path);
        // 解析 HTML
        Document document = Jsoup.parse(s);

        Elements docsDivs = document.select("div.docs-main__content");
        List<Map> arrayList = new ArrayList<>();
        String h2Text=null;
        for (Element docsDiv : docsDivs) {
            Elements allElements = docsDiv.children(); // 获取所有子元素


            for (int i = 0; i < allElements.size(); i++) {
                Map<String, String> hashMap = new HashMap<>();
                Element currentElement = allElements.get(i);

                String tagName = currentElement.tagName();


                if (tagName.equals("h2")){
                     Element h21 = currentElement.selectFirst("h2");
                     h2Text = h21.attr("id");
                }

                if (StringUtils.isNotBlank(h2Text)){

                    Element ruleDiv = currentElement.selectFirst("div.rule__content");
                  if (ObjectUtils.isNotEmpty(ruleDiv)){
                      if (("possible-problems").equals(h2Text)){
                          hashMap.put("problemLevel","2");
                          hashMap.put("ruleType","function");
                      }
                      if (("suggestions").equals(h2Text)){
                          hashMap.put("problemLevel","3");
                          hashMap.put("ruleType","norm");
                      }
                      if (("layout--formatting").equals(h2Text)){
                          hashMap.put("problemLevel","4");
                          hashMap.put("ruleType","norm");
                      }
                      if (("deprecated").equals(h2Text)){
                          break;
                      }
                      // 获取 a 标签
                      Elements links = ruleDiv.select("a");
                      for (Element link : links) {
                          String text = link.text();
                          List<Map> collected = leaveData.stream().filter(a -> a.get("real_name").equals(text)).collect(Collectors.toList());
                          if (!CollectionUtils.isEmpty(collected)){
                              hashMap.put("problemLevel",collected.get(0).get("severity").toString());
                              String category = collected.get(0).get("category").toString();
                              if (("1").equals(category)){
                                  hashMap.put("ruleType","function");
                              }else {
                                  hashMap.put("ruleType","norm");
                              }
                          }

                          hashMap.put("scanTool","Eslint");
                          hashMap.put("ruleName",link.text());
                          hashMap.put("href",link.attr("href"));
                      }
                      // 获取 p 标签
                      Elements paragraphs = ruleDiv.select("p");
                      for (Element paragraph : paragraphs) {
                          hashMap.put("ruleOverview",paragraph.text());
                      }
                      arrayList.add(hashMap);
                  }
                }

            }
        }
        addDataFile(arrayList,"JavaScript");
    }


    //golangci  的规则
    public static void golangci(){
        String a="https://golangci-lint.run/usage/linters/";
        try {
            String filePath=getDirPath("golangci.html");
            File file = new File(filePath);
            Path path = Paths.get(file.getPath());

            // 如果文件不存在则创建文件
         /*   if (Files.exists(path)) {
                Files.delete(path);
            }

            String jsonObject = SourceFareUtil.restTemplateGet(a);
            Files.write(path, jsonObject.getBytes());*/

            analysisGolangciXml(path);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static void analysisGolangciXml(Path path) throws IOException {
        String s = Files.readString(path);
        // 解析 HTML
        Document document = Jsoup.parse(s);

        Elements docsDivs = document.select("tbody");
        List<Map> arrayList = new ArrayList<>();
        int a=0;
        for (Element docsDiv : docsDivs) {
            a+=1;

            Elements elements = docsDiv.select("tr");
            for (Element element : elements) {
                Map<String, String> hashMap = new HashMap<>();
                Elements aelement = element.select("a");
                String text = aelement.text();
                hashMap.put("problemLevel",String.valueOf(a));
                hashMap.put("ruleType","function");
                hashMap.put("scanTool","Golangci-Lint");
                hashMap.put("ruleName",text);
                String text1 = element.text();
                hashMap.put("ruleOverview",text1);
                arrayList.add(hashMap);
            }
        }

        addDataFile(arrayList,"Go");
    }



    //获取pylint 扫描规则
    public static void pylint(){
        String url="https://pylint.pycqa.org/en/latest/user_guide/messages/messages_overview.html" ;
        try {
            String filePath=getDirPath("pylint.html");
            File file = new File(filePath );
            Path path = Paths.get(file.getPath());
          /*  // 如果文件不存在则创建文件
            if (Files.exists(path)) {
                Files.delete(path);
            }

            String jsonObject = SourceFareUtil.restTemplateGet(url);
            Files.write(path, jsonObject.getBytes());*/

            //解析pylint
            analysisPylintXml(path);
        }catch (Exception e){
            throw new RuntimeException(e);
        }
    }

    //解析pylint结果
    public static void analysisPylintXml(Path path) throws IOException {
        String s = Files.readString(path);
        // 解析 HTML
        Document document = Jsoup.parse(s);

        Elements docsDivs = document.select("section");
        List<Map> arrayList = new ArrayList<>();
        for (Element docsDiv : docsDivs) {
            String  id = docsDiv.attr("id");
            if (id.equals("messages-overview")){
                continue;
            }
            Integer leven;
            String ruleType;
            switch (id){
                case "fatal"->{
                    leven=1;
                    ruleType="security";
                }
                case "error"->{
                    leven=2;
                    ruleType="function";
                }
                case "warning"->{
                    leven=3;
                    ruleType="function";
                }
                default -> {
                    leven=4;
                    ruleType="norm";
                }
            }


            Elements divElements = docsDiv.select("div");
            Element element = divElements.get(0);
            Elements liElements=element.select("li");
            for (Element liElement : liElements) {
                HashMap<String, Object> hashMap = new HashMap<>();
                String text = liElement.text();
                String s1 = StringUtils.substringBefore(text, "/");
                String trim = s1.trim();


                //获取详情
                String data = analysisPylintDetailXml(id, trim);

                hashMap.put("scanTool","pylint");
                hashMap.put("ruleName",trim);
                hashMap.put("problemLevel",leven);
                hashMap.put("ruleType",ruleType);
                hashMap.put("ruleOverview",data);
                hashMap.put("href",id+"/"+trim+".html");
                hashMap.put("desc",data);
                arrayList.add(hashMap);
            }
        }
        addDataFile(arrayList,"pylint");
    }

    public static String analysisPylintDetailXml(String type,String ruleName){
        String url="https://pylint.pycqa.org/en/latest/user_guide/messages/"+type+"/"+ruleName+".html" ;
        String data = SourceFareUtil.restTemplateGet(url);
        Document document = Jsoup.parse(data);
        Elements element = document.select("em");
        String text = element.text();
        return text;
    }


    public static List<Map> getLeaveData(String type) throws IOException {
        String filePath;
        if ("java".equals(type)){
             filePath=getDirPath("spotBug_leave.json");
        }else {
            filePath=getDirPath("eslint_leave.json");
        }
        File file = new File(filePath);
        String content = Files.readString(file.toPath(), StandardCharsets.UTF_8);
        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode jsonNode = objectMapper.readTree(content);
        List<Map> ruleSetList = objectMapper.convertValue(jsonNode, List.class);
        return ruleSetList;
    }


    public static void semgrep(){

        String filePath=getDirPath("semgrep-csharp.json");
        File file = new File(filePath);
        try {
            String content = Files.readString(file.toPath(), StandardCharsets.UTF_8);
            ObjectMapper objectMapper = new ObjectMapper();
            JsonNode jsonNode = objectMapper.readTree(content);
            JsonNode jsonNode1 = jsonNode.get("rules");
            List<Map> ruleSetList = objectMapper.convertValue(jsonNode1, List.class);

            List<Map> arrayList = new ArrayList<>();
            for (Map ruleData:ruleSetList){
                Object ruleName = ruleData.get("id");
                String severity = ruleData.get("severity").toString();
                int leavn=0;
                switch (severity){
                    case "WARNING":
                         leavn=3;
                         break;
                    case "INFO":
                        leavn=4;
                        break;
                    case "ERROR":
                        leavn=2;
                }


                Map metadata =(LinkedHashMap) ruleData.get("metadata");
                String category = metadata.get("category").toString();
                String ruleType;
                switch (category){
                    case "security":
                        ruleType="security";
                    default:
                        ruleType="function";
                }


                Object message = ruleData.get("message");

                HashMap<Object, Object> hashMap = new HashMap<>();
                hashMap.put("scanTool","semgrep");
                hashMap.put("ruleName",ruleName);
                hashMap.put("problemLevel",leavn);
                hashMap.put("ruleType",ruleType);
                hashMap.put("ruleOverview",message);
                hashMap.put("desc",message);
                arrayList.add(hashMap);
            }

            addDataFile(arrayList,"semgrep");
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    public static void cppCheck(){

        String dirPath = getDirPath("cppcheck_rules.xml");
        // 读取XML文件
        try {
            File xmlFile = new File(dirPath);
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            org.w3c.dom.Document document = dBuilder.parse(xmlFile);

            // 获取根元素
            org.w3c.dom.Element documentElement = document.getDocumentElement();

            // 获取error元素的列表
            NodeList errorList = documentElement.getElementsByTagName("error");

            List<Map> arrayList = new ArrayList<>();
            // 遍历BugInstance元素列表
            for (int i = 0; i < errorList.getLength(); i++) {
                Node errorNode = errorList.item(i);
                org.w3c.dom.Element errorElement = (org.w3c.dom.Element) errorNode;
                String ruleName = errorElement.getAttribute("id");
                String msg = errorElement.getAttribute("msg");
                String severity = errorElement.getAttribute("severity");
               Integer leaven=4;
               String ruleType="norm";

               if (("error").equals(severity)){
                   leaven=2;
                   if (ruleName.startsWith("nullPointer")||
                           ruleName.equals("memleak")||
                           ruleName.equals("bufferAccessOutOfBounds")||
                           ruleName.startsWith("thisUseAfterFree")||
                           ruleName.startsWith("invalidFunctionArg")){
                       ruleType="security";
                   }else {
                       ruleType="function";
                   }

               }
               if (("warning").equals(severity)){
                   leaven=3;
                   ruleType="function";
               }
                if (("performance").equals(severity)){
                    leaven=3;
                    ruleType="function";
                }
                if (("portability").equals(severity)){
                    leaven=3;
                    ruleType="norm";
                }
                if (("style").equals(severity)){
                    leaven=4;
                    ruleType="norm";
                }
                if (("information").equals(severity)){
                    leaven=4;
                    ruleType="norm";
                }


                HashMap<Object, Object> hashMap = new HashMap<>();
                hashMap.put("scanTool","cppcheck");
                hashMap.put("ruleName",ruleName);
                hashMap.put("problemLevel",leaven);
                hashMap.put("ruleType",ruleType);
                hashMap.put("ruleOverview",msg);
                hashMap.put("desc",msg);
                arrayList.add(hashMap);
            }
            addCppCheckDataFile(arrayList,"cppcheck");
        }catch (Exception e){
            throw new RuntimeException(e);
        }
    }

    public static void addCppCheckDataFile(List<Map> arrayList,String type) throws IOException {
        List<Map> objects = new ArrayList<>();
        Map<String, Object> hashMap = new HashMap<>();
        hashMap.put("language","C++");
        hashMap.put("ruleSetName","C/C++规则包");
        hashMap.put("describe","C/C++规则包,基于CppCheck实现的安全、功能、代码风格检测功能");

        List<Map> ruleList = new ArrayList<>();
        for (Map data:arrayList){
            Map<String, Object> ruleMap = new HashMap<>();
            ruleMap.put("scanTool",data.get("scanTool"));
            ruleMap.put("ruleName",data.get("ruleName"));
            ruleMap.put("problemLevel",data.get("problemLevel"));
            ruleMap.put("ruleType",data.get("ruleType"));
            ruleMap.put("ruleOverview",data.get("ruleOverview"));
            ruleMap.put("href","");
            ruleMap.put("desc",data.get("desc"));
            ruleList.add(ruleMap);
        }
        hashMap.put("ruleList",ruleList);
        objects.add(hashMap);


        String dirPath = getDirPath("cppCheck.json");
        File file = new File(dirPath);
        Path path1 = Paths.get(file.getPath());

        String jsonString = JSONObject.toJSONString(objects);
        Files.write(path1, jsonString.getBytes());
    }


    public static void pmd(){
        getQuickstartRule();

       /* String [] ruleList=new String[]{"bestpractices.xml","codestyle.xml","design.xml","documentation.xml","errorprone.xml","multithreading.xml","performance.xml","security.xml"};

       // getPmdRuleWrite(ruleList);
        List<Map> arrayList = new ArrayList<>();
        for (String rule:ruleList){
            String ruleType=null;
            if (rule.equals("bestpractices.xml")||rule.equals("codestyle.xml")||rule.equals("design.xml")||rule.equals("documentation.xml")){
                ruleType="norm";
            }
            if (rule.equals("errorprone.xml")||rule.equals("performance.xml")||rule.equals("multithreading.xml")){
                ruleType="function";
            }
            if (rule.equals("security.xml")){
                ruleType="security";
            }
            try {
                String filePath=getDirPath("pmd/"+rule);
                File xmlFile = new File(filePath);
                DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
                DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
                org.w3c.dom.Document document = dBuilder.parse(xmlFile);

                // 获取根元素
                org.w3c.dom.Element documentElement = document.getDocumentElement();

                // 获取rule元素的列表
                NodeList ruleNodeList = documentElement.getElementsByTagName("rule");

                // 遍历ruleNodeList元素列表
                for (int i = 0; i < ruleNodeList.getLength(); i++) {
                    Node ruleNode = ruleNodeList.item(i);
                    org.w3c.dom.Element ruleElement = (org.w3c.dom.Element) ruleNode;
                    String deprecated = ruleElement.getAttribute("deprecated");
                    if (ObjectUtils.isNotEmpty(deprecated)&&("true").equals(deprecated)){
                        continue;
                    }
                    String ruleName = ruleElement.getAttribute("name");
                    String message = ruleElement.getAttribute("message");

                    //等级
                    NodeList priorityNodeList = ruleElement.getElementsByTagName("priority");
                    Node priorityNode = priorityNodeList.item(0);
                    org.w3c.dom.Element priorityElement = (org.w3c.dom.Element) priorityNode;
                    String  leaven = priorityElement.getTextContent();



                    NodeList descNodeList = ruleElement.getElementsByTagName("description");
                    Node descNode = descNodeList.item(0);
                    org.w3c.dom.Element descElement = (org.w3c.dom.Element) descNode;
                    String desc;
                    if (!ObjectUtils.isEmpty(descElement)){
                         desc = descElement.getTextContent();
                    }else {
                        desc= message;
                    }


                    HashMap<Object, Object> hashMap = new HashMap<>();
                    hashMap.put("scanTool","pmd");
                    hashMap.put("ruleName",ruleName);
                    hashMap.put("problemLevel",leaven);
                    hashMap.put("ruleType",ruleType);
                    hashMap.put("ruleOverview",message);
                    hashMap.put("desc",desc);
                    arrayList.add(hashMap);
                }

                addPmdDataFile(arrayList);
                } catch (Exception e) {
                throw new RuntimeException(e);
            }
        }*/




    }


    public static void getQuickstartRule(){
        try {
            //获取快速扫描的规则
            String filePath=getDirPath("pmd/quickstart.xml");
            File xmlFile = new File(filePath);
            DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            org.w3c.dom.Document document = dBuilder.parse(xmlFile);

            // 获取根元素
            org.w3c.dom.Element documentElement = document.getDocumentElement();

            List<String> ruleList  = new ArrayList<>();
            // 获取rule元素的列表
            NodeList ruleNodeList = documentElement.getElementsByTagName("rule");
            // 遍历ruleNodeList元素列表
            for (int i = 0; i < ruleNodeList.getLength(); i++) {
                Node ruleNode = ruleNodeList.item(i);
                org.w3c.dom.Element ruleElement = (org.w3c.dom.Element) ruleNode;
                String deprecated = ruleElement.getAttribute("ref");
                if (ObjectUtils.isNotEmpty(deprecated)){
                    String afterLast = StringUtils.substringAfterLast(deprecated, "/");
                    ruleList.add(afterLast);
                }
            }

            String dirPath = getDirPath("pmd-quickstart.json");
            File file = new File(dirPath);
            Path path1 = Paths.get(file.getPath());

            String jsonString = JSONObject.toJSONString(ruleList);
            Files.write(path1, jsonString.getBytes());
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    public static void addPmdDataFile(List<Map> arrayList ) throws IOException {
        List<Map> objects = new ArrayList<>();
        Map<String, Object> hashMap = new HashMap<>();
        hashMap.put("language","Java");
        hashMap.put("ruleSetName","Java静态扫描规则包");
        hashMap.put("describe","Java静态扫描规则包,基于Pmd实现的安全、功能、代码风格检测功能");

        List<Map> ruleList = new ArrayList<>();
        for (Map data:arrayList){
            Map<String, Object> ruleMap = new HashMap<>();
            ruleMap.put("scanTool",data.get("scanTool"));
            ruleMap.put("ruleName",data.get("ruleName"));
            ruleMap.put("problemLevel",data.get("problemLevel"));
            ruleMap.put("ruleType",data.get("ruleType"));
            ruleMap.put("ruleOverview",data.get("ruleOverview"));
            ruleMap.put("href","");
            ruleMap.put("desc",data.get("desc"));
            ruleList.add(ruleMap);
        }
        hashMap.put("ruleList",ruleList);
        objects.add(hashMap);


        String dirPath = getDirPath("pmd.json");
        File file = new File(dirPath);
        Path path1 = Paths.get(file.getPath());

        String jsonString = JSONObject.toJSONString(objects);
        Files.write(path1, jsonString.getBytes());
    }

    //获取写入规则
    public static void getPmdRuleWrite(String [] ruleList){
        for (String rule:ruleList){
            String url="https://docs.pmd-code.org/pmd-doc-7.16.0/pmd_rules_java_"+rule ;
            try {
                String data = SourceFareUtil.restTemplateGet(url);
                String filePath=getDirPath("pmd/"+rule);
                File file = new File(filePath );
                Path path = Paths.get(file.getPath());
                Files.write(path, data.getBytes());
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }
    }




    public static void addDataFile(List<Map> arrayList,String type) throws IOException {
        List<Map> objects = new ArrayList<>();
        Map<Object, List<Map>> ruleTypes = arrayList.stream()
                .collect(Collectors.groupingBy(a -> a.get("ruleType")));

        String path=null;
        File file=null;
        if (("JavaScript").equals(type)){
            file = new File(getDirPath("eslint.json"));
            path="https://zh-hans.eslint.org";
        }
        if (("Java").equals(type)){
            file = new File(getDirPath("spotbugs.json"));

            path="https://spotbugs.readthedocs.io/en/stable/bugDescriptions.html";
        }
        if (("Go").equals(type)){
            file = new File(getDirPath("golangci.json"));
            path="https://golangci-lint.run/usage/linters";
        }
        if (("pylint").equals(type)){
            file = new File(getDirPath("pylint.json"));
            path="https://pylint.pycqa.org/en/latest/user_guide/messages/";
        }
        if (("semgrep").equals(type)){
            file = new File(getDirPath("semgrep.json"));
            path="https://semgrep.dev/c/p/csharp";
        }
        Set<Object> objects1 = ruleTypes.keySet();
        for (Object key:objects1){
            Map<String, Object> hashMap = new HashMap<>();
            if (("JavaScript").equals(type)){
                hashMap.put("language","JavaScript");
                if (key.equals("function")){
                    hashMap.put("ruleSetName","JavaScript功能规则包");
                    hashMap.put("describe","检查并提示代码中可能存在的功能缺陷");
                }
                if (key.equals("norm")){
                    hashMap.put("ruleSetName","JavaScript 代码规范规则包");
                    hashMap.put("describe","针对JS的项目，继承了JS开发规范的默认配置，使用官方ESLint插件，能够准确的检测项目中的语法以及代码规范相关的问题。");
                }
            }
            if (("Java").equals(type)){
                hashMap.put("language","Java");
                if (key.equals("function")){
                    hashMap.put("ruleSetName","Java功能规则包");
                    hashMap.put("describe","基于spotbugs的规则，发现代码缺陷");
                }
                if (key.equals("norm")){
                    hashMap.put("ruleSetName","Java开发规范包");
                    hashMap.put("describe","基于spotbugs提供一系列规则可维护性，帮助开发人员提高代码质量");
                }
                if (key.equals("security")){
                    hashMap.put("ruleSetName","Java安全检查");
                    hashMap.put("describe","基于spotbugs提供一系列规则和模式来检测代码中的常见问题，帮助开发人员提高代码质量、减少潜在的安全漏洞。");
                }
            }
            if (("Go").equals(type)){
                hashMap.put("language","Go");
                if (key.equals("function")){
                    hashMap.put("ruleSetName","Go开发规则检查");
                    hashMap.put("describe","基于Golangci-Lint提供一系列规则和模式来开发规范检查，帮助开发人员提高代码质量");
                }
            }
            if (("pylint").equals(type)){
                hashMap.put("language","Python");
                if (key.equals("function")){
                    hashMap.put("ruleSetName","Python功能规则包");
                    hashMap.put("describe","潜在问题和可能错误、确定的代码错误");
                }
                if (key.equals("norm")){
                    hashMap.put("ruleSetName","Python代码规范包");
                    hashMap.put("describe","编码风格和格式问题、代码结构优化建议");
                }
                if (key.equals("security")){
                    hashMap.put("ruleSetName","Python安全检查");
                    hashMap.put("describe","严重的安全风险");
                }
            }
            if (("semgrep").equals(type)){
                hashMap.put("language","c#");
                if (key.equals("function")){
                    hashMap.put("ruleSetName","c#功能规则包");
                    hashMap.put("describe","潜在问题和可能错误、确定的代码错误");
                }
                if (key.equals("norm")){
                    hashMap.put("ruleSetName","c#代码规范包");
                    hashMap.put("describe","编码风格和格式问题、代码结构优化建议");
                }
                if (key.equals("security")){
                    hashMap.put("ruleSetName","c#安全检查规则包");
                    hashMap.put("describe","安全风险");
                }
            }

            List<Map> ruleList = new ArrayList<>();
            List<Map> maps = ruleTypes.get(key.toString());
            for (Map data:maps){
                Map<String, Object> ruleMap = new HashMap<>();
                ruleMap.put("scanTool",data.get("scanTool"));
                ruleMap.put("ruleName",data.get("ruleName"));
                ruleMap.put("problemLevel",data.get("problemLevel"));
                ruleMap.put("ruleType",data.get("ruleType"));
                ruleMap.put("ruleOverview",data.get("ruleOverview"));
                ruleMap.put("href",path+data.get("href"));
                ruleMap.put("desc",data.get("desc"));
                ruleList.add(ruleMap);
            }
            hashMap.put("ruleList",ruleList);
            objects.add(hashMap);
        }



        Path path1 = Paths.get(file.getPath());

        String jsonString = JSONObject.toJSONString(objects);
        Files.write(path1, jsonString.getBytes());
    }

    //获取路径
    public static String  getDirPath(String fileName){
        String currentDir = System.getProperty("user.dir");
        String beforeLast = StringUtils.substringBeforeLast(currentDir, "/");
        String path=beforeLast+"/tiklab-sourcefare/tiklab-sourcefare-starter/file/"+fileName;
        return path;
    }
}


