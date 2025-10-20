package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.sql.Timestamp;

/*
 * 扫描问题的统计
 * */
@ApiModel
@Join
@Mapper
public class IssueStatistic {

    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="projectId",desc="项目id")
    private String projectId;

    @ApiProperty(name="filePath",desc="文件路径")
    private String filePath;

    @ApiProperty(name="ruleType",desc="问题类型 安全:security  功能：function 规范：norm")
    private String ruleType;

    @ApiProperty(name="problemLevel",desc="问题等级 严重:1、警告：2、建议:3")
    private Integer problemLevel;

    @ApiProperty(name="problemLine",desc="问题行")
    private Integer problemLine;

    @ApiProperty(name="problemState",desc="问题状态 0(未解决) 1(已解决) ")
    private Integer problemState;

    @ApiProperty(name="ruleName",desc="问题规则名称")
    private String ruleName;

    @ApiProperty(name="problemDesc",desc="问题描述")
    private String problemDesc;

    @ApiProperty(name="createTime",desc="创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp createTime;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
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

    public Integer getProblemState() {
        return problemState;
    }

    public void setProblemState(Integer problemState) {
        this.problemState = problemState;
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

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getRuleType() {
        return ruleType;
    }

    public void setRuleType(String ruleType) {
        this.ruleType = ruleType;
    }
}
