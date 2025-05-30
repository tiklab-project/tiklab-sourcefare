package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.beans.annotation.Mapping;
import io.tiklab.toolkit.beans.annotation.Mappings;
import io.tiklab.toolkit.join.annotation.Join;
import io.tiklab.toolkit.join.annotation.JoinQuery;
import io.tiklab.user.user.model.User;

import java.io.Serializable;
import java.sql.Timestamp;

@ApiModel
@Join
@Mapper
public class ScanRecord implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="scanPlay",desc="扫描计划")
    @Mappings({
            @Mapping(source = "scanPlay.id",target = "scanPlayId")
    })
    @JoinQuery(key = "id")
    private ScanPlay scanPlay;

    @ApiProperty(name="scanObject",desc="扫描对象 （git 提交的id）")
    private String scanObject;

    @ApiProperty(name="projectId",desc="项目")
    private String projectId;

    @ApiProperty(name="scanUser",desc="扫描用户")
    @Mappings({
            @Mapping(source = "scanUser.id",target = "scanUserId")
    })
    @JoinQuery(key = "id")
    private User scanUser;

    @ApiProperty(name="scanResult",desc="扫描结果 执行中：run 通过：success、失败：fail")
    private String scanResult;

    @ApiProperty(name="scanWay",desc="扫描方式 hand：手动")
    private String scanWay;

    @ApiProperty(name="scanTime",desc="扫描耗时")
    private String scanTime;


    @ApiProperty(name="allTrouble",desc="所有问题数量")
    private Integer allTrouble;

    @ApiProperty(name="severityTrouble",desc="严重问题")
    private Integer severityTrouble;

    @ApiProperty(name="severityTrouble",desc="错误问题")
    private Integer errorTrouble;

    @ApiProperty(name="noticeTrouble",desc="警告问题")
    private Integer noticeTrouble;

    @ApiProperty(name="suggestTrouble",desc="提示问题")
    private Integer suggestTrouble;

    @ApiProperty(name="createTime",desc="创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp createTime;

    @ApiProperty(name="execLog",desc="日志")
    private String execLog;



    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public ScanPlay getScanPlay() {
        return scanPlay;
    }

    public void setScanPlay(ScanPlay scanPlay) {
        this.scanPlay = scanPlay;
    }

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public User getScanUser() {
        return scanUser;
    }

    public void setScanUser(User scanUser) {
        this.scanUser = scanUser;
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


    public String getScanTime() {
        return scanTime;
    }

    public void setScanTime(String scanTime) {
        this.scanTime = scanTime;
    }

    public String getExecLog() {
        return execLog;
    }

    public void setExecLog(String execLog) {
        this.execLog = execLog;
    }

}
