package io.tiklab.sourcefare.server.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.sourcefare.server.model.RepositoryServerQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.constraints.NotNull;
import java.util.List;

@JoinProvider(model = RepositoryServer.class)
public interface RepositoryServerService {


    /**
     * 创建仓库服务
     * @param RepositoryServer 信息
     * @return 仓库服务id
     */
    String createRepositoryServer(RepositoryServer RepositoryServer);

    /**
     * 删除仓库服务
     * @param codeGroupId 仓库服务id
     */
    void deleteRepositoryServer(String codeGroupId);

    /**
     * 更新仓库服务
     * @param RepositoryServer 仓库服务信息
     */
    void updateRepositoryServer(RepositoryServer RepositoryServer);

    @FindOne
    RepositoryServer findOne(@NotNull String id);

    /**
     * 查询所有仓库服务
     * @return 仓库服务信息列表
     */
    @FindAll
    List<RepositoryServer> findAllRepositoryServer();


    @FindList
    List<RepositoryServer> findList(List<String> idList);

    /**
     * 查询单个仓库服务
     * @param id id
     * @return 仓库服务信息
     */
    RepositoryServer findRepositoryServer(@NotNull String id);



    /**
     * 分页查询仓库服务
     * @param RepositoryServerQuery RepositoryServerQuery
     */
    Pagination<RepositoryServer> findRepositoryServerPage(RepositoryServerQuery RepositoryServerQuery);

    /**
     * 查询仓库服务
     * @param RepositoryServerQuery RepositoryServerQuery
     */
    List<RepositoryServer> findRepositoryServerList(RepositoryServerQuery RepositoryServerQuery);


}





















