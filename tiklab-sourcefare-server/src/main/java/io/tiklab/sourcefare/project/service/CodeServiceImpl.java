package io.tiklab.sourcefare.project.service;

import io.tiklab.core.exception.SystemException;
import io.tiklab.sourcefare.project.model.Code;
import io.tiklab.sourcefare.project.model.CodeQuery;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.sourcefare.scan.service.RecordComplexityService;
import io.tiklab.sourcefare.scan.service.RecordDuplicatedService;
import io.tiklab.sourcefare.scan.service.RecordInstanceService;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.ObjectUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.sql.Timestamp;
import java.util.*;
import java.util.stream.Collectors;

@Service
public class CodeServiceImpl implements CodeService {

    @Autowired
    PathSetService pathSetService;

    @Autowired
    RecordInstanceService recordInstanceService;

    @Autowired
    RecordComplexityService complexityService;

    @Autowired
    RecordDuplicatedService duplicatedService;





    @Override
    public String findCodeData(String filePath) {
        //代码文件的详细位置
        String path = pathSetService.codePath()+"/"+filePath;
        File file = new File(path);
        if (!file.exists()){
            throw new SystemException(5000,"文件不存在");
        }

        try {
            String s = FileUtils.readFileToString(new File(path));
            return s;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    @Override
    public   Map<String, Object> findCode(CodeQuery codeQuery) {
        Map<String, Object> resultMap = new HashMap<>();
        List<Code> arrayList = new ArrayList<>();


        //获取扫描记录的实例
        List<RecordInstance> instanceList=null;
        if (("code").equals(codeQuery.getType())){
             instanceList = recordInstanceService.findScanInstanceByCon(codeQuery.getRecordId(),"recordId");
        }

        //重复率
        List<RecordDuplicated> duplicatedList=null;
        if(("duplicated").equals(codeQuery.getType())){
             duplicatedList = duplicatedService.findRecordDuplicatedByCon(codeQuery.getRecordId(),"recordId");
        }

        //复杂度
        List<RecordComplexity> complexityList=null;
        if(("complexity").equals(codeQuery.getType())){
             complexityList = complexityService.findRecordComplexityByCon(codeQuery.getRecordId(),"recordId");
        }

        String allPath = pathSetService.codePath() + "/" + codeQuery.getPath();
        File directory = new File(allPath);
        File[] files = directory.listFiles();
        int fileAllCount=0;  //当前文件夹下面的文件数量
        int noticeCount=0;  // 严重问题
        int errorCount=0;  //错误问题
        int severityCount=0; //警告问题
        int suggestCount=0;  //提示问题
        int duplicatedClass=0; //重复类
        int duplicatedLine=0;  //重复行
        int complexityNum=0; //复杂度
        int lineNonCount=0; //非空代码行

        for (File file : files) {
            Code code = new Code();

            //文件夹相对路径
            String relativePath;
            if (file.isDirectory()) {
                code.setType("folder");
                String s = file.getAbsolutePath();

                //计算文件夹相对路径
                getBorder(s, codeQuery);
                relativePath = StringUtils.substringAfter(codeQuery.getOmitPath(), pathSetService.codePath()+"/");

                String showName = StringUtils.substringAfter(codeQuery.getOmitPath(), allPath+"/");
                code.setName(showName);
                // 统计当前文件夹下面的文件数量
                Path currentDir = Paths.get(file.getAbsolutePath()).toAbsolutePath();
                try {
                    // 统计文件数量，包括子文件夹中的文件
                    long fileCount = Files.walk(currentDir)
                            .filter(Files::isRegularFile) // 只处理文件
                            .count();
                    code.setFileNum(Integer.valueOf(String.valueOf(fileCount)));
                    fileAllCount+=fileCount;
                } catch (IOException e) {
                    e.printStackTrace();
                    throw new RuntimeException(e);
                }
            } else {
                //文件名字
                String fileName = file.getName();
                if (fileName.endsWith(".DS_Store")){
                    continue;
                }


                code.setType("file");
                code.setName(fileName);
                code.setFileNum(1);
                fileAllCount+=1;
                //文件路径
                String filePath = file.getPath();
                relativePath = StringUtils.substringAfter(filePath, pathSetService.codePath()+"/");
            }

            code.setPath(relativePath);
            //计算扫描问题数量
            if (("code").equals(codeQuery.getType())){
                boolean problemsNum = problemsNum(instanceList, code);
                if (problemsNum){
                    noticeCount+=code.getNoticeTrouble();
                    severityCount+=code.getSeverityTrouble();
                    suggestCount+=code.getSuggestTrouble();
                    errorCount+=code.getErrorTrouble();
                }
            }
            //计算重复率
            if(("duplicated").equals(codeQuery.getType())){
                boolean duplicatedNum = duplicatedNum(duplicatedList, code);
                if (duplicatedNum){
                    duplicatedClass+=code.getDuplicatedClass();
                    duplicatedLine+=code.getDuplicatedLines();
                }
            }
            //计算复杂度
            if(("complexity").equals(codeQuery.getType())){
                boolean complexitied = complexityNum(complexityList, code);
                if (complexitied){
                    complexityNum+=code.getComplexityNum();
                 //   lineNonCount+=code.getCodeLineNon();
                }
            }

            arrayList.add(code);
        }
        //排序
        arrayList=arrayList.stream()
                .sorted(Comparator.comparing(Code::getType,
                        Comparator.<String>comparingInt(s -> s.equals("folder") ? 0 : (s.equals("file") ? 1 : 2))
                                .thenComparing(Comparator.naturalOrder())))
                .collect(Collectors.toList());

        resultMap.put("parentPath",codeQuery.getPath());
        resultMap.put("codeList",arrayList);
        resultMap.put("fileCount",fileAllCount);
        if (("code").equals(codeQuery.getType())){
            resultMap.put("noticeCount",noticeCount);
            resultMap.put("severityCount",severityCount);
            resultMap.put("suggestCount",suggestCount);
            resultMap.put("errorCount",errorCount);
        }
        if(("duplicated").equals(codeQuery.getType())){
            resultMap.put("duplicatedClass",duplicatedClass);
            resultMap.put("duplicatedLine",duplicatedLine);
        }
        if(("complexity").equals(codeQuery.getType())){
            resultMap.put("complexityNum",complexityNum);
            resultMap.put("lineNonCount",lineNonCount);
        }
        return resultMap;
    }

    @Override
    public Object findDuplicatedCodeData(String filePath) {
        //代码文件的详细位置
        String path = pathSetService.codePath()+"/"+filePath;
        File file = new File(path);
        if (!file.exists()){
            throw new SystemException(5000,"文件不存在");
        }

        List<RecordDuplicated> duplicatedList = duplicatedService.findRecordDuplicatedList(new RecordDuplicatedQuery().setPath(filePath));
        try {
            String s = FileUtils.readFileToString(new File(path));
            String[] split = s.split("\\n");

            for (int i=0;i<=split.length;i++){

            }

            return s;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * 递归获取文件(如果子级别只有目录且只有一个的时候，直接用 / 拼接不加增加层级)
     * @param path 文件夹、文件路径
     * */
    public void getBorder(String path,CodeQuery codeQuery) {
        File directory = new File(path);
        File[] files = directory.listFiles();

        if (files.length == 1 && files[0].isDirectory()) {
            String s = path + "/" + files[0].getName();
            codeQuery.setOmitPath(s);
            getBorder(s, codeQuery);
        } else {
            codeQuery.setOmitPath(path);
        }
    }



    /**
     * 计算扫描问题数量
     * @param instanceList 问题实例
     * @param code code
     * */
    public boolean problemsNum( List<RecordInstance> instanceList, Code code){
        String substringAfter = StringUtils.substringAfter(code.getPath(), "/");
        String path;
        if (("folder").equals(code.getType())){
            path=substringAfter+"/";
        }else {
            path = substringAfter;
        }
        if (CollectionUtils.isNotEmpty(instanceList)){
            List<RecordInstance> instances = instanceList.stream().filter(a -> a.getFilePath().startsWith(path)).collect(Collectors.toList());
            List<RecordInstance> severity = instances.stream().filter(a -> a.getProblemLevel() == 1).collect(Collectors.toList());
            List<RecordInstance> error = instances.stream().filter(a -> a.getProblemLevel() == 2).collect(Collectors.toList());
            List<RecordInstance> notice = instances.stream().filter(a -> a.getProblemLevel() == 3).collect(Collectors.toList());
            List<RecordInstance> suggest = instances.stream().filter(a -> a.getProblemLevel() == 4).collect(Collectors.toList());

            int severityNum = CollectionUtils.isNotEmpty(severity) ? severity.size() : 0;
            int errorNum = CollectionUtils.isNotEmpty(error) ? error.size() : 0;
            int noticeNum = CollectionUtils.isNotEmpty(notice) ? notice.size() : 0;
            int suggestNum = CollectionUtils.isNotEmpty(suggest) ? suggest.size() : 0;
            code.setSeverityTrouble(severityNum);
            code.setErrorTrouble(errorNum);
            code.setNoticeTrouble(noticeNum);
            code.setSuggestTrouble(suggestNum);

            return true;
        }
        return false;
    }

    /**
     * 计算重复率
     * @param duplicatedList 重复率list
     * @param code code
     * */
    public boolean duplicatedNum(List<RecordDuplicated> duplicatedList, Code code){
        if (CollectionUtils.isNotEmpty(duplicatedList)){
            String path;
            if (("folder").equals(code.getType())){
                path=code.getPath()+"/";
            }else {
                path = code.getPath();
            }

            List<RecordDuplicated> recordDuplicatedList = duplicatedList.stream().filter(a -> a.getPath().startsWith(path)).collect(Collectors.toList());

            if (CollectionUtils.isNotEmpty(recordDuplicatedList)){
                int lineSum = recordDuplicatedList.stream().mapToInt(RecordDuplicated::getLines).sum();
                code.setDuplicatedClass(recordDuplicatedList.size());
                code.setDuplicatedLines(lineSum);
            }else {
                code.setDuplicatedClass(0);
                code.setDuplicatedLines(0);
            }
            return true;
        }
        return false;
    }

    /**
     * 计算复杂度
     * @param complexityList 复杂度list
     * @param code code
     * */
    public boolean complexityNum(List<RecordComplexity> complexityList, Code code){
        if (CollectionUtils.isNotEmpty(complexityList)){
            String path;
            if (("folder").equals(code.getType())){
                path=code.getPath()+"/";
            }else {
                path = code.getPath();
            }

            List<RecordComplexity> recordComplexityList = complexityList.stream().filter(a -> a.getPath().startsWith(path)).collect(Collectors.toList());

            //直接计算出类型为文件的复杂度
            int complexityNum = recordComplexityList.stream().filter(a -> ("file").equals(a.getType()))
                    .mapToInt(RecordComplexity::getComplexityNum).sum();

            //直接计算出类型为文件的非空代码行
        /*    int codeLineNon = recordComplexityList.stream().filter(a -> ("file").equals(a.getType()))
                    .mapToInt(RecordComplexity::getCodeLineNon).sum();*/

            code.setComplexityNum(complexityNum);
           // code.setCodeLineNon(codeLineNon);

            return true;
        }
        return false;
    }
}

