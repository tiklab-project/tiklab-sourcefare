package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.scan.model.ScanRecord;

public interface OverviewService {

    /**
     * 通过扫描记录id查询扫描覆盖率统计
     * @param recordId 扫描记录的id
     */
    Object findProjectCoverStat(String recordId);

    /**
     * 统计扫描记录
     * @param recordId 扫描记录的id
     */
    ScanRecord findScanRecordStat(String recordId);




    /**
     * 统计扫描重复率、圈复杂度
     * @param recordId 扫描记录的id
     */
    Object findMetricStat(String recordId, String projectId);
}
