package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
* 每次扫描的记录
* */
@Entity
@Table(name="scan_record")
public class ScanRecordEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "scan_play_id" ,notNull = true)
    private String scanPlayId;

    @Column(name = "scan_object" )
    private String scanObject;

    @Column(name = "project_id",notNull = true)
    private String projectId;

    @Column(name = "scan_user_id")
    private String scanUserId;

    @Column(name = "scan_result")
    private String scanResult;

    @Column(name = "scan_way")
    private String scanWay;

    @Column(name = "log")
    private String execLog;

    @Column(name = "scan_time")
    private String scanTime;


    @Column(name = "all_trouble")
    private Integer allTrouble;

    @Column(name = "severity_trouble")
    private Integer severityTrouble;


    @Column(name = "error_trouble")
    private Integer errorTrouble;

    @Column(name = "notice_trouble")
    private Integer noticeTrouble;

    @Column(name = "suggest_trouble")
    private Integer suggestTrouble;

    @Column(name = "create_time")
    private Timestamp createTime;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getScanPlayId() {
        return scanPlayId;
    }

    public void setScanPlayId(String scanPlayId) {
        this.scanPlayId = scanPlayId;
    }

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public String getScanUserId() {
        return scanUserId;
    }

    public void setScanUserId(String scanUserId) {
        this.scanUserId = scanUserId;
    }

    public String getScanResult() {
        return scanResult;
    }

    public void setScanResult(String scanResult) {
        this.scanResult = scanResult;
    }

    public Integer getSeverityTrouble() {
        return severityTrouble;
    }

    public void setSeverityTrouble(Integer severityTrouble) {
        this.severityTrouble = severityTrouble;
    }

    public Integer getNoticeTrouble() {
        return noticeTrouble;
    }

    public void setNoticeTrouble(Integer noticeTrouble) {
        this.noticeTrouble = noticeTrouble;
    }

    public Integer getSuggestTrouble() {
        return suggestTrouble;
    }

    public void setSuggestTrouble(Integer suggestTrouble) {
        this.suggestTrouble = suggestTrouble;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getScanWay() {
        return scanWay;
    }

    public void setScanWay(String scanWay) {
        this.scanWay = scanWay;
    }

    public String getScanObject() {
        return scanObject;
    }

    public void setScanObject(String scanObject) {
        this.scanObject = scanObject;
    }

    public Integer getErrorTrouble() {
        return errorTrouble;
    }

    public void setErrorTrouble(Integer errorTrouble) {
        this.errorTrouble = errorTrouble;
    }

    public Integer getAllTrouble() {
        return allTrouble;
    }

    public void setAllTrouble(Integer allTrouble) {
        this.allTrouble = allTrouble;
    }

    public String getExecLog() {
        return execLog;
    }

    public void setExecLog(String execLog) {
        this.execLog = execLog;
    }

    public String getScanTime() {
        return scanTime;
    }

    public void setScanTime(String scanTime) {
        this.scanTime = scanTime;
    }
}
