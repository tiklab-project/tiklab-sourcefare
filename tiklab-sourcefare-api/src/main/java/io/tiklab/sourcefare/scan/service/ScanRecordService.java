package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.model.ScanRecordQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ScanRecordService-扫描记录
*/
@JoinProvider(model = ScanRecord.class)
public interface ScanRecordService {

    /**
    * 创建
    * @param scanRecord
    * @return
    */
    String createScanRecord(@NotNull @Valid ScanRecord scanRecord);



    /**
    * 更新
    * @param scanRecord
    */
    void updateScanRecord(@NotNull @Valid ScanRecord scanRecord);

    /**
    * 删除
    * @param id
    */
    void deleteScanRecord(@NotNull String id);

    /**
     * 通过项目id删除扫描记录
     * @param projectId 项目id
     * @param recordId 记录id
     */
    void deleteScanRecordByProjectId(String projectId,String recordId);

    /**
     * 条件删除扫描结果
     * @param  key  删除条件字段
     * @param value
     */
    void deleteScanRecordByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    ScanRecord findOne(@NotNull String id);

    @FindList
    List<ScanRecord> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    ScanRecord findScanRecord(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ScanRecord> findAllScanRecord();

    /**
    * 查询列表
    * @param scanRecordQuery
    * @return
    */
    List<ScanRecord> findScanRecordList(ScanRecordQuery scanRecordQuery);

    /**
     * 查询列表
     * @param projectId
     * @return
     */
    List<ScanRecord> findScanRecordListByProjectId(String projectId);

    //查询最新的扫描记录

    ScanRecord findNewScanRecord(String projectId);
    /**
    * 按分页查询
    * @param scanRecordQuery
    * @return
    */
    Pagination<ScanRecord> findScanRecordPage(ScanRecordQuery scanRecordQuery);


}