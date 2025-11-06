package io.tiklab.sourcefare.project.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.sourcefare.scan.model.ScanScheme;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.beans.annotation.Mapping;
import io.tiklab.toolkit.beans.annotation.Mappings;
import io.tiklab.toolkit.join.annotation.Join;
import io.tiklab.toolkit.join.annotation.JoinField;
import io.tiklab.user.user.model.User;

import java.io.Serializable;
import java.sql.Timestamp;

@ApiModel
@Join
@Mapper
public class Project implements Serializable {


    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="name",desc="项目名称")
    private String name;

    @ApiProperty(name="scanWay",desc="扫描方式 client、server、serverUpload")
    private String scanWay;


    @ApiProperty(name="scanScheme",desc="扫描方案")
    @Mappings({
            @Mapping(source = "scanScheme.id",target = "scanSchemeId")
    })
    @JoinField(key = "id")
    private ScanScheme scanScheme;

    @Mappings({
            @Mapping(source = "user.id",target = "userId")
    })
    @JoinField(key = "id")
    private User user;

    @ApiProperty(name="projectDesc",desc="描述")
    private String projectDesc;

    @ApiProperty(name="category",desc="种类  demo（演示）、formal(正式的)、demox (演示删除的)")
    private String category="formal";

    @ApiProperty(name="rules",desc="权限")
    private String rules;

    @ApiProperty(name="color")
    private Integer color;

    @ApiProperty(name="cover",desc = "是否启用覆盖率测试，0不开启、1开启")
    private Integer cover;

    @ApiProperty(name="complexity",desc = "是否启用复杂度测试，0不开启、1开启")
    private Integer complexity;

    @ApiProperty(name="buildPath",desc = "构建路径")
    private String buildPath;

    @ApiProperty(name="scanResult",desc = "最新扫描结果")
    private String scanResult;

    @ApiProperty(name="createTime",desc="创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd",timezone = "GMT+8")
    private Timestamp createTime;


    @ApiProperty(name="updateTime",desc="更新时间")
    @JsonFormat(pattern = "yyyy-MM-dd",timezone = "GMT+8")
    private Timestamp updateTime;

    @ApiProperty(name="扫描时间",desc="scanTime")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp scanTime;

    @ApiProperty(name="scanWay",desc="扫描方式  静态扫描：static、编译扫描：compile、组合扫描：collect")
    private String scanType="static";

    @ApiProperty(name="scanLanguage",desc="扫描语言 java、javascript、c++ 、python 、c#")
    private String scanLanguage;



    /*----其他字段------*/

    //收藏
    private boolean collect;


    //仓库服务端地址
    private String repositoryServerId;

    //代码仓库名字
    private String repositoryName;

    //代码仓库分支
    private String branch;

    //代码仓库拉取地址
    private String repositoryAddress;

    //仓库code
    private String repositoryCode;


    //执行环境
    private String excEnv;

    //jdk环境
    private String jdkEnv;

    //python环境
    private String python;

    //类型：全局overall、自定义custom
    private String type;

    @ApiProperty(name="newScanTime",desc="最新扫描时间")
    private String newScanTime;



    //是否允许删除
    private boolean isDelete;

    //是否允许删除
    private boolean isUpdate;


    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getProjectDesc() {
        return projectDesc;
    }

    public void setProjectDesc(String projectDesc) {
        this.projectDesc = projectDesc;
    }

    public Integer getColor() {
        return color;
    }

    public void setColor(Integer color) {
        this.color = color;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public Timestamp getUpdateTime() {
        return updateTime;
    }

    public void setUpdateTime(Timestamp updateTime) {
        this.updateTime = updateTime;
    }

    public User getUser() {
        return user;
    }

    public void setUser(User user) {
        this.user = user;
    }

    public String getRules() {
        return rules;
    }

    public void setRules(String rules) {
        this.rules = rules;
    }

    public String getCategory() {
        return category;
    }

    public void setCategory(String category) {
        this.category = category;
    }

    public String getScanWay() {
        return scanWay;
    }

    public void setScanWay(String scanWay) {
        this.scanWay = scanWay;
    }


    public ScanScheme getScanScheme() {
        return scanScheme;
    }

    public void setScanScheme(ScanScheme scanScheme) {
        this.scanScheme = scanScheme;
    }

    public Timestamp getScanTime() {
        return scanTime;
    }

    public void setScanTime(Timestamp scanTime) {
        this.scanTime = scanTime;
    }

    public String getRepositoryServerId() {
        return repositoryServerId;
    }

    public void setRepositoryServerId(String repositoryServerId) {
        this.repositoryServerId = repositoryServerId;
    }

    public String getRepositoryName() {
        return repositoryName;
    }

    public void setRepositoryName(String repositoryName) {
        this.repositoryName = repositoryName;
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

    public String getNewScanTime() {
        return newScanTime;
    }

    public void setNewScanTime(String newScanTime) {
        this.newScanTime = newScanTime;
    }

    public String getRepositoryCode() {
        return repositoryCode;
    }

    public void setRepositoryCode(String repositoryCode) {
        this.repositoryCode = repositoryCode;
    }

    public Integer getCover() {
        return cover;
    }

    public void setCover(Integer cover) {
        this.cover = cover;
    }

    public String getExcEnv() {
        return excEnv;
    }

    public void setExcEnv(String excEnv) {
        this.excEnv = excEnv;
    }

    public String getJdkEnv() {
        return jdkEnv;
    }

    public void setJdkEnv(String jdkEnv) {
        this.jdkEnv = jdkEnv;
    }

    public boolean isCollect() {
        return collect;
    }

    public void setCollect(boolean collect) {
        this.collect = collect;
    }

    public String getScanResult() {
        return scanResult;
    }

    public void setScanResult(String scanResult) {
        this.scanResult = scanResult;
    }

    public Integer getComplexity() {
        return complexity;
    }

    public void setComplexity(Integer complexity) {
        this.complexity = complexity;
    }

    public String getPython() {
        return python;
    }

    public void setPython(String python) {
        this.python = python;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public boolean isDelete() {
        return isDelete;
    }

    public void setDelete(boolean delete) {
        isDelete = delete;
    }

    public boolean isUpdate() {
        return isUpdate;
    }

    public void setUpdate(boolean update) {
        isUpdate = update;
    }

    public String getScanType() {
        return scanType;
    }

    public void setScanType(String scanType) {
        this.scanType = scanType;
    }

    public String getScanLanguage() {
        return scanLanguage;
    }

    public void setScanLanguage(String scanLanguage) {
        this.scanLanguage = scanLanguage;
    }

    public String getBuildPath() {
        return buildPath;
    }

    public void setBuildPath(String buildPath) {
        this.buildPath = buildPath;
    }
}