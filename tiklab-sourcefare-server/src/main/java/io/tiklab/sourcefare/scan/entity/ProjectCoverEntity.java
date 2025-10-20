package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
* 项目覆盖率
* */
@Entity
@Table(name="wair_project_cover")
public class ProjectCoverEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "project_id" ,notNull = true)
    private String projectId;

    @Column(name = "scan_record_id",notNull = true)
    private String scanRecordId;

    @Column(name = "name",notNull = true)
    private String name;

    @Column(name = "type")
    private String type;

    @Column(name = "path")
    private String path;


    @Column(name = "parent_path")
    private String parentPath;

    @Column(name = "instructions")
    private Integer instructions;

    @Column(name = "instructions_missed")
    private Integer instructionsMissed;

    @Column(name = "instructions_percent")
    private String instructionsPercent;

    @Column(name = "branch")
    private Integer branch;

    @Column(name = "branch_missed")
    private Integer branchMissed;

    @Column(name = "branch_percent")
    private String branchPercent;

    @Column(name = "complexity")
    private Integer complexity;
    @Column(name = "complexity_missed")
    private Integer complexityMissed;
    @Column(name = "line")
    private Integer line;
    @Column(name = "line_missed")
    private Integer lineMissed;
    @Column(name = "methods")
    private Integer methods;
    @Column(name = "methods_missed")
    private Integer methodsMissed;
    @Column(name = "classes")
    private Integer classes;
    @Column(name = "classes_missed")
    private Integer classesMissed;

    @Column(name = "create_time")
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
