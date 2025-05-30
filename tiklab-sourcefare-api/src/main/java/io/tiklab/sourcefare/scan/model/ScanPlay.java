package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.sourcefare.server.model.RepositoryServer;
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
public class ScanPlay implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;

    @ApiProperty(name="playName",desc="计划名称")
    private String playName;

    @ApiProperty(name="projectId",desc="项目id")
    private String projectId;

    @ApiProperty(name="branch",desc="分支")
    private String branch;

    @ApiProperty(name="scanWay",desc="扫描方式 client、server")
    private String scanWay;

    @ApiProperty(name="repositoryAddress",desc="代码仓库路径")
    private String repositoryAddress;

    @ApiProperty(name="repositoryServer",desc="扫描方案")
    @Mappings({
            @Mapping(source = "repositoryServer.id",target = "repositoryServerId")
    })
    @JoinQuery(key = "id")
    private RepositoryServer repositoryServer;

    @ApiProperty(name="scanScheme",desc="扫描方案")
    @Mappings({
            @Mapping(source = "scanScheme.id",target = "scanSchemeId")
    })
    @JoinQuery(key = "id")
    private ScanScheme scanScheme;

    @ApiProperty(name="user",desc="用户")
    @Mappings({
            @Mapping(source = "user.id",target = "userId")
    })
    @JoinQuery(key = "id")
    private User user;


    @ApiProperty(name="repositoryName",desc="仓库名字")
    private String repositoryName;

    @ApiProperty(name="scanType",desc="扫描方式 服务端扫描：server、客户端扫描：client")
    private String scanType;


    @ApiProperty(name="扫描时间",desc="scan_time")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp scanTime;

    @ApiProperty(name="createTime",desc="创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp createTime;

    /*------其他字段--------*/
    private String userName;

    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp latScanTime;

    @ApiProperty(name="allReqNum",desc="扫描结果")
    private String scanResult;

    @ApiProperty(name="allReqNum",desc="总问题数量")
    private Integer allReqNum;

    @ApiProperty(name="scanObject",desc="扫描对象 （git 提交的id）")
    private String scanObject;

    private String recordId;

    public String getScanType() {
        return scanType;
    }

    public void setScanType(String scanType) {
        this.scanType = scanType;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getPlayName() {
        return playName;
    }

    public void setPlayName(String playName) {
        this.playName = playName;
    }

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public String getBranch() {
        return branch;
    }

    public void setBranch(String branch) {
        this.branch = branch;
    }

    public String getRepositoryAddress() {
        return repositoryAddress;
    }

    public void setRepositoryAddress(String repositoryAddress) {
        this.repositoryAddress = repositoryAddress;
    }

    public ScanScheme getScanScheme() {
        return scanScheme;
    }

    public void setScanScheme(ScanScheme scanScheme) {
        this.scanScheme = scanScheme;
    }

    public RepositoryServer getRepositoryServer() {
        return repositoryServer;
    }

    public void setRepositoryServer(RepositoryServer repositoryServer) {
        this.repositoryServer = repositoryServer;
    }

    public String getRepositoryName() {
        return repositoryName;
    }

    public void setRepositoryName(String repositoryName) {
        this.repositoryName = repositoryName;
    }

    public Timestamp getScanTime() {
        return scanTime;
    }

    public void setScanTime(Timestamp scanTime) {
        this.scanTime = scanTime;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public Timestamp getLatScanTime() {
        return latScanTime;
    }

    public void setLatScanTime(Timestamp latScanTime) {
        this.latScanTime = latScanTime;
    }

    public String getScanWay() {
        return scanWay;
    }

    public void setScanWay(String scanWay) {
        this.scanWay = scanWay;
    }

    public String getScanResult() {
        return scanResult;
    }

    public void setScanResult(String scanResult) {
        this.scanResult = scanResult;
    }

    public Integer getAllReqNum() {
        return allReqNum;
    }

    public void setAllReqNum(Integer allReqNum) {
        this.allReqNum = allReqNum;
    }

    public String getScanObject() {
        return scanObject;
    }

    public void setScanObject(String scanObject) {
        this.scanObject = scanObject;
    }

    public String getRecordId() {
        return recordId;
    }

    public void setRecordId(String recordId) {
        this.recordId = recordId;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }


}
