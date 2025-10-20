package io.tiklab.sourcefare.scan.model;

import io.tiklab.postin.annotation.ApiProperty;

public class StatisticsQuery {


    @ApiProperty(name ="projectId",desc = "项目id")
    private String projectId;

    @ApiProperty(name ="findNum",desc = "查询次数")
    private Integer findNum=7;

    @ApiProperty(name ="findType",desc = "查询类型 issueLevel、issueType")
    private String findType;

    public String getProjectId() {
        return projectId;
    }

    public void setProjectId(String projectId) {
        this.projectId = projectId;
    }

    public Integer getFindNum() {
        return findNum;
    }

    public void setFindNum(Integer findNum) {
        this.findNum = findNum;
    }

    public String getFindType() {
        return findType;
    }

    public void setFindType(String findType) {
        this.findType = findType;
    }
}
