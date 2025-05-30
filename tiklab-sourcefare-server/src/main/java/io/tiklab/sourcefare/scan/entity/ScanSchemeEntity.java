package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

@Entity
@Table(name="scan_scheme")
public class ScanSchemeEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "scheme_name" ,notNull = true)
    private String schemeName;

    @Column(name = "language",notNull = true)
    private String language;

    @Column(name = "scan_way",notNull = true)
    private String scanWay;

    @Column(name = "deploy_env_id")
    private String deployEnvId;

    //种类 1 、默认 ；2、自定义
    @Column(name = "category")
    private Integer category;

    @Column(name = "describe")
    private String describe;

    @Column(name = "create_time")
    private Timestamp createTime;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getSchemeName() {
        return schemeName;
    }

    public void setSchemeName(String schemeName) {
        this.schemeName = schemeName;
    }

    public String getLanguage() {
        return language;
    }

    public void setLanguage(String language) {
        this.language = language;
    }

    public String getDescribe() {
        return describe;
    }

    public void setDescribe(String describe) {
        this.describe = describe;
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

    public Integer getCategory() {
        return category;
    }

    public void setCategory(Integer category) {
        this.category = category;
    }

    public String getDeployEnvId() {
        return deployEnvId;
    }

    public void setDeployEnvId(String deployEnvId) {
        this.deployEnvId = deployEnvId;
    }
}
