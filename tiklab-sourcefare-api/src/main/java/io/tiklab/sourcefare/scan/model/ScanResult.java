package io.tiklab.sourcefare.scan.model;


import java.io.Serializable;
import java.util.List;

public class ScanResult implements Serializable {

    //扫描对象id (扫描计划id或者项目id)
    private  String scanObjectId;

    //扫描结果 succeed、fail
    private  String result;

    //所有问题数量
    private Integer allTrouble;


    //严重问题数
    private Integer severityTrouble;


    //警告问题数
    private Integer noticeTrouble;

    //建议问题数
    private Integer suggestTrouble;


    //扫描时长
    private String scanTime;

    //日志
    private String log;

    List<ScanResultFile> scanResultFiles;

    public String getScanObjectId() {
        return scanObjectId;
    }

    public void setScanObjectId(String scanObjectId) {
        this.scanObjectId = scanObjectId;
    }

    public String getResult() {
        return result;
    }

    public void setResult(String result) {
        this.result = result;
    }

    public List<ScanResultFile> getScanResultFiles() {
        return scanResultFiles;
    }

    public void setScanResultFiles(List<ScanResultFile> scanResultFiles) {
        this.scanResultFiles = scanResultFiles;
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

    public Integer getAllTrouble() {
        return allTrouble;
    }

    public void setAllTrouble(Integer allTrouble) {
        this.allTrouble = allTrouble;
    }

    public String getLog() {
        return log;
    }

    public void setLog(String log) {
        this.log = log;
    }

    public String getScanTime() {
        return scanTime;
    }

    public void setScanTime(String scanTime) {
        this.scanTime = scanTime;
    }


}
