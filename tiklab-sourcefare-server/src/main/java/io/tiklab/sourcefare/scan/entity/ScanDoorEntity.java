package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
 * 扫描门禁
 * */
@Entity
@Table(name="wair_scan_door")
public class ScanDoorEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "project_id",notNull = true)
    private String projectId;

    @Column(name = "severity_num")
    private Integer severityNum;

    @Column(name = "severity_state")
    private Integer severityState;

    @Column(name = "notice_num")
    private Integer noticeNum;

    @Column(name = "notice_state")
    private Integer noticeState;

    @Column(name = "error_num")
    private Integer errorNum;

    @Column(name = "error_state")
    private Integer errorState;

    @Column(name = "suggest_num")
    private Integer suggestNum;

    @Column(name = "suggest_state")
    private Integer suggestState;

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

    public Integer getSeverityNum() {
        return severityNum;
    }

    public void setSeverityNum(Integer severityNum) {
        this.severityNum = severityNum;
    }

    public Integer getSeverityState() {
        return severityState;
    }

    public void setSeverityState(Integer severityState) {
        this.severityState = severityState;
    }

    public Integer getNoticeNum() {
        return noticeNum;
    }

    public void setNoticeNum(Integer noticeNum) {
        this.noticeNum = noticeNum;
    }

    public Integer getNoticeState() {
        return noticeState;
    }

    public void setNoticeState(Integer noticeState) {
        this.noticeState = noticeState;
    }

    public Integer getErrorNum() {
        return errorNum;
    }

    public void setErrorNum(Integer errorNum) {
        this.errorNum = errorNum;
    }

    public Integer getErrorState() {
        return errorState;
    }

    public void setErrorState(Integer errorState) {
        this.errorState = errorState;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public Integer getSuggestNum() {
        return suggestNum;
    }

    public void setSuggestNum(Integer suggestNum) {
        this.suggestNum = suggestNum;
    }

    public Integer getSuggestState() {
        return suggestState;
    }

    public void setSuggestState(Integer suggestState) {
        this.suggestState = suggestState;
    }
}
