package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.RecordInstance;
import io.tiklab.sourcefare.scan.model.RecordInstanceCondQuery;
import io.tiklab.sourcefare.scan.model.RecordInstanceQuery;
import io.tiklab.sourcefare.scan.model.ScanRule;
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
@JoinProvider(model = RecordInstance.class)
public interface RecordInstanceService {

    /**
    * 创建
    * @param scanRecordInstance
    * @return
    */
    String createScanRecordInstance(@NotNull @Valid RecordInstance scanRecordInstance);

    void createScanRecordInstance(@NotNull List<RecordInstance> recordInstanceList);

    /**
    * 更新
    * @param scanRecordInstance
    */
    void updateScanRecordInstance(@NotNull @Valid RecordInstance scanRecordInstance);

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
    RecordInstance findOne(@NotNull String id);

    @FindList
    List<RecordInstance> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    RecordInstance findScanRecordInstance(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<RecordInstance> findAllScanRecordInstance();

    /**
    * 查询列表
    * @param scanRecordInstanceQuery
    * @return
    */
    List<RecordInstance> findScanRecordInstanceList(RecordInstanceQuery scanRecordInstanceQuery);




    /**
     * 查询列表
     * @param value  查询对象的value
     * @param type   类型
     */
    List<RecordInstance> findScanInstanceByCon(String value,String type);


    /**
    * 按分页查询
    * @param scanRecordInstanceQuery
    * @return
    */
    Pagination<RecordInstance> findScanRecordInstancePage(RecordInstanceQuery scanRecordInstanceQuery);

    /**
     * 通过扫描计划查询规则
     * @param scanRecordInstanceQuery
     * @return
     */
    Pagination<RecordInstance> findRecordInstancePageByPlay(RecordInstanceQuery scanRecordInstanceQuery);

    /**
     * 条件分页查询项目扫描记录、相同的只取一个
     * @param scanRecordInstanceQuery scanRecordInstanceQuery
     */
    Pagination<RecordInstance> findProjectInstancePage( RecordInstanceQuery scanRecordInstanceQuery);

    /**
     * 条件分页查询项目总的扫描记录数量
     * @param scanRecordInstanceQuery scanRecordInstanceQuery
     */
    Object findProjectInstanceNum(RecordInstanceQuery scanRecordInstanceQuery);
}