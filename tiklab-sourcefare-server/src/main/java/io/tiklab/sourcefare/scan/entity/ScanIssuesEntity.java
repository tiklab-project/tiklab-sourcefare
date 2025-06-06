package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
* 扫描问题
* */
@Entity
@Table(name="wair_scan_issues")
public class ScanIssuesEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "scan_record_id" ,notNull = true)
    private String scanRecordId;

    @Column(name = "issues_severity",notNull = true)
    private String issuesSeverity;

    @Column(name = "file_name",notNull = true)
    private String fileName;

    @Column(name = "rule_name")
    private String ruleName;

    @Column(name = "issues_message")
    private String issuesMessage;

    @Column(name = "lead_in_time")
    private Timestamp leadInTime;

    @Column(name = "issues_line")
    private Integer issuesLine;

    @Column(name = "scan_issues_key")
    private Integer scanIssuesKey;


    @Column(name = "create_time")
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

    public Timestamp getLeadInTime() {
        return leadInTime;
    }

    public void setLeadInTime(Timestamp leadInTime) {
        this.leadInTime = leadInTime;
    }

    public Integer getIssuesLine() {
        return issuesLine;
    }

    public void setIssuesLine(Integer issuesLine) {
        this.issuesLine = issuesLine;
    }

    public Integer getScanIssuesKey() {
        return scanIssuesKey;
    }

    public void setScanIssuesKey(Integer scanIssuesKey) {
        this.scanIssuesKey = scanIssuesKey;
    }
}
