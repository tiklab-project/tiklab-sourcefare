package io.tiklab.sourcefare.scan.model;

import com.fasterxml.jackson.annotation.JsonFormat;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.beans.annotation.Mapping;
import io.tiklab.toolkit.beans.annotation.Mappings;
import io.tiklab.toolkit.join.annotation.Join;
import io.tiklab.toolkit.join.annotation.JoinQuery;

import java.io.Serializable;
import java.sql.Timestamp;

/*
* 扫描方案的规则关系
* */
@ApiModel
@Join
@Mapper
public class ScanSchemeRule implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;

    @ApiProperty(name="scanSchemeId",desc="扫描方案id")
    private String scanSchemeId;


    @ApiProperty(name="scheme_ruleset_id",desc="扫描方案规则集关系表id")
    private String schemeRulesetId;



    @ApiProperty(name="scanRule",desc="规则")
    @Mappings({
            @Mapping(source = "scanRule.id",target = "ruleId")
    })
    @JoinQuery(key = "id")
    private ScanRule scanRule;

    @ApiProperty(name="problemLevel",desc="问题等级 严重:1、警告：2、建议:3")
    private Integer problemLevel;

    @ApiProperty(name="isDisable",desc="是否禁用 0：使用 1禁用")
    private Integer isDisable=0;

    @ApiProperty(name="createTime",desc="创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp createTime;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getScanSchemeId() {
        return scanSchemeId;
    }

    public void setScanSchemeId(String scanSchemeId) {
        this.scanSchemeId = scanSchemeId;
    }

    public String getSchemeRulesetId() {
        return schemeRulesetId;
    }

    public void setSchemeRulesetId(String schemeRulesetId) {
        this.schemeRulesetId = schemeRulesetId;
    }

    public ScanRule getScanRule() {
        return scanRule;
    }

    public void setScanRule(ScanRule scanRule) {
        this.scanRule = scanRule;
    }

    public Integer getProblemLevel() {
        return problemLevel;
    }

    public void setProblemLevel(Integer problemLevel) {
        this.problemLevel = problemLevel;
    }

    public Integer getIsDisable() {
        return isDisable;
    }

    public void setIsDisable(Integer isDisable) {
        this.isDisable = isDisable;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }
}
