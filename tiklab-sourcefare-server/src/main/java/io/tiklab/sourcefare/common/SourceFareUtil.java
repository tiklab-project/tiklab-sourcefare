package io.tiklab.sourcefare.common;

import com.alibaba.fastjson.JSONObject;
import org.springframework.http.*;
import org.springframework.web.client.RestTemplate;

import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.*;

public class SourceFareUtil {

    //获取随机数
    public static String getRandom(int length) {
        char[] ss = new char[length];
        int[] flag = {0,0,0}; //A-Z, a-z, 0-9
        int i=0;
        while(flag[0]==0 || flag[1]==0 || flag[2]==0 || i<length) {
            i = i%length;
            int f = (int) (Math.random()*3%3);
            if(f==0)
                ss[i] = (char) ('A'+Math.random()*26);
            else if(f==1)
                ss[i] = (char) ('a'+Math.random()*26);
            else
                ss[i] = (char) ('0'+Math.random()*10);
            flag[f]=1;
            i++;
        }
        return new String(ss);
    }

    /**
     * 获取与当前时间的时间差
     * @param date 时间
     * @param  type 类型 scan、commit
     * @return 时间差
     */
    public static String time(Date date, String type){

        long time = new Date().getTime();
        long dateTime = date.getTime();
        long l=time-dateTime;


        long day=l/(24*60*60*1000);
        long hour=(l/(60*60*1000)-day*24);
        long minute=((l/(60*1000))-day*24*60-hour*60);
        long second=(l/1000-day*24*60*60-hour*60*60-minute*60);
        if (("scan").equals(type)||("clean").equals(type)){
            if (minute != 0){
                return minute+"分钟"+second+"秒";
            }
            return second+"秒";
        }
        if (day != 0){
            return day+"天";
        }
        if (hour != 0){
            return hour+"小时";
        }
        if (minute != 0){
            return minute+"分钟";
        }
        return second+"秒";
    }

    /**
     * 返回系统时间
     * @param type 时间类型 1.(yyyy-MM-dd HH:mm:ss) 2.(yyyy-MM-dd) 3.(HH:mm:ss) 4.([format]) 5.(HH:mm)
     * @return 时间
     */
    public static String date(int type,Date date){
        switch (type) {
            case 2 -> {
                return new SimpleDateFormat("yyyy-MM-dd").format(date);
            }
            case 3 -> {
                return new SimpleDateFormat("HH:mm:ss").format(date);
            }
            case 4 -> {
                String format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date);
                return "[" + format + "]" + "  ";
            }
            case 5 -> {
                return new SimpleDateFormat("HH:mm").format(date);
            }
            default -> {
                return new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(date);
            }
        }
    }

    /**
     *
     * @param mediaType 请求类型 MediaType.MULTIPART_FORM_DATA --formdata  MediaType.APPLICATION_JSON --json
     * @param headerMap 其他请求头
     * @return 请求头
     */
    public static HttpHeaders initHeaders(MediaType mediaType, Map<String,String> headerMap){
        HttpHeaders headers = new HttpHeaders();
        headers.setAccept(Collections.singletonList(mediaType));
        if (Objects.isNull(headerMap)){
            return headers;
        }
        for (Map.Entry<String, String> header : headerMap.entrySet()) {
            String key = header.getKey();
            String value = header.getValue();
            headers.set(key,value);
        }
        return headers;
    }

    /**
     * 不同系统返回的地址
     * @param address
     * @return 位置
     */
    public static String SystemTypeAddress(String address) {
        int systemType = findSystemType();
        if (systemType == 1) {
            return address.replace("/", "\\");
        }
        return address;
    }


    /**
     * 系统类型
     * @return 1.windows 2.其他
     */
    public static int findSystemType(){
        String property = System.getProperty("os.name");
        String[] s1 = property.split(" ");
        switch (s1[0]){
            case "Windows":
                return 1;
            case "Mac":
                return 2;
            default:
                return 3;
        }
    }

    /**
     *执行maven编译
     * @param mavenPath maven地址
     * @param  repositoryPath 编译项目地址
     * @return
     */
    public static Process mavenBuild(String mavenPath,String repositoryPath) throws IOException {
        String path = mavenPath+"/mvn";

        String s = SystemTypeAddress(path);
        ProcessBuilder processBuilder = new ProcessBuilder(
                s,
                "clean",
                "compile"
        );
        processBuilder.directory(new File(repositoryPath));
        return processBuilder.start();
    }

    /**
     *  获取随机数
     *  @param num   取摸数
     */
    public static int getRandomNum(int num) {
        // 获取当前时间的纳秒数
        long nanoTime = System.nanoTime();

        return (int) (nanoTime % num);
    }

    /**
     *  修改文件夹名称
     * @param  oldPath oldPath
     * @param  newPath newPath
     * @param  execNum 执行次数
     */
    public static boolean updateDirName(String oldPath,String newPath,int execNum){

        // 原文件夹路径
        File oldDir = new File(oldPath);
        // 新文件夹路径
        File newDir = new File( newPath);
        boolean b = oldDir.renameTo(newDir);
        if (!b){
            if (execNum>5){
                return  false;
            }
            updateDirName(oldPath,newPath,execNum+1);
        }
        return true;
    }

    /**
     * 递归获取文件夹下面的所有文件
     * @param path
     * @return 位置
     */
    public static List<String> getFolderFile(File path, List<String> list){
        File[] fa = path.listFiles();
        if (fa != null) {
            for (File file : fa) {
                if (file.isDirectory()){
                    getFolderFile(file,list);
                }
                list.add(file.getPath());
            }
        }
        return list;
    }

    public static String restTemplateGet(String url){
        HttpHeaders headers = new HttpHeaders();

        // 请求
        HttpEntity<String> request = new HttpEntity<>(headers);

        RestTemplate restTemplate = new RestTemplate();
        ResponseEntity<String> result = restTemplate.exchange(url, HttpMethod.GET, request, String.class);
        String responseBody = result.getBody();
        return responseBody;
    }
}
