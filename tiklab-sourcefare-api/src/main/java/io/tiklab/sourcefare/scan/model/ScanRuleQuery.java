package io.tiklab.sourcefare.scan.model;

import io.tiklab.core.order.Order;
import io.tiklab.core.order.OrderBuilders;
import io.tiklab.core.page.Page;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.util.List;

@ApiModel
public class ScanRuleQuery {

    @ApiProperty(name ="orderParams",desc = "排序参数")
    private List<Order> orderParams = OrderBuilders.instance().asc("problemLevel").get();

    @ApiProperty(name ="pageParam",desc = "分页参数")
    private Page pageParam = new Page();

    //规则集id
    private String ruleSetId;


    @ApiProperty(name="problemLevel",desc="规则等级")
    private Integer problemLevel;

    @ApiProperty(name="ruleName",desc="规则名称")
    private String ruleName;

    @ApiProperty(name="scanTool",desc="工具")
    private String scanTool;

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

    public String getRuleSetId() {
        return ruleSetId;
    }

    public ScanRuleQuery setRuleSetId(String ruleSetId) {
        this.ruleSetId = ruleSetId;
        return this;
    }

    public Integer getProblemLevel() {
        return problemLevel;
    }

    public ScanRuleQuery setProblemLevel(Integer problemLevel) {
        this.problemLevel = problemLevel;
        return this;
    }

    public String getRuleName() {
        return ruleName;
    }

    public ScanRuleQuery setRuleName(String ruleName) {
        this.ruleName = ruleName;
        return this;
    }

    public String getScanTool() {
        return scanTool;
    }

    public ScanRuleQuery setScanTool(String scanTool) {
        this.scanTool = scanTool;
        return this;
    }
}
