package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

@Entity
@Table(name="scan_scheme_rule")
public class ScanSchemeRuleEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "scan_scheme_id" ,notNull = true)
    private String scanSchemeId;

    @Column(name = "scheme_ruleset_id",notNull = true)
    private String schemeRulesetId;

    @Column(name = "rule_Id",notNull = true)
    private String ruleId;

    @Column(name = "problem_level",notNull = true)
    private Integer problemLevel;

    @Column(name = "is_disable",notNull = true)
    private Integer isDisable;

    @Column(name = "create_time")
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

    public void setProblemLevel(Integer problemLevel) {
        this.problemLevel = problemLevel;
    }

    public String getRuleId() {
        return ruleId;
    }

    public void setRuleId(String ruleId) {
        this.ruleId = ruleId;
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

    public Integer getProblemLevel() {
        return problemLevel;
    }
}
