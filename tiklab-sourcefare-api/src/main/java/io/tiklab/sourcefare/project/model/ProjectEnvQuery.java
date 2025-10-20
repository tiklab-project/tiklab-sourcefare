package io.tiklab.sourcefare.project.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.io.Serializable;

@ApiModel
public class ProjectEnvQuery implements Serializable {


    @ApiProperty(name ="projectId",desc = "项目")
    private String  projectId;




    public String getProjectId() {
        return projectId;
    }

    public ProjectEnvQuery setProjectId(String projectId) {
        this.projectId = projectId;
        return this;
    }
}
