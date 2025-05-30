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

@ApiModel
@Join
@Mapper
public class ScanSchemeRuleSet implements Serializable {

    @ApiProperty(name="id",desc="id")
    private String id;

    @ApiProperty(name="scanSchemeId",desc="扫描方案id")
    private String scanSchemeId;


    @ApiProperty(name="language",desc="语言")
    private String language;


    @ApiProperty(name="scanRuleSet",desc="规则集")
    @Mappings({
            @Mapping(source = "scanRuleSet.id",target = "ruleSetId")
    })
    @JoinQuery(key = "id")
    private ScanRuleSet scanRuleSet;

    @ApiProperty(name="createTime",desc="创建时间")
    @JsonFormat(pattern = "yyyy-MM-dd HH:mm",timezone = "GMT+8")
    private Timestamp createTime;


    /*-------其他字段----------*/

    @ApiProperty(name="ruleNum",desc="规则数量")
    private Integer ruleNum;


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

    public ScanRuleSet getScanRuleSet() {
        return scanRuleSet;
    }

    public void setScanRuleSet(ScanRuleSet scanRuleSet) {
        this.scanRuleSet = scanRuleSet;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getLanguage() {
        return language;
    }

    public void setLanguage(String language) {
        this.language = language;
    }

    public Integer getRuleNum() {
        return ruleNum;
    }

    public void setRuleNum(Integer ruleNum) {
        this.ruleNum = ruleNum;
    }
}
