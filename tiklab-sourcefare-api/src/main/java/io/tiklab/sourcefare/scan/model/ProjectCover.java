package io.tiklab.sourcefare.scan.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.sql.Timestamp;

/*
 * 项目覆盖率
 * */
@ApiModel
@Join
@Mapper
public class ProjectCover {
    @ApiProperty(name="id",desc="id")
    private String id;


    @ApiProperty(name="projectId",desc="项目id")
    private String projectId;

    @ApiProperty(name="scanRecordId",desc="扫描记录Id")
    private String scanRecordId;

    @ApiProperty(name="name",desc="名称")
    private String name;

    @ApiProperty(name="path",desc="路径")
    private String path;

    @ApiProperty(name="type",desc="类型：package、class、method")
    private String type;


    @ApiProperty(name="parentPath",desc="父级别路径")
    private String parentPath;

    @ApiProperty(name="instructions",desc="总的指令")
    private Integer instructions;

    @ApiProperty(name="instructionsMissed",desc="未覆盖指令")
    private Integer instructionsMissed;

    @ApiProperty(name="instructionsPercent",desc="未覆盖指令百分比")
    private String instructionsPercent;

    @ApiProperty(name="branch",desc="分支:如 if、switch 等都会产生多个分支")
    private Integer branch;

    @ApiProperty(name="branchMissed",desc="未覆盖分支")
    private Integer branchMissed;

    @ApiProperty(name="branchPercent",desc="未覆盖指令百分比")
    private String branchPercent;

    @ApiProperty(name="complexity",desc="复杂度")
    private Integer complexity;

    @ApiProperty(name="complexityMissed",desc="未覆盖复杂度")
    private Integer complexityMissed;

    @ApiProperty(name="line",desc="行")
    private Integer line;

    @ApiProperty(name="lineMissed",desc="未覆盖行")
    private Integer lineMissed;

    @ApiProperty(name="scanRecordId",desc="方法")
    private Integer methods;

    @ApiProperty(name="scanRecordId",desc="未覆盖方法")
    private Integer methodsMissed;

    @ApiProperty(name="scanRecordId",desc="类")
    private Integer classes;

    @ApiProperty(name="scanRecordId",desc="未覆盖类")
    private Integer classesMissed;

    @ApiProperty(name="createTime",desc="createTime")
    private Timestamp createTime;

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

    public String getScanRecordId() {
        return scanRecordId;
    }

    public void setScanRecordId(String scanRecordId) {
        this.scanRecordId = scanRecordId;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getParentPath() {
        return parentPath;
    }

    public void setParentPath(String parentPath) {
        this.parentPath = parentPath;
    }

    public Integer getInstructions() {
        return instructions;
    }

    public void setInstructions(Integer instructions) {
        this.instructions = instructions;
    }

    public Integer getInstructionsMissed() {
        return instructionsMissed;
    }

    public void setInstructionsMissed(Integer instructionsMissed) {
        this.instructionsMissed = instructionsMissed;
    }

    public Integer getBranch() {
        return branch;
    }

    public void setBranch(Integer branch) {
        this.branch = branch;
    }

    public Integer getBranchMissed() {
        return branchMissed;
    }

    public void setBranchMissed(Integer branchMissed) {
        this.branchMissed = branchMissed;
    }

    public Integer getComplexity() {
        return complexity;
    }

    public void setComplexity(Integer complexity) {
        this.complexity = complexity;
    }

    public Integer getComplexityMissed() {
        return complexityMissed;
    }

    public void setComplexityMissed(Integer complexityMissed) {
        this.complexityMissed = complexityMissed;
    }

    public Integer getLine() {
        return line;
    }

    public void setLine(Integer line) {
        this.line = line;
    }

    public Integer getLineMissed() {
        return lineMissed;
    }

    public void setLineMissed(Integer lineMissed) {
        this.lineMissed = lineMissed;
    }

    public Integer getMethods() {
        return methods;
    }

    public void setMethods(Integer methods) {
        this.methods = methods;
    }

    public Integer getMethodsMissed() {
        return methodsMissed;
    }

    public void setMethodsMissed(Integer methodsMissed) {
        this.methodsMissed = methodsMissed;
    }

    public Integer getClasses() {
        return classes;
    }

    public void setClasses(Integer classes) {
        this.classes = classes;
    }

    public Integer getClassesMissed() {
        return classesMissed;
    }

    public void setClassesMissed(Integer classesMissed) {
        this.classesMissed = classesMissed;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getInstructionsPercent() {
        return instructionsPercent;
    }

    public void setInstructionsPercent(String instructionsPercent) {
        this.instructionsPercent = instructionsPercent;
    }

    public String getBranchPercent() {
        return branchPercent;
    }

    public void setBranchPercent(String branchPercent) {
        this.branchPercent = branchPercent;
    }
}
