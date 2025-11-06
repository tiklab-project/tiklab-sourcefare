package io.tiklab.sourcefare.scan.model;

import io.tiklab.core.order.Order;
import io.tiklab.core.order.OrderBuilders;
import io.tiklab.core.page.Page;
import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.util.List;

@ApiModel
public class ScanSchemeQuery {

    @ApiProperty(name ="orderParams",desc = "排序参数")
    private List<Order> orderParams = OrderBuilders.instance().asc("language").get();

    @ApiProperty(name ="pageParam",desc = "分页参数")
    private Page pageParam = new Page();

    private Integer category;

    private String language;

    //扫描类型      静态扫描：static、编译扫描：compile、组合扫描：collect
    private String scanType;

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


    public Integer getCategory() {
        return category;
    }

    public ScanSchemeQuery setCategory(Integer category) {
        this.category = category;
        return this;
    }

    public String getLanguage() {
        return language;
    }

    public ScanSchemeQuery setLanguage(String language) {
        this.language = language;
        return this;
    }

    public String getScanType() {
        return scanType;
    }

    public void setScanType(String scanType) {
        this.scanType = scanType;
    }
}
