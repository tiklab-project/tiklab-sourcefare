package io.tiklab.sourcefare.common;

import com.alibaba.fastjson.JSONObject;
import org.apache.commons.lang3.ObjectUtils;
import org.apache.commons.lang3.StringUtils;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;

public class PullRule {
    public static void main(String[] args) throws IOException {

       // eslint();

        spotbugs();
    }


    public static void spotbugs() throws IOException {

       String url="https://spotbugs.readthedocs.io/en/stable/bugDescriptions.html" ;
        String filePath= "/Users/limingliang/work/work-project/tiklab-sourcefare/tiklab-sourcefare-starter";
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
        String s = Files.readString(path);
        // 解析 HTML
        Document document = Jsoup.parse(s);

        Elements docsDivs = document.select("section");
        List<Map> arrayList = new ArrayList<>();
        String h2Text=null;
        for (Element docsDiv : docsDivs) {
            String  section1 = docsDiv.attr("id");


            //不良写法
            if (section1.equals("bad-practice-bad-practice")){
                Elements allElements = docsDiv.children();
                analysisElement(arrayList,allElements,"norm");
            }

            if (section1.equals("correctness-correctness")){
                Elements allElements = docsDiv.children();
                analysisElement(arrayList,allElements,"function");
            }
            if (section1.equals("correctness-correctness")){
                Elements allElements = docsDiv.children();
                analysisElement(arrayList,allElements,"secure");
            }
            if (section1.equals("dodgy-code-style")){
                Elements allElements = docsDiv.children();
                analysisElement(arrayList,allElements,"norm1");
            }


        }
        addDataFile(arrayList,"Java");
    }

    //解析子集Element
    public static void analysisElement(List<Map> arrayList,Elements allElements,String type){
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

                            if (("function").equals(type)||("secure").equals(type)){
                                hashMap.put("problemLevel","1");
                                hashMap.put("ruleType",type);
                            }
                            if (("norm").equals(type)){
                                hashMap.put("problemLevel","2");
                                hashMap.put("ruleType",type);
                            }
                            if (("norm1").equals(type)){
                                hashMap.put("problemLevel","3");
                                hashMap.put("ruleType","norm");
                            }


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
            String filePath= "/Users/limingliang/work/work-project/tiklab-sourcefare/tiklab-sourcefare-starter";
            File file = new File(filePath + "/file/eslint.html");
            Path path = Paths.get(file.getPath());

            // 如果文件不存在则创建文件
            if (Files.exists(path)) {
                Files.delete(path);
            }

            String jsonObject = SourceFareUtil.restTemplateGet(a);
            Files.write(path, jsonObject.getBytes());

            analysisEslintXml(path);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }


    //解析eslint的xml
    public static void analysisEslintXml(Path path) throws IOException {

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
                          hashMap.put("problemLevel","1");
                          hashMap.put("ruleType","function");
                      }
                      if (("suggestions").equals(h2Text)){
                          hashMap.put("problemLevel","2");
                          hashMap.put("ruleType","norm");
                      }
                      if (("layout--formatting").equals(h2Text)){
                          hashMap.put("problemLevel","2");
                          hashMap.put("ruleType","norm");
                      }
                      if (("deprecated").equals(h2Text)){
                          break;
                      }
                      // 获取 a 标签
                      Elements links = ruleDiv.select("a");
                      for (Element link : links) {
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


    public static void addDataFile(List<Map> arrayList,String type) throws IOException {
        List<Map> objects = new ArrayList<>();
        Map<Object, List<Map>> ruleTypes = arrayList.stream()
                .collect(Collectors.groupingBy(a -> a.get("ruleType")));

        String filePath= "/Users/limingliang/work/work-project/tiklab-sourcefare/tiklab-sourcefare-starter";

        String path=null;
        File file=null;
        if (("JavaScript").equals(type)){
            file = new File(filePath + "/file/eslint.json");
             path="https://zh-hans.eslint.org";
        }
        if (("Java").equals(type)){
            file = new File(filePath + "/file/spotbugs.json");
            path="https://spotbugs.readthedocs.io/en/stable/bugDescriptions.html";
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
                    hashMap.put("describe","检查并提示代码中可能存在的功能缺陷");
                }
                if (key.equals("norm")){
                    hashMap.put("ruleSetName","Java开发规范检查");
                    hashMap.put("describe","基于spotbugs提供一系列规则和模式来开发规范检查，帮助开发人员提高代码质量");
                }
                if (key.equals("secure")){
                    hashMap.put("ruleSetName","Java安全检查");
                    hashMap.put("describe","基于spotbugs提供一系列规则和模式来检测代码中的常见问题，帮助开发人员提高代码质量、减少潜在的安全漏洞。");
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
}


