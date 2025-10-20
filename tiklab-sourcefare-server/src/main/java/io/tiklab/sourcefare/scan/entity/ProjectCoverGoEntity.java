package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
* go项目覆盖率
* */
@Entity
@Table(name="wair_project_cover_go")
public class ProjectCoverGoEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "project_id" ,notNull = true)
    private String projectId;

    @Column(name = "scan_record_id",notNull = true)
    private String scanRecordId;

    @Column(name = "file_path")
    private String filePath;

    @Column(name = "mode_path")
    private String modePath;

    @Column(name = "coverage_rate")
    private String coverageRate;

    @Column(name = "create_time")
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

    public String getScanRecordId() {
        return scanRecordId;
    }

    public void setScanRecordId(String scanRecordId) {
        this.scanRecordId = scanRecordId;
    }

    public String getCoverageRate() {
        return coverageRate;
    }

    public void setCoverageRate(String coverageRate) {
        this.coverageRate = coverageRate;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public String getModePath() {
        return modePath;
    }

    public void setModePath(String modePath) {
        this.modePath = modePath;
    }
}
