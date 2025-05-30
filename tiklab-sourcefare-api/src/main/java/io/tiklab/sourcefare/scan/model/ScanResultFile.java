package io.tiklab.sourcefare.scan.model;

public class ScanResultFile {


    //文件名称
    private  String fileName;

    //文件路径
    private  String filePath;

    //问题等级 严重:1、警告：2、建议:3
    private  Integer problemLevel;


    //问题行
    private  Integer problemLine;

    //错误规则名称
    private  String errorRuleName;


    //问题概述
    private String problemOverview;


    //问题描述
    private String problemDesc;

    //修复概述
    private String repairOverview;

    //修复描述
    private String repairDesc;

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public Integer getProblemLevel() {
        return problemLevel;
    }

    public void setProblemLevel(Integer problemLevel) {
        this.problemLevel = problemLevel;
    }

    public Integer getProblemLine() {
        return problemLine;
    }

    public void setProblemLine(Integer problemLine) {
        this.problemLine = problemLine;
    }

    public String getErrorRuleName() {
        return errorRuleName;
    }

    public void setErrorRuleName(String errorRuleName) {
        this.errorRuleName = errorRuleName;
    }

    public String getProblemOverview() {
        return problemOverview;
    }

    public void setProblemOverview(String problemOverview) {
        this.problemOverview = problemOverview;
    }

    public String getProblemDesc() {
        return problemDesc;
    }

    public void setProblemDesc(String problemDesc) {
        this.problemDesc = problemDesc;
    }

    public String getRepairOverview() {
        return repairOverview;
    }

    public void setRepairOverview(String repairOverview) {
        this.repairOverview = repairOverview;
    }

    public String getRepairDesc() {
        return repairDesc;
    }

    public void setRepairDesc(String repairDesc) {
        this.repairDesc = repairDesc;
    }
}
