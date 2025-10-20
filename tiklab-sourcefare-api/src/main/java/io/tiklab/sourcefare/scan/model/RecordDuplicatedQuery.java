package io.tiklab.sourcefare.scan.model;

import io.tiklab.core.order.Order;
import io.tiklab.core.order.OrderBuilders;
import io.tiklab.core.page.Page;
import io.tiklab.postin.annotation.ApiProperty;

import java.util.List;

public class RecordDuplicatedQuery {

    @ApiProperty(name ="orderParams",desc = "排序参数")
    private List<Order> orderParams = OrderBuilders.instance().desc("id").get();

    @ApiProperty(name ="pageParam",desc = "分页参数")
    private Page pageParam = new Page();

    private String projectId;

    private String scanRecordId;

    private String path;


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

    public RecordDuplicatedQuery setProjectId(String projectId) {
        this.projectId = projectId;
        return this;
    }

    public String getScanRecordId() {
        return scanRecordId;
    }

    public RecordDuplicatedQuery setScanRecordId(String scanRecordId) {
        this.scanRecordId = scanRecordId;
        return this;
    }

    public String getPath() {
        return path;
    }

    public RecordDuplicatedQuery setPath(String path) {
        this.path = path;
        return this;
    }
}
