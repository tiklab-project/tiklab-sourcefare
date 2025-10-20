package io.tiklab.sourcefare.scan.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.sql.Timestamp;


/*
 * go项目覆盖率
 * */
@ApiModel
@Join
@Mapper
public class ProjectCoverGo {

    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="projectId",desc="项目id")
    private String projectId;

    @ApiProperty(name="scanRecordId",desc="扫描记录Id")
    private String scanRecordId;

    @ApiProperty(name="filePath",desc="文件路径")
    private String filePath;

    @ApiProperty(name="modePath",desc="mode path")
    private String modePath;

    @ApiProperty(name="coverageRate",desc="覆盖率")
    private String coverageRate;

    @ApiProperty(name="createTime",desc="createTime")
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
}
