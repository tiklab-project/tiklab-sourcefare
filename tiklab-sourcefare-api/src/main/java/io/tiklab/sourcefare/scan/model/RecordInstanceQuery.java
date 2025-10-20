package io.tiklab.sourcefare.scan.model;

import io.tiklab.core.order.Order;
import io.tiklab.core.order.OrderBuilders;
import io.tiklab.core.page.Page;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.util.List;

@ApiModel
public class RecordInstanceQuery {

    @ApiProperty(name ="orderParams",desc = "排序参数")
    private List<Order> orderParams = OrderBuilders.instance().asc("problemLevel").get();

    @ApiProperty(name ="pageParam",desc = "分页参数")
    private Page pageParam = new Page();

    private String scanRecordId;


    //项目id
    private String projectId;

    //ruleName
    private String ruleName;

    //fileName
    private String fileName;

    //问题等级
    private Integer problemLevel;

    //问题行
    private Integer problemLine;

    //state
    private Integer state;

    //规则类型
    private String ruleType;

    public List<Order> getOrderParams() {
        return orderParams;
    }

    public void setOrderParams(List<Order> orderParams) {
        this.orderParams = orderParams;
    }

    public Page getPageParam() {
        return pageParam;
    }

    public void setPageParam(Page pageParam) {
        this.pageParam = pageParam;
    }

    public String getScanRecordId() {
        return scanRecordId;
    }

    public RecordInstanceQuery setScanRecordId(String scanRecordId) {
        this.scanRecordId = scanRecordId;
        return this;
    }



    public String getProjectId() {
        return projectId;
    }

    public RecordInstanceQuery setProjectId(String projectId) {
        this.projectId = projectId;
        return  this;
    }

    public Integer getProblemLevel() {
        return problemLevel;
    }

    public void setProblemLevel(Integer problemLevel) {
        this.problemLevel = problemLevel;
    }

    public String getRuleName() {
        return ruleName;
    }

    public void setRuleName(String ruleName) {
        this.ruleName = ruleName;
    }

    public Integer getState() {
        return state;
    }

    public void setState(Integer state) {
        this.state = state;
    }

    public String getRuleType() {
        return ruleType;
    }

    public void setRuleType(String ruleType) {
        this.ruleType = ruleType;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public Integer getProblemLine() {
        return problemLine;
    }

    public void setProblemLine(Integer problemLine) {
        this.problemLine = problemLine;
    }
}
