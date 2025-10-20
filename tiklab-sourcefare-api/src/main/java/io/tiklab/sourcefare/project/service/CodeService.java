package io.tiklab.sourcefare.project.service;

import io.tiklab.sourcefare.project.model.Code;
import io.tiklab.sourcefare.project.model.CodeQuery;

import java.util.List;
import java.util.Map;

public interface CodeService {


    /**
     * 查询代码内容
     * @param filePath 文件地址
     */
    String findCodeData(String filePath);

    /**
     * 查询代码
     * @param codeQuery codeQuery
     */
    Map<String, Object> findCode(CodeQuery codeQuery);

    /**
     * 查询重复度代码内容
     * @param filePath 文件地址
     */
    Object findDuplicatedCodeData(String filePath);


}
