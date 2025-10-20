package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.io.Serializable;
import java.sql.Timestamp;

/*
* 扫描门禁
* */
@ApiModel
@Join
@Mapper
public class ScanDoor implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;

    @ApiProperty(name="projectId",desc="项目id")
    private String projectId;


    @ApiProperty(name="severityNum",desc="严重问题数量")
    private Integer severityNum;

    @ApiProperty(name="severityState",desc="是否启动状态 不开启 0、开启 1")
    private Integer severityState;

    @ApiProperty(name="noticeNum",desc="警告问题数量")
    private Integer noticeNum;

    @ApiProperty(name="noticeState",desc="是否启动状态 不开启 0、开启 1")
    private Integer noticeState;

    @ApiProperty(name="errorNum",desc="问题数量")
    private Integer errorNum;

    @ApiProperty(name="errorState",desc="是否启动状态 不开启 0、开启 1")
    private Integer errorState;


    @ApiProperty(name="suggestNum",desc="提示问题数量")
    private Integer suggestNum;

    @ApiProperty(name="suggestState",desc="是否启动状态 不开启 0、开启 1")
    private Integer suggestState;

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
