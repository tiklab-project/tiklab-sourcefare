package io.tiklab.sourcefare.scan.model;

import io.tiklab.core.order.Order;
import io.tiklab.core.order.OrderBuilders;
import io.tiklab.core.page.Page;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.util.List;

@ApiModel
public class IssueStatisticQuery {

    @ApiProperty(name ="orderParams",desc = "排序参数")
    private List<Order> orderParams = OrderBuilders.instance().asc("problemLevel").get();

    @ApiProperty(name ="pageParam",desc = "分页参数")
    private Page pageParam = new Page();

    @ApiProperty(name ="projectId",desc = "项目id")
    private String  projectId;

    @ApiProperty(name ="filePath",desc = "文件路径")
    private String  filePath;

    @ApiProperty(name ="ruleName",desc = "问题规则名称")
    private String  ruleName;

    @ApiProperty(name ="ruleType",desc = "问题类型")
    private String  ruleType;

    @ApiProperty(name ="problemLine",desc = "文件行")
    private Integer  problemLine;

    @ApiProperty(name ="problemLine",desc = "问题状态")
    private Integer  problemState;

    @ApiProperty(name ="problemLevel",desc = "问题等级")
    private Integer  problemLevel;



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

    public String getProjectId() {
        return projectId;
    }

    public IssueStatisticQuery setProjectId(String projectId) {
        this.projectId = projectId;
        return this;
    }

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }

    public String getRuleName() {
        return ruleName;
    }

    public void setRuleName(String ruleName) {
        this.ruleName = ruleName;
    }

    public Integer getProblemLine() {
        return problemLine;
    }

    public void setProblemLine(Integer problemLine) {
        this.problemLine = problemLine;
    }

    public Integer getProblemState() {
        return problemState;
    }

    public void setProblemState(Integer problemState) {
        this.problemState = problemState;
    }

    public String getRuleType() {
        return ruleType;
    }

    public void setRuleType(String ruleType) {
        this.ruleType = ruleType;
    }

    public Integer getProblemLevel() {
        return problemLevel;
    }

    public void setProblemLevel(Integer problemLevel) {
        this.problemLevel = problemLevel;
    }
}
