package io.tiklab.sourcefare.project.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.io.Serializable;

@ApiModel
public class ProjectCollectQuery implements Serializable {


    @ApiProperty(name ="projectId",desc = "项目")
    private String  projectId;

    @ApiProperty(name ="userId",desc = "用户id")
    private String  userId;

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public String getUserId() {
        return userId;
    }

    public ProjectCollectQuery setUserId(String userId) {
        this.userId = userId;
        return this;
    }
}
