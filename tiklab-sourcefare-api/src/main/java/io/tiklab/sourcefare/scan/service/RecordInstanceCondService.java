package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.RecordInstanceCond;
import io.tiklab.sourcefare.scan.model.RecordInstanceCondQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* RecordInstanceCondService-扫描记录实例的动态
*/
@JoinProvider(model = RecordInstanceCond.class)
public interface RecordInstanceCondService {

    /**
    * 创建
    * @param recordInstanceCond
    * @return
    */
    String createRecordInstanceCond(@NotNull @Valid RecordInstanceCond recordInstanceCond);

    /**
    * 更新
    * @param recordInstanceCond
    */
    void updateRecordInstanceCond(@NotNull @Valid RecordInstanceCond recordInstanceCond);

    /**
    * 删除
    * @param id
    */
    void deleteRecordInstanceCond(@NotNull String id);

    /**
     * 条件删除扫描结果实例
     * @param  key  删除条件字段
     * @param value
     */
    void deleteRecordInstanceCondByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    RecordInstanceCond findOne(@NotNull String id);

    @FindList
    List<RecordInstanceCond> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    RecordInstanceCond findRecordInstanceCond(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<RecordInstanceCond> findAllRecordInstanceCond();

    /**
    * 查询列表
    * @param recordInstanceCondQuery
    * @return
    */
    List<RecordInstanceCond> findRecordInstanceCondList(RecordInstanceCondQuery recordInstanceCondQuery);

    /**
    * 按分页查询
    * @param recordInstanceCondQuery
    * @return
    */
    Pagination<RecordInstanceCond> findRecordInstanceCondPage(RecordInstanceCondQuery recordInstanceCondQuery);

    /**
     * 查询列表
     * @param instanceIds
     * @return
     */
    List<RecordInstanceCond> findRecordInstanceCondList(String [] instanceIds);

}