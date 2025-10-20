package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
* 项目记录的重复数据
* */
@Entity
@Table(name="wair_scan_record_duplicated")
public class RecordDuplicatedEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;


    @Column(name = "project_id",notNull = true)
    private String projectId;

    @Column(name = "record_id")
    private String recordId;

    @Column(name = "path")
    private String path;

    @Column(name = "start_line")
    private Integer startLine;


    @Column(name = "end_line")
    private Integer endLine;

    @Column(name = "lines")
    private Integer lines;

    @Column(name = "grouping")
    private String group;

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

    public String getRecordId() {
        return recordId;
    }

    public void setRecordId(String recordId) {
        this.recordId = recordId;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public Integer getStartLine() {
        return startLine;
    }

    public void setStartLine(Integer startLine) {
        this.startLine = startLine;
    }

    public Integer getEndLine() {
        return endLine;
    }

    public void setEndLine(Integer endLine) {
        this.endLine = endLine;
    }

    public Integer getLines() {
        return lines;
    }

    public void setLines(Integer lines) {
        this.lines = lines;
    }

    public String getGroup() {
        return group;
    }

    public void setGroup(String group) {
        this.group = group;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }
}
