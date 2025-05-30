package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.io.Serializable;
import java.sql.Timestamp;

/*
* 扫描记录实例
* */
@ApiModel
@Join
@Mapper
public class ScanRecordInstance implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;

    @ApiProperty(name="scanRecordId",desc="扫描记录id")
    private String scanRecordId;


    @ApiProperty(name="scanPlayId",desc="扫描计划id")
    private String scanPlayId;

    @ApiProperty(name="fileName",desc="文件名称")
    private String fileName;

    @ApiProperty(name="filePath",desc="文件地址")
    private String filePath;


    @ApiProperty(name="problemLevel",desc="问题等级 严重:1、警告：2、建议:3")
    private Integer problemLevel;

    @ApiProperty(name="problemLine",desc="问题行")
    private Integer problemLine;

    @ApiProperty(name="ruleName",desc="规则名称")
    private String ruleName;

    @ApiProperty(name="problemDesc",desc="问题描述")
    private String problemDesc;

    @ApiProperty(name="problemOverview",desc="问题概述")
    private String problemOverview;

    @ApiProperty(name="problemState",desc="问题状态 未解决：unsolved 、解决：solved ")
    private String problemState;

    @ApiProperty(name="repairOverview",desc="修复概述")
    private String repairOverview;

    @ApiProperty(name="repairDesc",desc="修复描述")
    private String repairDesc;

    @ApiProperty(name="importUser",desc="问题引入人")
    private String importUser;

    @ApiProperty(name="importTime",desc="引入时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp importTime;

    @ApiProperty(name="createTime",desc="创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp createTime;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getScanRecordId() {
        return scanRecordId;
    }

    public void setScanRecordId(String scanRecordId) {
        this.scanRecordId = scanRecordId;
    }

    public String getScanPlayId() {
        return scanPlayId;
    }

    public void setScanPlayId(String scanPlayId) {
        this.scanPlayId = scanPlayId;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
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

    public String getRuleName() {
        return ruleName;
    }

    public void setRuleName(String ruleName) {
        this.ruleName = ruleName;
    }

    public String getProblemDesc() {
        return problemDesc;
    }

    public void setProblemDesc(String problemDesc) {
        this.problemDesc = problemDesc;
    }

    public String getProblemState() {
        return problemState;
    }

    public void setProblemState(String problemState) {
        this.problemState = problemState;
    }

    public String getImportUser() {
        return importUser;
    }

    public void setImportUser(String importUser) {
        this.importUser = importUser;
    }

    public Timestamp getImportTime() {
        return importTime;
    }

    public void setImportTime(Timestamp importTime) {
        this.importTime = importTime;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getProblemOverview() {
        return problemOverview;
    }

    public void setProblemOverview(String problemOverview) {
        this.problemOverview = problemOverview;
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

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }
}
