package io.tiklab.sourcefare.scan.entity;

import io.tiklab.dal.jpa.annotation.*;

import java.sql.Timestamp;

/*
* 扫描记录的实例
* */
@Entity
@Table(name="wair_scan_record_instance")
public class ScanRecordInstanceEntity {
    @Id
    @GeneratorValue(length=12)
    @Column(name = "id")
    private String id;

    @Column(name = "scan_record_id" ,notNull = true)
    private String scanRecordId;

    @Column(name = "scan_play_id",notNull = true)
    private String scanPlayId;

    @Column(name = "file_name",notNull = true)
    private String fileName;

    @Column(name = "file_path")
    private String filePath;


    @Column(name = "problem_level")
    private Integer problemLevel;

    @Column(name = "problem_line")
    private Integer problemLine;

    @Column(name = "rule_name")
    private String ruleName;

    @Column(name = "repair_overview")
    private String repairOverview;

    @Column(name = "repair_desc")
    private String repairDesc;


    @Column(name = "problem_overview")
    private String problemOverview;

    @Column(name = "problem_desc")
    private String problemDesc;

    @Column(name = "problem_state")
    private String problemState;

    @Column(name = "import_user")
    private String importUser;

    @Column(name = "import_time")
    private Timestamp importTime;

    @Column(name = "create_time")
    private Timestamp createTime;

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getScanRecordId() {
        return scanRecordId;
    }

    public void setScanRecordId(String scanRecordId) {
        this.scanRecordId = scanRecordId;
    }

    public String getScanPlayId() {
        return scanPlayId;
    }

    public void setScanPlayId(String scanPlayId) {
        this.scanPlayId = scanPlayId;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public Integer getProblemLevel() {
        return problemLevel;
    }

    public void setProblemLevel(Integer problemLevel) {
        this.problemLevel = problemLevel;
    }

    public Integer getProblemLine() {
        return problemLine;
    }

    public void setProblemLine(Integer problemLine) {
        this.problemLine = problemLine;
    }

    public String getRuleName() {
        return ruleName;
    }

    public void setRuleName(String ruleName) {
        this.ruleName = ruleName;
    }

    public String getProblemDesc() {
        return problemDesc;
    }

    public void setProblemDesc(String problemDesc) {
        this.problemDesc = problemDesc;
    }

    public String getProblemState() {
        return problemState;
    }

    public void setProblemState(String problemState) {
        this.problemState = problemState;
    }

    public String getImportUser() {
        return importUser;
    }

    public void setImportUser(String importUser) {
        this.importUser = importUser;
    }

    public Timestamp getImportTime() {
        return importTime;
    }

    public void setImportTime(Timestamp importTime) {
        this.importTime = importTime;
    }

    public Timestamp getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Timestamp createTime) {
        this.createTime = createTime;
    }

    public String getProblemOverview() {
        return problemOverview;
    }

    public void setProblemOverview(String problemOverview) {
        this.problemOverview = problemOverview;
    }

    public String getRepairOverview() {
        return repairOverview;
    }

    public void setRepairOverview(String repairOverview) {
        this.repairOverview = repairOverview;
    }

    public String getRepairDesc() {
        return repairDesc;
    }

    public void setRepairDesc(String repairDesc) {
        this.repairDesc = repairDesc;
    }

    public String getFilePath() {
        return filePath;
    }

    public void setFilePath(String filePath) {
        this.filePath = filePath;
    }
}
