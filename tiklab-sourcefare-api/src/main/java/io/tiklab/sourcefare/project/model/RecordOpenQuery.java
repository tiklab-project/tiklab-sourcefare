package io.tiklab.sourcefare.project.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.io.Serializable;

@ApiModel
public class RecordOpenQuery implements Serializable {

    @ApiProperty(name ="userId",desc = "登录用户")
    private String  userId;

    @ApiProperty(name ="projectId",desc = "项目")
    private String  projectId;


    public String getUserId() {
        return userId;
    }

    public RecordOpenQuery setUserId(String userId) {
        this.userId = userId;
        return this;
    }

    public String getProjectId() {
        return projectId;
    }

    public RecordOpenQuery setProjectId(String projectId) {
        this.projectId = projectId;
        return this;
    }
}
