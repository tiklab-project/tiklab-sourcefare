package io.tiklab.sourcefare.project.model;

import io.tiklab.postin.annotation.ApiModel;
import io.tiklab.postin.annotation.ApiProperty;
import io.tiklab.toolkit.beans.annotation.Mapper;
import io.tiklab.toolkit.join.annotation.Join;

import java.io.Serializable;

/*
*代码mode
* */
@ApiModel
@Join
@Mapper
public class Code implements Serializable {

    @ApiProperty(name="name",desc="文件夹、文件名字")
    private String name;

    @ApiProperty(name="path",desc="文件夹、文件路径")
    private String path;

    @ApiProperty(name="type",desc="类型 文件夹：folder、文件：file ")
    private String type;

    @ApiProperty(name="fileNum",desc="文件数量")
    private Integer fileNum;

    @ApiProperty(name="severityTrouble",desc="严重问题")
    private Integer severityTrouble;

    @ApiProperty(name="errorTrouble",desc="错误问题")
    private Integer errorTrouble;

    @ApiProperty(name="noticeTrouble",desc="警告问题")
    private Integer noticeTrouble;

    @ApiProperty(name="suggestTrouble",desc="提示问题")
    private Integer suggestTrouble;

    @ApiProperty(name="cover",desc="覆盖率")
    private String cover;


    /*-----重复度-----*/
    @ApiProperty(name="duplicated",desc="重复行数")
    private Integer duplicatedLines;

    @ApiProperty(name="duplicated",desc="重复类数")
    private Integer duplicatedClass;

    @ApiProperty(name="duplicated",desc="重复率")
    private String duplicatedRatio;


    /*-----复杂度-----*/
    @ApiProperty(name="complexityNum",desc="覆盖数")
    private Integer complexityNum;

    @ApiProperty(name="codeLineNon",desc="非空代码行")
    private Integer codeLineNon;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public Integer getSeverityTrouble() {
        return severityTrouble;
    }

    public void setSeverityTrouble(Integer severityTrouble) {
        this.severityTrouble = severityTrouble;
    }

    public Integer getNoticeTrouble() {
        return noticeTrouble;
    }

    public void setNoticeTrouble(Integer noticeTrouble) {
        this.noticeTrouble = noticeTrouble;
    }

    public Integer getSuggestTrouble() {
        return suggestTrouble;
    }

    public void setSuggestTrouble(Integer suggestTrouble) {
        this.suggestTrouble = suggestTrouble;
    }

    public String getCover() {
        return cover;
    }

    public void setCover(String cover) {
        this.cover = cover;
    }

    public Integer getFileNum() {
        return fileNum;
    }

    public void setFileNum(Integer fileNum) {
        this.fileNum = fileNum;
    }

    public Integer getDuplicatedLines() {
        return duplicatedLines;
    }

    public void setDuplicatedLines(Integer duplicatedLines) {
        this.duplicatedLines = duplicatedLines;
    }

    public Integer getDuplicatedClass() {
        return duplicatedClass;
    }

    public void setDuplicatedClass(Integer duplicatedClass) {
        this.duplicatedClass = duplicatedClass;
    }

    public String getDuplicatedRatio() {
        return duplicatedRatio;
    }

    public void setDuplicatedRatio(String duplicatedRatio) {
        this.duplicatedRatio = duplicatedRatio;
    }

    public Integer getComplexityNum() {
        return complexityNum;
    }

    public void setComplexityNum(Integer complexityNum) {
        this.complexityNum = complexityNum;
    }

    public Integer getCodeLineNon() {
        return codeLineNon;
    }

    public void setCodeLineNon(Integer codeLineNon) {
        this.codeLineNon = codeLineNon;
    }

    public Integer getErrorTrouble() {
        return errorTrouble;
    }

    public void setErrorTrouble(Integer errorTrouble) {
        this.errorTrouble = errorTrouble;
    }
}
