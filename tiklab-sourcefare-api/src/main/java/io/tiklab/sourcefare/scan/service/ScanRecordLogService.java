package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanRecordLog;
import io.tiklab.sourcefare.scan.model.ScanRecordLogQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ScanRecordLogService-扫描记录日志
*/
@JoinProvider(model = ScanRecordLog.class)
public interface ScanRecordLogService {

    /**
    * 创建
    * @param scanRecordLog
    * @return
    */
    String createScanRecordLog(@NotNull @Valid ScanRecordLog scanRecordLog);

    /**
    * 更新
    * @param scanRecordLog
    */
    void updateScanRecordLog(@NotNull @Valid ScanRecordLog scanRecordLog);

    /**
    * 删除
    * @param id
    */
    void deleteScanRecordLog(@NotNull String id);

    /**
     * 条件删除扫描记录日志
     * @param  key  删除条件字段
     * @param value
     */
    void deleteScanRecordLogByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    ScanRecordLog findOne(@NotNull String id);

    @FindList
    List<ScanRecordLog> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    ScanRecordLog findScanRecordLog(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ScanRecordLog> findAllScanRecordLog();

    /**
    * 查询列表
    * @param scanRecordLogQuery
    * @return
    */
    List<ScanRecordLog> findScanRecordLogList(ScanRecordLogQuery scanRecordLogQuery);

    /**
    * 按分页查询
    * @param scanRecordLogQuery
    * @return
    */
    Pagination<ScanRecordLog> findScanRecordLogPage(ScanRecordLogQuery scanRecordLogQuery);


}