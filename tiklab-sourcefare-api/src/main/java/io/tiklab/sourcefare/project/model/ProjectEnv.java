package io.tiklab.sourcefare.project.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.sourcefare.scan.model.DeployEnv;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.beans.annotation.Mapping;
import io.tiklab.toolkit.beans.annotation.Mappings;
import io.tiklab.toolkit.join.annotation.Join;
import io.tiklab.toolkit.join.annotation.JoinField;

import java.io.Serializable;

/*
* 项目环境关联表
* */

@ApiModel
@Join
@Mapper
public class ProjectEnv implements Serializable {


    @ApiProperty(name="id",desc="id")
    private String id;

    @ApiProperty(name="deployEnv",desc="环境")
    @Mappings({
            @Mapping(source = "deployEnv.id",target = "envId")
    })
    @JoinField(key = "id")
    private DeployEnv deployEnv;

    @ApiProperty(name="projectId",desc="projectId")
    private String projectId;

    @ApiProperty(name="type",desc="类型：全局overall、自定义custom")
    private String type;



    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public DeployEnv getDeployEnv() {
        return deployEnv;
    }

    public void setDeployEnv(DeployEnv deployEnv) {
        this.deployEnv = deployEnv;
    }

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }


}