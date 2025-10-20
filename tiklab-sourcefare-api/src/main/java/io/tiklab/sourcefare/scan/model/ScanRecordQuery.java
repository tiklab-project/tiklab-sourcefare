package io.tiklab.sourcefare.scan.model;

import io.tiklab.core.order.Order;
import io.tiklab.core.order.OrderBuilders;
import io.tiklab.core.page.Page;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.util.List;

@ApiModel
public class ScanRecordQuery {

    @ApiProperty(name ="orderParams",desc = "排序参数")
    private List<Order> orderParams = OrderBuilders.instance().desc("createTime").get();

    @ApiProperty(name ="pageParam",desc = "分页参数")
    private Page pageParam = new Page();

    private String projectId;



    @ApiProperty(name ="playWay",desc = "扫描计划方式")
    private String playWay;

    @ApiProperty(name ="scanResult",desc = "扫描结果")
    private String scanResult;


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

    public ScanRecordQuery setProjectId(String projectId) {
        this.projectId = projectId;
        return this;
    }


    public String getScanResult() {
        return scanResult;
    }

    public void setScanResult(String scanResult) {
        this.scanResult = scanResult;
    }

    public String getPlayWay() {
        return playWay;
    }

    public void setPlayWay(String playWay) {
        this.playWay = playWay;
    }
}
