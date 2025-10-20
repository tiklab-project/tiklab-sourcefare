package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
* 扫描记录实例的动态
* */
@Entity
@Table(name="wair_scan_record_instance_condition")
public class RecordInstanceCondEntity {

    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "scan_record_id" ,notNull = true)
    private String scanRecordId;

    @Column(name = "project_id",notNull = true)
    private String projectId;

    @Column(name = "record_instance_id",notNull = true)
    private String recordInstanceId;

    @Column(name = "user_id")
    private String userId;

    @Column(name = "data")
    private String data;

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

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public String getRecordInstanceId() {
        return recordInstanceId;
    }

    public void setRecordInstanceId(String recordInstanceId) {
        this.recordInstanceId = recordInstanceId;
    }

    public String getData() {
        return data;
    }

    public void setData(String data) {
        this.data = data;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }
}
