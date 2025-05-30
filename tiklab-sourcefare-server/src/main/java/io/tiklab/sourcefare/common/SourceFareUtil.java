package io.tiklab.sourcefare.common;

import org.springframework.http.HttpHeaders;
import org.springframework.http.MediaType;

import java.io.File;
import java.io.IOException;
import java.util.Collections;
import java.util.Date;
import java.util.Map;
import java.util.Objects;

public class SourceFareUtil {
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
}
