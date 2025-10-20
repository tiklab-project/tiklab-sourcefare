package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
* 项目记录的复杂度数据
* */
@Entity
@Table(name="wair_scan_record_complexity")
public class RecordComplexityEntity {
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

    @Column(name = "method")
    private String method;


    @Column(name = "type")
    private String type;

    @Column(name = "complexity_num")
    private Integer complexityNum;

    @Column(name = "line")
    private Integer line;

    @Column(name = "code_line_non")
    private Integer codeLineNon;

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

    public String getMethod() {
        return method;
    }

    public void setMethod(String method) {
        this.method = method;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Integer getComplexityNum() {
        return complexityNum;
    }

    public void setComplexityNum(Integer complexityNum) {
        this.complexityNum = complexityNum;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public Integer getCodeLineNon() {
        return codeLineNon;
    }

    public void setCodeLineNon(Integer codeLineNon) {
        this.codeLineNon = codeLineNon;
    }

    public Integer getLine() {
        return line;
    }

    public void setLine(Integer line) {
        this.line = line;
    }
}
