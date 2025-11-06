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
import org.springframework.http.ResponseEntity;
import org.springframework.http.client.SimpleClientHttpRequestFactory;
import org.springframework.util.CollectionUtils;
import org.springframework.web.client.RestTemplate;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.swing.text.html.HTML;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Proxy;
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

        //spotbugs();
        //pmd();
         //eslint();

        //golangci();

        //pylint();

        //semgrep();

        //cppCheck();

        securityCodeScan();

    }


    public static void spotbugs() throws IOException {

       String url="https://spotbugs.readthedocs.io/en/stable/bugDescriptions.html" ;
        String filePath = getDirPath("spotbugs.html");
        File file = new File(filePath);
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
                analysisElement(arrayList,leaveData,allElements,"norm");
            }

            //安全
            if (section1.equals("malicious-code-vulnerability-malicious-code")||     //恶意代码漏洞
                section1.equals("security-security")  ){  //安全

                Integer grade=0;


                Elements allElements = docsDiv.children();
                analysisElement(arrayList,leaveData,allElements,"security");
            }

            //功能
            if (section1.equals("multithreaded-correctness-mt-correctness")|| //多线程正确性
                section1.equals("performance-performance")||
                section1.equals("correctness-correctness")||
                section1.equals("bogus-random-noise-noise")){

                //性能
                Integer grade=0;

                Elements allElements = docsDiv.children();
                analysisElement(arrayList,leaveData,allElements,"function");
            }
        }
        addDataFile(arrayList,"Java");
    }

    //解析子集Element
    public static void analysisElement( List<Map> arrayList,
                                        List<Map> leaveDataList,
                                        Elements allElements,
                                        String type){
            //基础规则包
           List<String> basicRule = Arrays.asList(
                "SQL", "XSS", "password", "null", "Null", "array", "index", "bound",
                "infinite", "loop", "close", "stream", "resource", "leak",
                "equals", "hashCode", "String", "comparison", "==", "hardcoded",
                "NP_", "RANGE_", "IL_", "OS_", "DMI_"
        );
           //高级规则包
        List<String> advancedRule = Arrays.asList(
                "privileged", "reflection", "concurrent", "thread", "synchroniz",
                "atomic", "volatile", "performance", "memory", "clone",
                "serializ", "design pattern", "singleton", "lazy", "REFLC_",
                "DP_", "MC_", "AT_", "MS_", "EI_"
        );
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
                            Object severity="3";
                            if (!CollectionUtils.isEmpty(collected)){
                                 severity = collected.get(0).get("severity");
                            }


                            // 检查是否是基础规则
                            boolean isBasic = basicRule.stream()
                                    .anyMatch(keyword ->
                                            ruleOverview.contains(keyword.toLowerCase()) ||
                                                    rule.contains(keyword)
                                    );

                            // 检查是否是高级规则
                            boolean isAdvanced = advancedRule.stream()
                                    .anyMatch(keyword ->
                                            ruleOverview.contains(keyword.toLowerCase()) ||
                                                    rule.contains(keyword)
                                    );
                            if (isBasic){
                                hashMap.put("property","0");
                            } else if (isAdvanced){
                                hashMap.put("property","1");
                            }else {
                                hashMap.put("property","0");
                            }
                            hashMap.put("ruleName",rule);
                            hashMap.put("problemLevel",severity.toString());
                            hashMap.put("ruleType",type);
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

        //基础规则包
        List<String> advancedRule = Arrays.asList(

                // 复杂度度量
                "complexity", "max-depth", "max-lines", "max-lines-per-function",
                "max-nested-callbacks", "max-params", "max-statements",

                // 现代JavaScript特性
                "no-var", "prefer-const", "prefer-arrow-callback", "prefer-template",
                "prefer-destructuring", "object-shorthand", "prefer-rest-params",
                "prefer-spread", "prefer-numeric-literals", "prefer-promise-reject-errors",

             // 高级代码质量
                "class-methods-use-this", "consistent-return", "consistent-this",
                "max-classes-per-file", "no-bitwise", "no-continue", "no-delete-var",
                "no-div-regex", "no-empty", "no-empty-function", "no-eq-null",
                "no-extend-native", "no-extra-bind", "no-extra-label",
                "no-extra-parens", "no-global-assign", "no-inline-comments",
                "no-iterator", "no-label-var", "no-labels", "no-loop-func",
                "no-magic-numbers", "no-mixed-operators", "no-negated-condition",
                "no-nested-ternary", "no-new-object", "no-plusplus",
                "no-restricted-exports", "no-restricted-globals", "no-restricted-imports",
                "no-restricted-properties", "no-restricted-syntax", "no-shadow",
                "no-ternary", "no-unused-private-class-members", "no-useless-catch",
                "no-useless-computed-key", "no-useless-rename", "no-warning-comments",
                "nonblock-statement-body-position", "one-var", "one-var-declaration-per-line",
                "operator-assignment", "prefer-exponentiation-operator",
                "prefer-named-capture-group", "prefer-object-has-own", "prefer-object-spread",
                "prefer-regex-literals", "quote-props", "radix", "require-await",
                "require-unicode-regexp", "require-yield", "sort-imports", "sort-keys",
                "sort-vars", "spaced-comment", "strict", "symbol-description",
                "unicode-bom", "vars-on-top", "wrap-iife", "wrap-regex", "yield-star-spacing"
        );



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


                          List<String> collect = advancedRule.stream().filter(a -> link.text().contains(a)).collect(Collectors.toList());
                          if (CollectionUtils.isEmpty(collect)){
                              hashMap.put("property","0");
                          }else {
                              hashMap.put("property","1");
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
        //高级规则包
        List<String> advancedRule = Arrays.asList(
                "asasalint", "bidichk", "canonicalheader", "containedctx", "copyloopvar", "cyclop",
                "dupl",  "exptostd", "fatcontext", "forbidigo", "funlen", "ginkgolinter",
                "gochecknoglobals", "gochecksumtype", "gocognit",  "gomoddirectives", "gomodguard", "grouper",
                "iface", "inamedparam", "interfacebloat", "intrange", "ireturn",  "loggercheck", "maintidx", "mirror",
                "mnd", "nakedret", "nestif",  "nolintlint", "nonamedreturns", "nosprintfhostport", "paralleltest", "perfsprint",
                "predeclared", "promlinter", "protogetter", "reassign", "recvcheck", "revive", "sloglint", "testableexamples",
                "testifylint", "testpackage", "thelper", "tparallel", "usestdlibvars", "usetesting", "wastedassign"
        );

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

                List<String> collect = advancedRule.stream().filter(b -> text.contains(b)).collect(Collectors.toList());
                if (CollectionUtils.isEmpty(collect)){
                    hashMap.put("property","0");
                }else {
                    hashMap.put("property","1");
                }

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

        //高级规则包
        List<String> advancedRule = Arrays.asList(
                // 代码质量与性能优化 (68个)
                "consider-using-dict-items", "use-set-for-membership", "use-maxsplit-arg",
                "consider-iterating-dictionary", "consider-using-any-or-all", "consider-using-enumerate",
                "use-implicit-booleaness-not-comparison", "use-implicit-booleaness-not-comparison-to-string",
                "use-implicit-booleaness-not-comparison-to-zero", "use-implicit-booleaness-not-len",
                "use-sequence-for-iteration", "consider-using-join", "consider-using-max-builtin",
                "consider-using-min-builtin", "consider-using-sys-exit", "use-a-generator",
                "use-dict-literal", "use-list-literal", "consider-using-generator",
                "consider-using-dict-comprehension", "consider-using-set-comprehension",
                "consider-using-tuple", "use-yield-from", "nested-min-max",

                // 复杂度控制
                "too-complex", "too-many-arguments", "too-many-statements", "too-many-branches",
                "too-many-locals", "too-many-return-statements", "too-many-nested-blocks",
                "too-many-positional-arguments", "too-many-boolean-expressions", "too-many-public-methods",
                "too-many-instance-attributes", "too-many-ancestors", "too-few-public-methods",

                // 重复代码检测
                "duplicate-code",

                // 现代化Python特性 (45个)
                "consider-using-f-string", "consider-using-assignment-expr",
                "consider-alternative-union-syntax", "consider-using-namedtuple-or-dataclass",
                "redundant-typehint-argument", "using-assignment-expression-in-unsupported-version",
                "using-f-string-in-unsupported-version", "using-final-decorator-in-unsupported-version",
                "using-generic-type-syntax-in-unsupported-version", "using-positional-only-args-in-unsupported-version",
                "using-exception-groups-in-unsupported-version", "consider-using-alias",
                "prefer-typing-namedtuple", "unnecessary-default-type-args",

                // 类型注解优化
                "consider-using-alias", "redundant-typehint-argument", "typevar-double-variance",
                "typevar-name-incorrect-variance", "typevar-name-mismatch",

                // 高级重构建议 (38个)
                "consider-using-in", "consider-using-get", "consider-using-ternary",
                "simplify-boolean-expression", "simplifiable-condition", "simplifiable-if-expression",
                "simplifiable-if-statement", "consider-refactoring-into-while-condition",
                "consider-swap-variables", "consider-using-augmented-assign", "consider-using-from-import",
                "consider-merging-isinstance", "chained-comparison", "comparison-of-constants",
                "comparison-with-itself", "condition-evals-to-constant", "literal-comparison",
                "magic-value-comparison", "no-else-break", "no-else-continue", "no-else-raise",
                "no-else-return", "else-if-used", "consider-ternary-expression",
                "unnecessary-comprehension", "unnecessary-dict-index-lookup", "unnecessary-list-index-lookup",
                "unnecessary-lambda", "unnecessary-direct-lambda-call", "unnecessary-lambda-assignment",
                "unnecessary-dunder-call", "unnecessary-negation", "useless-object-inheritance",
                "useless-return", "stop-iteration-return", "super-with-arguments",

                // 资源管理与上下文
                "consider-using-with", "contextmanager-generator-missing-cleanup",

                // 高级代码结构
                "confusing-consecutive-elif", "inconsistent-return-statements",
                "redefined-variable-type", "redefined-argument-from-local",
                "property-with-parameters", "no-self-use", "no-classmethod-decorator",
                "no-staticmethod-decorator", "cyclic-import", "empty-comment",
                "trailing-comma-tuple", "useless-option-value", "useless-parent-delegation",

                // 高级命名与导入规范
                "ungrouped-imports", "wrong-import-order", "consider-using-from-import",
                "useless-import-alias", "shadowed-import", "import-private-name",

                // 高级异常处理
                "broad-exception-raised", "raise-missing-from", "lost-exception",
                "try-except-raise", "return-in-finally", "break-in-finally", "continue-in-finally",

                // 高级模式检测
                "method-cache-max-size-none", "subprocess-popen-preexec-fn", "subprocess-run-check",
                "shallow-copy-environ", "boolean-datetime", "nan-comparison", "comparison-with-callable",
                "confusing-with-statement", "named-expr-without-context", "using-constant-test",
                "while-used", "wildcard-import", "wrong-exception-operation",

                // 高级文档与注释
                "differing-param-doc", "differing-type-doc", "missing-any-param-doc",
                "missing-param-doc", "missing-raises-doc", "missing-return-doc",
                "missing-return-type-doc", "missing-type-doc", "missing-yield-doc",
                "missing-yield-type-doc", "multiple-constructor-doc", "redundant-returns-doc",
                "redundant-yields-doc", "useless-param-doc", "useless-type-doc",

                // 高级字符串处理
                "duplicate-string-formatting-argument", "format-combined-specification",
                "format-string-without-interpolation", "f-string-without-interpolation",
                "logging-format-interpolation", "logging-fstring-interpolation", "logging-not-lazy",

                // 高级迭代与集合操作
                "modified-iterating-list", "modified-iterating-dict", "modified-iterating-set",
                "unbalanced-dict-unpacking", "unbalanced-tuple-unpacking", "undefined-loop-variable",
                "dict-init-mutate", "duplicate-key", "duplicate-value", "implicit-flag-alias",
                "implicit-str-concat", "redefined-slots-in-subclass", "single-string-used-for-slots",

                // 高级类设计
                "arguments-differ", "arguments-out-of-order", "arguments-renamed",
                "signature-differs", "overridden-final-method", "subclassed-final-class",
                "non-parent-init-called", "super-init-not-called", "super-without-brackets",
                "attribute-defined-outside-init", "method-hidden", "protected-access",
                "unused-private-member", "useless-with-lock", "self-cls-assignment",
                "bad-classmethod-argument", "bad-mcs-classmethod-argument", "bad-mcs-method-argument",
                "bad-staticmethod-argument"
        );

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

                List<String> collect = advancedRule.stream().filter(a -> trim.contains(a)).collect(Collectors.toList());
                if (CollectionUtils.isEmpty(collect)){
                    hashMap.put("property","0");
                }else {
                    hashMap.put("property","1");
                }

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
             filePath=getDirPath("spotBugs_leave.json");
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

        List<String> advancedRule = Arrays.asList(
                // 🏗️ 面向对象设计改进
                "noConstructor", "noExplicitConstructor", "functionConst", "functionStatic",
                "missingOverride", "uselessOverride", "returnByReference", "virtualCallInConstructor",

                // 📝 代码质量和可读性
                "unusedVariable", "unusedFunction", "unusedPrivateFunction", "unusedStructMember",
                "variableScope", "constParameter", "constVariable", "cstyleCast", "postfixOperator",
                "shadowVariable", "shadowFunction", "shadowArgument", "unusedScopedObject",

                // 🧠 逻辑优化
                "duplicateCondition", "redundantCondition", "duplicateBranch", "unreachableCode",
                "clarifyCondition", "oppositeExpression", "duplicateExpression", "unsignedLessThanZero",
                "unsignedPositive", "comparisonOfFuncReturningBoolError", "comparisonOfTwoFuncsReturningBoolError",

                // ⚡ 性能优化
                "passedByValue", "returnByReference", "useStlAlgorithm", "useStandardLibrary",
                "redundantCopy", "stlSize", "unpreciseMathCall", "returnStdMoveLocal",

                // 🔧 STL使用改进
                "stlIfFind", "stlIfStrFind", "stlFindInsert", "stlcstrReturn", "stlcstrParam",
                "uselessCallsCompare", "uselessCallsSwap", "uselessCallsSubstr", "uselessCallsEmpty",

                // 🎯 其他代码改进
                "incompleteArrayFill", "commaSeparatedReturn", "redundantPointerOp", "selfAssignment",
                "suspiciousSemicolon", "clarifyCalculation", "clarifyStatement"
        );

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
                List<String> collect = advancedRule.stream().filter(a -> ruleName.equals(a)).collect(Collectors.toList());
                if (CollectionUtils.isEmpty(collect)){
                    hashMap.put("property","0");
                }else {
                    hashMap.put("property","1");
                }


                hashMap.put("scanTool","cppcheck");
                hashMap.put("ruleName",ruleName);
                hashMap.put("problemLevel",leaven);
                hashMap.put("ruleType",ruleType);
                hashMap.put("ruleOverview",msg);
                hashMap.put("desc",msg);
                arrayList.add(hashMap);
            }
            //addCppCheckDataFile(arrayList,"cppcheck");
            addDataFile(arrayList,"cppcheck");
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
        //getQuickstartRule();

        String [] ruleList=new String[]{"bestpractices.xml","codestyle.xml","design.xml","documentation.xml","errorprone.xml","multithreading.xml","performance.xml","security.xml"};

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

                    HashMap<String, Object> hashMap = new HashMap<>();
                    List<String> quickStart = getQuickStart();
                    List<String> strings = quickStart.stream().filter(a -> ruleName.equals(a)).collect(Collectors.toList());
                    if (CollectionUtils.isEmpty(strings)){
                        hashMap.put("property","1");
                    }else {
                        hashMap.put("property","0");
                    }
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
        }
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
        Map<Object, List<Map>> ruleTypes = arrayList.stream()
                .collect(Collectors.groupingBy(a -> a.get("property")));

        Set<Object> keyedSet = ruleTypes.keySet();
        for (Object key:keyedSet ){
            Map<String, Object> hashMap = new HashMap<>();
            if (key.equals("0")){
                hashMap.put("language","Java");
                hashMap.put("property",0);
                hashMap.put("ruleSetName","Java基础规则包(静态扫描)");
                hashMap.put("describe","Java静态扫描规则包,quickstart扫描");
            }else {
                hashMap.put("language","Java");
                hashMap.put("property",1);
                hashMap.put("ruleSetName","Java高级规则包(静态扫描)");
                hashMap.put("describe","Java静态扫描规则包,包含代码复杂度与设计、并发与线程安全、高级性能优化等");
            }


            List<Map> ruleList = new ArrayList<>();
            List<Map> mapList = ruleTypes.get(key);
            for (Map data:mapList){
                Map<String, Object> ruleMap = new HashMap<>();
                ruleMap.put("property",key);
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
        }

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
        /*Map<Object, List<Map>> ruleTypes = arrayList.stream()
                .collect(Collectors.groupingBy(a -> a.get("ruleType")));*/
        Map<Object, List<Map>> ruleTypes = arrayList.stream()
                .collect(Collectors.groupingBy(a -> a.get("property")));

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
        if (("cppcheck").equals(type)){
            file = new File(getDirPath("cppCheck.json"));
        }
        if (("semgrep").equals(type)){
            file = new File(getDirPath("semgrep.json"));
            path="https://semgrep.dev/c/p/csharp";
        }


        Set<Object> objects1 = ruleTypes.keySet();
        for (Object key:objects1) {
            Map<String, Object> hashMap = new HashMap<>();
            if (("Java").equals(type)){
                hashMap.put("language",type);
                if (key.equals("0")){
                    hashMap.put("property","0");
                    hashMap.put("ruleSetName","Java基础规则包(编译扫描)");
                    hashMap.put("describe","编译代码扫描的基础规则包，包含：常见的安全漏洞（SQL注入、XSS、硬编码密码等）、基本的空指针异常、数组越界、无限循环等、常见的资源未关闭问题、基本的代码规范问题、正则表达式等");
                }
                if (key.equals("1")){
                    hashMap.put("property","1");
                    hashMap.put("ruleSetName","Java高级规则包(编译扫描)");
                    hashMap.put("describe","编译代码扫描的高级规则包，包含：复杂的权限检查、反射安全问题、并发问题、线程安全问题、性能优化相关规则、复杂的代码模式检测、深层的设计模式问题");
                }
            }
            if (("JavaScript").equals(type)){
                hashMap.put("language","JavaScript");
                if (key.equals("0")){
                    hashMap.put("property","0");
                    hashMap.put("ruleSetName","JavaScript基础规则包");
                    hashMap.put("describe","JavaScript基础规则包，包含：代码错误与潜在问题、变量与作用域、类型与比较、函数与类、基本代码质量、异步编程");
                }
                if (key.equals("1")){
                    hashMap.put("property","1");
                    hashMap.put("ruleSetName","JavaScript高级规则包");
                    hashMap.put("describe","JavaScript基础规则包，包含：代码复杂度与架构、现代JavaScript特性、高级代码质量等");
                }

            }
            if (("Go").equals(type)){
                hashMap.put("language",type);
                if (key.equals("0")){
                    hashMap.put("property","0");
                    hashMap.put("ruleSetName","Go基础规则包");
                    hashMap.put("describe","Go基础规则包，包含：错误处理、安全漏洞、资源泄露、代码风格和命名规范、性能问题等直接影响代码质量和稳定性的核心规则");
                }
                if (key.equals("1")){
                    hashMap.put("property","1");
                    hashMap.put("ruleSetName","Go高级规则包");
                    hashMap.put("describe","Go高级规则包，包含：复杂度检查、高级测试规范、特定场景优化等增强规则");
                }
            }
            if (("pylint").equals(type)){
                hashMap.put("language","Python");
                if (key.equals("0")){
                    hashMap.put("property","0");
                    hashMap.put("ruleSetName","Python基础规则包");
                    hashMap.put("describe","Go基础规则包，包含：错误处理、语法和运行时错误、基本代码格式");
                }
                if (key.equals("1")){
                    hashMap.put("property","1");
                    hashMap.put("ruleSetName","Python高级规则包");
                    hashMap.put("describe","Go高级规则包，包含：代码质量与性能优化、代码规范与团队协作、 代码复杂度与维护性、现代化编码实践、类型安全与重构");
                }
            }
            if (("cppcheck").equals(type)){
                hashMap.put("language","C++");
                if (key.equals("0")){
                    hashMap.put("property","0");
                    hashMap.put("ruleSetName","C、C++基础规则包");
                    hashMap.put("describe","C、C++基础规则包，包含：导致崩溃、安全漏洞的严重问题、内存管理相关的核心问题、未定义行为和运行时错误、资源泄漏问题");
                }
                if (key.equals("1")){
                    hashMap.put("property","1");
                    hashMap.put("ruleSetName","C、C++高级规则包");
                    hashMap.put("describe","C、C++高级规则包，包含：代码设计和架构改进、代码可读性和维护性、性能优化建议、最佳实践遵循");
                }
            }
            if (("semgrep").equals(type)){
                hashMap.put("language","C#");
                if (key.equals("0")){
                    hashMap.put("property","0");
                    hashMap.put("ruleSetName","C#基础规则包");
                    hashMap.put("describe","C#基础规则包，包含：导致崩溃、安全漏洞的严重问题、内存管理相关的核心问题、未定义行为和运行时错误、资源泄漏问题");
                }
                if (key.equals("1")){
                    hashMap.put("property","1");
                    hashMap.put("ruleSetName","C#高级规则包");
                    hashMap.put("describe","C、C++高级规则包，包含：代码设计和架构改进、代码可读性和维护性、性能优化建议、最佳实践遵循");
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
                ruleMap.put("property",data.get("property"));
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


    public static List<String> getQuickStart() throws IOException {
        String dirPath = getDirPath("pmd-quickstart.json");
        String content = Files.readString(Path.of(dirPath), StandardCharsets.UTF_8);
        ObjectMapper objectMapper = new ObjectMapper();
        JsonNode jsonNode = objectMapper.readTree(content);
        List<String> ruleSetList = objectMapper.convertValue(jsonNode, List.class);
        return ruleSetList;
    }

    //获取路径
    public static String  getDirPath(String fileName){
        String currentDir = System.getProperty("user.dir");
        String beforeLast = StringUtils.substringBeforeLast(currentDir, "/");
        String path=beforeLast+"/tiklab-sourcefare/tiklab-sourcefare-starter/file/"+fileName;
        return path;
    }

    public static void  securityCodeScan(){
        List<String> stringList = Arrays.asList("0001", "0002", "0003", "0004", "0005", "0006", "0007", "0008", "0009", "0010",
                "0011", "0012", "0013", "0015", "0016", "0017", "0018", "0019",
                "0021", "0022", "0023", "0024", "0026", "0027", "0028", "0029", "0030",
                "0031", "0032", "0033", "0034");

        for (String rule:stringList){
            String path="https://github.com/security-code-scan/security-code-scan/blob/vs2019/website/rules/"+rule+".md";
            RestTemplate restTemplate = new RestTemplate();
            restTemplate.setRequestFactory(getNetworkProxy());
            ResponseEntity<String> forEntity = restTemplate.getForEntity(path, String.class);
            String string = forEntity.toString();

            try {
                // 解析 HTML
                Document document = Jsoup.parse(string);

                // 提取目标文本
                Element article = document.selectFirst("article.markdown-body");
                if (article != null) {
                    // 获取所有段落文本
                    String fullText = article.text();

                    // 或者提取特定部分
                    Element firstParagraph = article.selectFirst("p");
                    if (firstParagraph != null) {
                        String text = firstParagraph.text();
                        System.out.println("");
                    }
                }

            }catch (Exception e){
                e.printStackTrace();
            }


        }
    }

    /**
     * 添加网络代理地址
     */
    public static SimpleClientHttpRequestFactory getNetworkProxy( ) {



        SimpleClientHttpRequestFactory factory = new SimpleClientHttpRequestFactory();
        //单位为ms
        factory.setReadTimeout(10 * 1000);
        //单位为ms
        factory.setConnectTimeout(30 * 1000);
        // 代理的url网址或ip, port端口
        InetSocketAddress address = new InetSocketAddress("127.0.0.1", 7897);
        Proxy proxy = new Proxy(Proxy.Type.HTTP, address);
        factory.setProxy(proxy);
        return factory;
    }
}


