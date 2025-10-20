package io.tiklab.sourcefare.project.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;

import java.io.Serializable;

@ApiModel
public class CodeQuery implements Serializable {


    @ApiProperty(name ="projectId",desc = "项目")
    private String  projectId;

    @ApiProperty(name ="path",desc = "路径")
    private String   path;

    @ApiProperty(name ="recordId",desc = "报告id")
    private String  recordId;

    @ApiProperty(name ="omitPath",desc = "omitPath")
    private String   omitPath;

    @ApiProperty(name ="type",desc = "查询类型  代码:code、重复率:duplicated、复杂度:complexity")
    private String   type;

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public String getRecordId() {
        return recordId;
    }

    public void setRecordId(String recordId) {
        this.recordId = recordId;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getOmitPath() {
        return omitPath;
    }

    public void setOmitPath(String omitPath) {
        this.omitPath = omitPath;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
