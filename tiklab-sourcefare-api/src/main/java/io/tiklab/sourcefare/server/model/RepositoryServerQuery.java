package io.tiklab.sourcefare.server.model;

import io.tiklab.core.order.Order;
import io.tiklab.core.order.OrderBuilders;
import io.tiklab.core.page.Page;
import io.tiklab.postin.annotation.ApiProperty;

import java.util.List;

public class RepositoryServerQuery {

    @ApiProperty(name ="pageParam",desc = "分页参数")
    private Page pageParam = new Page();

    @ApiProperty(name ="orderParams",desc = "排序参数")
    private List<Order> orderParams = OrderBuilders.instance().desc("createTime").get();

    @ApiProperty(name ="userId",desc = "用户id")
    private String  userId;

    @ApiProperty(name ="repServerId",desc = "仓库服务id")
    private String  repServerId;


    @ApiProperty(name ="repo",desc = "repo")
    private String  repo;

    @ApiProperty(name ="owner",desc = "组")
    private String  owner;

    public Page getPageParam() {
        return pageParam;
    }

    public void setPageParam(Page pageParam) {
        this.pageParam = pageParam;
    }

    public List<Order> getOrderParams() {
        return orderParams;
    }

    public void setOrderParams(List<Order> orderParams) {
        this.orderParams = orderParams;
    }

    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    public String getRepServerId() {
        return repServerId;
    }

    public void setRepServerId(String repServerId) {
        this.repServerId = repServerId;
    }

    public String getRepo() {
        return repo;
    }

    public void setRepo(String repo) {
        this.repo = repo;
    }

    public String getOwner() {
        return owner;
    }

    public void setOwner(String owner) {
        this.owner = owner;
    }
}
