package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.RecordDuplicated;
import io.tiklab.sourcefare.scan.model.RecordDuplicatedQuery;
import io.tiklab.sourcefare.scan.model.RecordInstance;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* RecordDuplicatedService-项目扫描记录的重复度
*/
@JoinProvider(model = RecordDuplicated.class)
public interface RecordDuplicatedService {

    /**
    * 创建
    * @param recordDuplicated
    * @return
    */
    String createRecordDuplicated(@NotNull @Valid RecordDuplicated recordDuplicated);

    /**
     * 创建
     * @param recordDuplicated
     * @return
     */
    void createRecordDuplicated(List<RecordDuplicated> recordDuplicated);

    /**
    * 更新
    * @param recordDuplicated
    */
    void updateRecordDuplicated(@NotNull @Valid RecordDuplicated recordDuplicated);

    /**
    * 删除
    * @param id
    */
    void deleteRecordDuplicated(@NotNull String id);

    /**
     * 条件删除项目扫描记录的重复度
     * @param  key  删除条件字段
     * @param value
     */
    void deleteRecordDuplicatedByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    RecordDuplicated findOne(@NotNull String id);

    @FindList
    List<RecordDuplicated> findList(List<String> idList);

    /**
    * 查找
    * @param id
    */

    RecordDuplicated findRecordDuplicated(@NotNull String id);

    /**
    * 查找所有
    */
    @FindAll
    List<RecordDuplicated> findAllRecordDuplicated();

    /**
    * 查询列表
    * @param recordDuplicatedQuery  recordDuplicatedQuery
    */
    List<RecordDuplicated> findRecordDuplicatedList(RecordDuplicatedQuery recordDuplicatedQuery);

    /**
     * 查询列表
     * @param value  查询对象的value
     * @param type   类型
     */
    List<RecordDuplicated> findRecordDuplicatedByCon(String value,String type);

    /**
    * 按分页查询
    * @param recordDuplicatedQuery recordDuplicatedQuery
    */
    Pagination<RecordDuplicated> findRecordDuplicatedPage(RecordDuplicatedQuery recordDuplicatedQuery);


}