package io.tiklab.sourcefare.common;

import com.alibaba.fastjson.JSONObject;
import io.tiklab.core.exception.ApplicationException;
import io.tiklab.sourcefare.scan.model.DeployEnv;
import io.tiklab.sourcefare.scan.model.ScanRecordLog;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.sourcefare.scanner.common.SourceFareFinal;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import org.apache.commons.lang3.StringUtils;
import org.springframework.http.*;
import org.springframework.http.client.ClientHttpRequestFactory;
import org.springframework.http.client.SimpleClientHttpRequestFactory;
import org.springframework.http.converter.StringHttpMessageConverter;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.text.SimpleDateFormat;
import java.util.*;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.TimeoutException;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;

import static io.tiklab.sourcefare.common.SourceFareServerFinal.*;
import static io.tiklab.sourcefare.scanner.common.SourceFareFinal.LOG_COMPILE;

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

        if (("project").equals(type)){
            if (day!=0){
                return day+" 天"+hour+" 小时";
            }
            if (hour != 0){
                return hour+" 小时"+minute+" 分钟";
            }
            if (minute != 0){
                return minute+" 分钟";
            }
            return second+" 秒";
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
     * 执行cmd命令
     * @param path 执行文件夹
     * @param order 执行命令
     * @return 执行信息
     * @throws IOException 调取命令行失败
     */
    public static Process executeCmd(String order,String path) throws Exception {
        Runtime runtime=Runtime.getRuntime();
        Process process;
        if (ProjectUtil.findSystemType()==1){
            if (StringUtils.isBlank(path)){
                process = runtime.exec(" cmd.exe /c " + " " + order);
            }else {
                process = runtime.exec(" cmd.exe /c " + " " + order,null,new File(path));
            }
        }else {
            if (StringUtils.isBlank(path)){
                String[]  cmd = new String[] { "/bin/sh", "-c", " source /etc/profile;"+ order };
                process = runtime.exec(cmd);
            }else {
                String[]  cmd = new String[] { "/bin/sh", "-c", "cd " + path + ";"+" source /etc/profile;"+ order };
                process = runtime.exec(cmd,null,new File(path));
            }
        }
        //执行命令等待时间
        if (process.waitFor(SourceFareFinal.CMD_TIMEOUT, TimeUnit.MILLISECONDS)) {
            return  process;
        } else {
            throw new TimeoutException();
        }
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



    /**
     * 解压zip文件夹
     * @param outputFolderPath 解压路径
     * @param inputFilePath 压缩包文件路径
     */

    public static void decompressionZip(String inputFilePath,String outputFolderPath) throws IOException {

        File targetFolder = new File(outputFolderPath);

        // 创建目标文件夹（如果不存在）
        if (!targetFolder.exists()) {
            targetFolder.mkdirs();
        }

        byte[] buffer = new byte[1024];
        // 获取ZIP文件名（不含扩展名）
        String zipName = StringUtils.substringAfterLast(inputFilePath, "/");
        String fileName = StringUtils.substringBeforeLast(zipName, ".zip");

        try (ZipInputStream zipInputStream = new ZipInputStream(new FileInputStream(inputFilePath))) {

            ZipEntry zipEntry = zipInputStream.getNextEntry();

            while (zipEntry != null) {
                String entryName = zipEntry.getName();

                // 跳过与ZIP文件同名的顶级目录
                if (entryName.startsWith(fileName + "/") || entryName.startsWith(fileName + "\\")) {
                    entryName = entryName.substring(fileName.length() + 1);
                }

                // 构建目标文件路径
                File extractedFile = new File(targetFolder, entryName);

                // 如果entry是一个文件，则解压缩
                if (!zipEntry.isDirectory()) {
                    // 创建目标文件的父目录（如果不存在）
                    if (!extractedFile.getParentFile().exists()) {
                        extractedFile.getParentFile().mkdirs();
                    }

                    try (FileOutputStream outputStream = new FileOutputStream(extractedFile)) {
                        int length;
                        while ((length = zipInputStream.read(buffer)) > 0) {
                            outputStream.write(buffer, 0, length);
                        }
                    } catch (java.util.zip.ZipException e) {
                        if (e.getMessage().contains("EXT descriptor")) {
                            System.err.println("跳过有EXT描述符问题的条目: " + entryName);
                            // 可以选择记录日志或采取其他措施
                            zipInputStream.closeEntry();
                            zipEntry = zipInputStream.getNextEntry();
                            continue; // 跳过这个条目
                        } else {
                            throw e; // 重新抛出其他异常
                        }
                    }
                }

                // 关闭当前entry，继续获取下一个entry
                zipInputStream.closeEntry();
                zipEntry = zipInputStream.getNextEntry();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }



    /**
     * 效验地址是否存在配置文件
     * @param deployEnv deployEnv
    // * @return 匹配状态  1.不是个目录或不存在这个文件夹  2. 空目录找不到可执行文件 0. 匹配成功
     */
    public static String validFile(DeployEnv deployEnv) throws ApplicationException {
        String fileAddress = deployEnv.getEnvAddress();
        String type = deployEnv.getEnvType();
        Integer installWay = deployEnv.getInstallWay();
        String address;
        if (installWay!=0){
            if (StringUtils.isEmpty(fileAddress)){
                throw new ApplicationException("地址配置异常,"+fileAddress+"没有文件!");
            }

            File file = new File(fileAddress);

            //不存在这个目录
            if (!file.exists()){
                throw new ApplicationException("地址配置异常，"+fileAddress+"路径在当前主机不存在。");
            }
            //不是个目录
            if (!file.isDirectory()){
                throw new ApplicationException("地址配置异常："+fileAddress+"不是个目录。");
            }
            //不存在可执行文件
            File[] files = file.listFiles();
            if (files == null || files.length == 0){
                throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到可执行文件。");
            }
             address = findScmAddress(file,type);
        }else {
            String envVersion = ProjectUtil.getEnvPath(type);
            if (StringUtils.isNotBlank(envVersion)&&envVersion.contains("not found")){
                address=null;
            }else {
                address=envVersion;
            }
        }


        if (StringUtils.isEmpty(address)){
            switch (type) {
                case TASK_TOOL_TYPE_JDK -> {
                    throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到JDK可执行文件。");
                }
                case TASK_TOOL_TYPE_GIT -> {
                    throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到Git的可执行文件。");
                }
                case TASK_TOOL_TYPE_SVN -> {
                    throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到Svn的可执行文件。");
                }
                case TASK_TOOL_TYPE_MAVEN -> {
                    throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到Maven的可执行文件。");
                }
                case TASK_TOOL_TYPE_NODE -> {
                    throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到Node的可执行文件。");
                }
                case TASK_TOOL_TYPE_NPM -> {
                    throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到npm的可执行文件。");
                }
                case TASK_TOOL_TYPE_GO -> {
                    throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到go的可执行文件。");
                }
                case TASK_TOOL_TYPE_PYTHON -> {
                    throw new ApplicationException("地址配置异常，在"+fileAddress+"找不到python的可执行文件。");
                }
            }
        }
        return address;
    }


    /**
     * 获取不同环境的可执行程序地址
     * @param file 目录
     * @param type 类型
     * @return 可执行程序地址
     */
    private static String findScmAddress(File file, String type){
        String address = null;
        for (File listFile : Objects.requireNonNull(file.listFiles())) {

            if (listFile.isDirectory() && !listFile.getName().startsWith(".")){
                // 递归找到值后立即返回，避免继续遍历
                if (!StringUtils.isEmpty(address)) {
                    return address;
                }
                address = findScmAddress(listFile, type);
            }

            String name = listFile.getName();
            switch (type) {
                case TASK_TOOL_TYPE_JDK -> {
                    if (name.equals("java") || name.equals("java.exe")) {
                        address = listFile.getParent();
                    }
                }
                case TASK_TOOL_TYPE_MAVEN -> {
                    if (name.equals("mvn")|| name.equals("maven.exe")) {
                        address = listFile.getParent();
                    }
                }
                case TASK_TOOL_TYPE_NODE -> {
                    if (name.equals("node")|| name.equals("node.exe")) {
                        address = listFile.getParent();
                    }
                }
                case TASK_TOOL_TYPE_NPM -> {
                    if (name.equals("npm")|| name.equals("npm.exe")) {
                        address = listFile.getParent();
                    }
                }
                case TASK_TOOL_TYPE_GO -> {
                    if (name.equals("go")|| name.equals("go.exe")) {
                        address = listFile.getParent();
                    }
                }
                case TASK_TOOL_TYPE_PYTHON -> {
                    if (name.equals("pip3")|| name.equals("pip3.exe")||name.equals("pip")|| name.equals("pip.exe")) {
                        address = listFile.getParent();
                    }
                }
            }
        }
        return address;
    }


    /**
     *  getRestTemplate 通过RestTemplate 查询
     * @param path 查询路径
     */
    public static ResponseEntity<List>  getRestTemplate(String path){
        RestTemplate restTemplate = new RestTemplate();
        restTemplate.getMessageConverters().set(1,new StringHttpMessageConverter(StandardCharsets.UTF_8));
        ResponseEntity<List> response = restTemplate.getForEntity(path, List.class);
        return response;
    }


    public static ResponseEntity<JSONObject>  restTemplateGitPuk(RepositoryServer server,String findPath){
        Map<String, String> hashMap = new HashMap<>();
        hashMap.put("accessToken", SourceFareServerFinal.ACCESS_TOKEN);

        // 创建请求头对象
        HttpHeaders headers = SourceFareUtil.initHeaders(MediaType.APPLICATION_JSON, hashMap);

        // 请求体参数
        MultiValueMap<String, Object> valueMap = new LinkedMultiValueMap<>();
        valueMap.add("account",server.getAccount());
        valueMap.add("password",server.getPassWord());
        valueMap.add("repName",server.getRepName());


        // 创建 HttpEntity 包含请求体和请求头
        HttpEntity<MultiValueMap<String, Object>> requestEntity = new HttpEntity<>(valueMap, headers);

        //设置连接超时时间
        ClientHttpRequestFactory factory = new SimpleClientHttpRequestFactory();
        ((SimpleClientHttpRequestFactory) factory).setConnectTimeout(10000);
        RestTemplate restTemplate = new RestTemplate(factory);

        ResponseEntity<JSONObject> response = restTemplate.exchange(findPath, HttpMethod.POST, requestEntity, JSONObject.class);
       return response;
    }

    public static void addLogOrder(ScanRecordLog recordLog, String type){
        switch (type){
            case LOG_COMPILE -> {
                recordLog.setSort(1);
                recordLog.setTitle("项目构建");
            }
            case SourceFareFinal.SCAN -> {
                recordLog.setSort(2);
                recordLog.setTitle("问题扫描");
            }
            case SourceFareFinal.DUPLICATED -> {
                recordLog.setSort(3);
                recordLog.setTitle("重复度扫描");
            }
            case SourceFareFinal.COMPLEXITY -> {
                recordLog.setSort(4);
                recordLog.setTitle("复杂度扫描");
            }
            case SourceFareFinal.COVER -> {
                recordLog.setSort(5);
                recordLog.setTitle("覆盖率扫描");
            }
        }
    }

    public static String getCommandPath(String cmd) {
        String[] whichCmd = System.getProperty("os.name").toLowerCase().contains("win")
                ? new String[]{"where", cmd}
                : new String[]{"which", cmd};
        try {
            Process p = new ProcessBuilder(whichCmd).start();
            try (BufferedReader r = new BufferedReader(new InputStreamReader(p.getInputStream()))) {
                String line = r.readLine();
                return (line != null && !line.isEmpty()) ? line.trim() : null;
            }
        } catch (IOException ignored) {}
        return null;
    }

}
