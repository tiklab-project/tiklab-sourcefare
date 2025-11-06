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

@ApiModel
@Join
@Mapper
public class ScanRecord implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="projectId",desc="项目")
    private String projectId;

    @ApiProperty(name="scanUser",desc="扫描用户")
    @Mappings({
            @Mapping(source = "scanUser.id",target = "scanUserId")
    })
    @JoinField(key = "id")
    private User scanUser;

    @ApiProperty(name="issueResult",desc="扫描结果 执行中：run 通过：success、失败：fail 、运行失败：execFail")
    private String issueResult;

    @ApiProperty(name="comResult",desc="复杂度扫描结果 success、execFail")
    private String comResult;
    @ApiProperty(name="dupResult",desc="重复度扫描结果 success、execFail")
    private String dupResult;
    @ApiProperty(name="coverResult",desc="覆盖率扫描结果 success、execFail")
    private String coverResult;

    @ApiProperty(name="scanWay",desc="扫描方式 client、server")
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



    /*-----其他字段-----*/
    @ApiProperty(name="storageCodePath",desc="代码存储位置,相对位置")
    private String storageCodePath;


    @ApiProperty(name="typeList",desc="扫描类型统计")
    private List typeList;



    private String scanResult;


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

    public User getScanUser() {
        return scanUser;
    }

    public void setScanUser(User scanUser) {
        this.scanUser = scanUser;
    }

    public String getIssueResult() {
        return issueResult;
    }

    public void setIssueResult(String issueResult) {
        this.issueResult = issueResult;
    }

    public String getComResult() {
        return comResult;
    }

    public void setComResult(String comResult) {
        this.comResult = comResult;
    }

    public String getDupResult() {
        return dupResult;
    }

    public void setDupResult(String dupResult) {
        this.dupResult = dupResult;
    }

    public String getCoverResult() {
        return coverResult;
    }

    public void setCoverResult(String coverResult) {
        this.coverResult = coverResult;
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


    public String getStorageCodePath() {
        return storageCodePath;
    }

    public void setStorageCodePath(String storageCodePath) {
        this.storageCodePath = storageCodePath;
    }

    public List getTypeList() {
        return typeList;
    }

    public void setTypeList(List typeList) {
        this.typeList = typeList;
    }

    public String getScanResult() {
        return scanResult;
    }

    public void setScanResult(String scanResult) {
        this.scanResult = scanResult;
    }
}
