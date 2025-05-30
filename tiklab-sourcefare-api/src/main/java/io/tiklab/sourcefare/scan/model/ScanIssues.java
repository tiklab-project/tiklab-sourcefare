package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.io.Serializable;
import java.sql.Timestamp;

@ApiModel
@Join
@Mapper
public class ScanIssues implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;

    @ApiProperty(name="scanRecordId",desc="扫描记录id")
    private String scanRecordId;

    @ApiProperty(name="issuesSeverity",desc="扫描问题严重等级 ")
    private String issuesSeverity;

    @ApiProperty(name="scanIssuesKey",desc="扫描问题的key")
    private String scanIssuesKey;

    @ApiProperty(name="fileName",desc="文件名称")
    private String fileName;

    @ApiProperty(name="ruleName",desc="规则名字")
    private String ruleName;

    @ApiProperty(name="issuesMessage",desc="问题")
    private String issuesMessage;

    @ApiProperty(name="leadInTime",desc="引入时间")
    private String leadInTime;

    @ApiProperty(name="issuesLine",desc="问题行")
    private Integer issuesLine;


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

    public String getIssuesSeverity() {
        return issuesSeverity;
    }

    public void setIssuesSeverity(String issuesSeverity) {
        this.issuesSeverity = issuesSeverity;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getRuleName() {
        return ruleName;
    }

    public void setRuleName(String ruleName) {
        this.ruleName = ruleName;
    }

    public String getIssuesMessage() {
        return issuesMessage;
    }

    public void setIssuesMessage(String issuesMessage) {
        this.issuesMessage = issuesMessage;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getLeadInTime() {
        return leadInTime;
    }

    public void setLeadInTime(String leadInTime) {
        this.leadInTime = leadInTime;
    }

    public Integer getIssuesLine() {
        return issuesLine;
    }

    public void setIssuesLine(Integer issuesLine) {
        this.issuesLine = issuesLine;
    }

    public String getScanIssuesKey() {
        return scanIssuesKey;
    }

    public void setScanIssuesKey(String scanIssuesKey) {
        this.scanIssuesKey = scanIssuesKey;
    }
}
