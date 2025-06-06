package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;
/*
* 扫描规则实体
* */
@Entity
@Table(name="wair_scan_rule")
public class ScanRuleEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "rule_set_id" ,notNull = true)
    private String ruleSetId;

    @Column(name = "rule_name",notNull = true)
    private String ruleName;

    @Column(name = "scan_tool")
    private String scanTool;

    @Column(name = "rule_type")
    private String ruleType;


    @Column(name = "rule_overview")
    private String ruleOverview;

    @Column(name = "problem_level")
    private Integer problemLevel;

    @Column(name = "description")
    private String description;

    @Column(name = "create_time")
    private Timestamp createTime;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getRuleSetId() {
        return ruleSetId;
    }

    public void setRuleSetId(String ruleSetId) {
        this.ruleSetId = ruleSetId;
    }

    public String getRuleName() {
        return ruleName;
    }

    public void setRuleName(String ruleName) {
        this.ruleName = ruleName;
    }

    public String getScanTool() {
        return scanTool;
    }

    public void setScanTool(String scanTool) {
        this.scanTool = scanTool;
    }

    public String getRuleOverview() {
        return ruleOverview;
    }

    public void setRuleOverview(String ruleOverview) {
        this.ruleOverview = ruleOverview;
    }


    public Integer getProblemLevel() {
        return problemLevel;
    }

    public void setProblemLevel(Integer problemLevel) {
        this.problemLevel = problemLevel;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getRuleType() {
        return ruleType;
    }

    public void setRuleType(String ruleType) {
        this.ruleType = ruleType;
    }
}
