package io.tiklab.sourcefare.project.model;

import java.util.List;

public class ProjectStat {

    //项目名字
    List <String> projectNameList;

    //执行数
    List <Integer> execList;

    //最近一周的时间
    List <String> timeList;

    //每天执行的次数
    List <Integer> timeNumList;


    public List<String> getProjectNameList() {
        return projectNameList;
    }

    public void setProjectNameList(List<String> projectNameList) {
        this.projectNameList = projectNameList;
    }

    public List<Integer> getExecList() {
        return execList;
    }

    public void setExecList(List<Integer> execList) {
        this.execList = execList;
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
