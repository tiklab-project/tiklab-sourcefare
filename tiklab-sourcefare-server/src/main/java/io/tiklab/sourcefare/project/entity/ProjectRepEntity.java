package io.tiklab.sourcefare.project.entity;

import io.tiklab.core.BaseModel;
import io.tiklab.dal.jpa.annotation.*;

@Entity
@Table(name="wair_project_rep")
public class ProjectRepEntity extends BaseModel {

    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "project_id")
    private String projectId;

    @Column(name = "repository_server_id")
    private String repositoryServerId;

    @Column(name = "repository_code")
    private String repositoryCode;


    @Column(name = "repository_name")
    private String repositoryName;

    @Column(name = "branch")
    private String branch;

    @Column(name = "repository_address")
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

    public String getRepositoryServerId() {
        return repositoryServerId;
    }

    public void setRepositoryServerId(String repositoryServerId) {
        this.repositoryServerId = repositoryServerId;
    }

    public String getRepositoryCode() {
        return repositoryCode;
    }

    public void setRepositoryCode(String repositoryCode) {
        this.repositoryCode = repositoryCode;
    }
}
