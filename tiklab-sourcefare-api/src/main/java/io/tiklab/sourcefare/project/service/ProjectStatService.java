package io.tiklab.sourcefare.project.service;

import io.tiklab.sourcefare.project.model.ProjectStat;
import io.tiklab.sourcefare.project.model.ScanPlayStat;

public interface ProjectStatService {

    /**
     * 通过项目的id统计扫描计划相关数据
     * @param projectId projectId
     * @return 项目id
     */
    ScanPlayStat scanPlayStat(String projectId);

    /**
     * 查询项目的统计
     */
    ProjectStat findProjectStat();
}
