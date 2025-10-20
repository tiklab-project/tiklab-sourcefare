package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.io.Serializable;
import java.sql.Timestamp;


@ApiModel
@Join
@Mapper
public class DeployEnv implements Serializable {


    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="envType",desc="环境类型")
    private String envType;

    @ApiProperty(name="envName",desc="环境名称")
    private String envName;

    @ApiProperty(name="envAddress",desc="环境应用地址")
    private String envAddress;

    @ApiProperty(name="installWay",desc="安装方式 0.全局、 1.本地、2.安装包、3.在线安装 ")
    private Integer installWay;

    @ApiProperty(name="category",desc="1 、默认 ；2、自定义")
    private Integer category=2;

    @ApiProperty(name="createTime",desc="创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp createTime;


    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getEnvType() {
        return envType;
    }

    public void setEnvType(String envType) {
        this.envType = envType;
    }

    public String getEnvName() {
        return envName;
    }

    public void setEnvName(String envName) {
        this.envName = envName;
    }

    public String getEnvAddress() {
        return envAddress;
    }

    public void setEnvAddress(String envAddress) {
        this.envAddress = envAddress;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public Integer getCategory() {
        return category;
    }

    public void setCategory(Integer category) {
        this.category = category;
    }

    public Integer getInstallWay() {
        return installWay;
    }

    public void setInstallWay(Integer installWay) {
        this.installWay = installWay;
    }
}

