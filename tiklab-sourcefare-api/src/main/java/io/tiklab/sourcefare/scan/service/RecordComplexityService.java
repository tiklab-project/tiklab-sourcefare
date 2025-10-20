package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.RecordComplexity;
import io.tiklab.sourcefare.scan.model.RecordComplexityQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* RecordComplexityService-项目扫描记录的复杂度
*/
@JoinProvider(model = RecordComplexity.class)
public interface RecordComplexityService {

    /**
    * 创建
    * @param recordComplexity
    * @return
    */
    String createRecordComplexity(@NotNull @Valid RecordComplexity recordComplexity);

    void createRecordComplexity( List<RecordComplexity> arrayList);


    /**
    * 更新
    * @param recordComplexity
    */
    void updateRecordComplexity(@NotNull @Valid RecordComplexity recordComplexity);

    /**
    * 删除
    * @param id
    */
    void deleteRecordComplexity(@NotNull String id);

    /**
     * 条件删除项目扫描记录的复杂度
     * @param  key  删除条件字段
     * @param value
     */
    void deleteRecordComplexityByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    RecordComplexity findOne(@NotNull String id);

    @FindList
    List<RecordComplexity> findList(List<String> idList);

    /**
    * 查找
    * @param id
    */

    RecordComplexity findRecordComplexity(@NotNull String id);

    /**
    * 查找所有
    */
    @FindAll
    List<RecordComplexity> findAllRecordComplexity();

    /**
    * 查询列表
    * @param recordComplexityQuery  recordComplexityQuery
    */
    List<RecordComplexity> findRecordComplexityList(RecordComplexityQuery recordComplexityQuery);

    List<RecordComplexity> findRecordComplexityByCon(String value,String type);

    /**
    * 按分页查询
    * @param recordComplexityQuery recordComplexityQuery
    */
    Pagination<RecordComplexity> findRecordComplexityPage(RecordComplexityQuery recordComplexityQuery);


}