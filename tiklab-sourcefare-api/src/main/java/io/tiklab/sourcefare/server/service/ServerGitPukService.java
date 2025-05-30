package io.tiklab.sourcefare.server.service;

import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.sourcefare.server.model.ThirdBranch;
import io.tiklab.sourcefare.server.model.ThirdRepository;

import java.util.List;

public interface ServerGitPukService {
    /**
     * 通过仓库服务信息查询仓库代码
     * @param repositoryServer repositoryServer
     */
    List<ThirdRepository> findRepositoryList(RepositoryServer repositoryServer);

    /**
     * 通过仓库的分支
     * @param repId 仓库id
     * @param repServerId 服务的id
     */
    List<ThirdBranch> findRepositoryBranchList(String repId, String repServerId);


}
