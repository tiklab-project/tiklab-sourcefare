package io.tiklab.sourcefare.project.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.beans.annotation.Mapping;
import io.tiklab.toolkit.beans.annotation.Mappings;
import io.tiklab.toolkit.join.annotation.Join;
import io.tiklab.toolkit.join.annotation.JoinField;

import java.io.Serializable;

@ApiModel
@Join
@Mapper
public class ProjectRep implements Serializable {


    @ApiProperty(name="id",desc="id")
    private String id;

    @ApiProperty(name="repositoryServer",desc="仓库服务")
    @Mappings({
            @Mapping(source = "repositoryServer.id",target = "repositoryServerId")
    })
    @JoinField(key = "id")
    private RepositoryServer repositoryServer;

    @ApiProperty(name="projectId",desc="projectId")
    private String projectId;

    @ApiProperty(name="repositoryCode",desc="仓库code")
    private String repositoryCode;


    @ApiProperty(name="repositoryName",desc="代码仓库名字")
    private String repositoryName;

    @ApiProperty(name="branch",desc="分支")
    private String branch;

    @ApiProperty(name="repository_address",desc="拉取地址")
    private String repositoryAddress;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public String getRepositoryName() {
        return repositoryName;
    }

    public void setRepositoryName(String repositoryName) {
        this.repositoryName = repositoryName;
    }

    public String getBranch() {
        return branch;
    }

    public void setBranch(String branch) {
        this.branch = branch;
    }

    public String getRepositoryAddress() {
        return repositoryAddress;
    }

    public void setRepositoryAddress(String repositoryAddress) {
        this.repositoryAddress = repositoryAddress;
    }

    public RepositoryServer getRepositoryServer() {
        return repositoryServer;
    }

    public void setRepositoryServer(RepositoryServer repositoryServer) {
        this.repositoryServer = repositoryServer;
    }

    public String getRepositoryCode() {
        return repositoryCode;
    }

    public void setRepositoryCode(String repositoryCode) {
        this.repositoryCode = repositoryCode;
    }
}