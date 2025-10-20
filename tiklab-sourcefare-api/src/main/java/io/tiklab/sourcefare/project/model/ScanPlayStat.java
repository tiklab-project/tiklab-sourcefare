package io.tiklab.sourcefare.project.model;

import java.util.List;

public class ScanPlayStat {

    //扫描计划名称
    List <String> scanPlayName;

    //扫描计划执行数
    List <Integer> scanPlayExec;

    //最近一周的时间
    List <String> timeList;

    //每天执行的次数
    List <Integer> timeNumList;




    public List<String> getScanPlayName() {
        return scanPlayName;
    }

    public void setScanPlayName(List<String> scanPlayName) {
        this.scanPlayName = scanPlayName;
    }

    public List<Integer> getScanPlayExec() {
        return scanPlayExec;
    }

    public void setScanPlayExec(List<Integer> scanPlayExec) {
        this.scanPlayExec = scanPlayExec;
    }

    public List<String> getTimeList() {
        return timeList;
    }

    public void setTimeList(List<String> timeList) {
        this.timeList = timeList;
    }

    public List<Integer> getTimeNumList() {
        return timeNumList;
    }

    public void setTimeNumList(List<Integer> timeNumList) {
        this.timeNumList = timeNumList;
    }
}
