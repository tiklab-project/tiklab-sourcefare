package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.beans.annotation.Mapping;
import io.tiklab.toolkit.beans.annotation.Mappings;
import io.tiklab.toolkit.join.annotation.Join;
import io.tiklab.toolkit.join.annotation.JoinField;
import io.tiklab.user.user.model.User;

import java.io.Serializable;
import java.sql.Timestamp;
import java.util.List;

/*
* 扫描记录的日志
* */
@ApiModel
@Join
@Mapper
public class ScanRecordLog implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="projectId",desc="项目id")
    private String projectId;

    @ApiProperty(name="scanRecordId",desc="扫描记录的日志")
    private String scanRecordId;

    @ApiProperty(name="title",desc="标题")
    private String title;

    @ApiProperty(name="type",desc="日志类型")
    private String type;

    @ApiProperty(name="time",desc="扫描时长")
    private String time;

    @ApiProperty(name="sort",desc="排序")
    private Integer sort;

    @ApiProperty(name="state",desc="状态 0失败、1成功 2:未执行")
    private Integer state;

    @ApiProperty(name="execLog",desc="日志")
    private String execLog;

    @ApiProperty(name="scanType",desc="扫描类型")
    private String scanType;


    //扫描时间搓
    private Long timestamp;

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

    public String getExecLog() {
        return execLog;
    }

    public void setExecLog(String execLog) {
        this.execLog = execLog;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public Integer getState() {
        return state;
    }

    public void setState(Integer state) {
        this.state = state;
    }

    public Integer getSort() {
        return sort;
    }

    public void setSort(Integer sort) {
        this.sort = sort;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getScanType() {
        return scanType;
    }

    public void setScanType(String scanType) {
        this.scanType = scanType;
    }

    public Long getTimestamp() {
        return timestamp;
    }

    public void setTimestamp(Long timestamp) {
        this.timestamp = timestamp;
    }
}
