package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.sql.Timestamp;

/*
 * 项目记录的复杂度数据
 * */
@ApiModel
@Join
@Mapper
public class RecordComplexity {

    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="projectId",desc="项目id")
    private String projectId;


    @ApiProperty(name="recordId",desc="扫描记录id")
    private String recordId;


    @ApiProperty(name="path",desc="文件路径")
    private String path;

    @ApiProperty(name="method",desc="方法")
    private String method;


    @ApiProperty(name="type",desc="类型 file、project")
    private String type;


    @ApiProperty(name="complexityNum",desc="复杂度")
    private Integer complexityNum;

    @ApiProperty(name="line",desc="行")
    private Integer line;

    @ApiProperty(name="codeLineNon",desc="非空代码行")
    private Integer codeLineNon;

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

    public Integer getCodeLineNon() {
        return codeLineNon;
    }

    public void setCodeLineNon(Integer codeLineNon) {
        this.codeLineNon = codeLineNon;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public Integer getLine() {
        return line;
    }

    public void setLine(Integer line) {
        this.line = line;
    }
}
