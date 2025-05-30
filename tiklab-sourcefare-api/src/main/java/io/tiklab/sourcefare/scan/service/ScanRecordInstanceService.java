package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanRecordInstance;
import io.tiklab.sourcefare.scan.model.ScanRecordInstanceQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ScanRecordInstanceService-扫描记录实例
*/
@JoinProvider(model = ScanRecordInstance.class)
public interface ScanRecordInstanceService {

    /**
    * 创建
    * @param scanRecordInstance
    * @return
    */
    String createScanRecordInstance(@NotNull @Valid ScanRecordInstance scanRecordInstance);

    /**
    * 更新
    * @param scanRecordInstance
    */
    void updateScanRecordInstance(@NotNull @Valid ScanRecordInstance scanRecordInstance);

    /**
    * 删除
    * @param id
    */
    void deleteScanRecordInstance(@NotNull String id);

    /**
     * 条件删除扫描结果实例
     * @param  key  删除条件字段
     * @param value
     */
    void deleteScanRecordInstanceByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    ScanRecordInstance findOne(@NotNull String id);

    @FindList
    List<ScanRecordInstance> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    ScanRecordInstance findScanRecordInstance(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ScanRecordInstance> findAllScanRecordInstance();

    /**
    * 查询列表
    * @param scanRecordInstanceQuery
    * @return
    */
    List<ScanRecordInstance> findScanRecordInstanceList(ScanRecordInstanceQuery scanRecordInstanceQuery);

    /**
    * 按分页查询
    * @param scanRecordInstanceQuery
    * @return
    */
    Pagination<ScanRecordInstance> findScanRecordInstancePage(ScanRecordInstanceQuery scanRecordInstanceQuery);

    /**
     * 通过扫描计划查询规则
     * @param scanRecordInstanceQuery
     * @return
     */
    Pagination<ScanRecordInstance> findRecordInstancePageByPlay(ScanRecordInstanceQuery scanRecordInstanceQuery);
}