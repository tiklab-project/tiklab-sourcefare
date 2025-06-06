package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanRuleSet;
import io.tiklab.sourcefare.scan.model.ScanRuleSetQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ScanRuleSetService-扫描规则集
*/
@JoinProvider(model = ScanRuleSet.class)
public interface ScanRuleSetService {

    /**
    * 创建
    * @param scanRuleSet
    * @return
    */
    String createScanRuleSet(@NotNull @Valid ScanRuleSet scanRuleSet);

    /**
     * 添加扫描规则
     * @param sql
     */
    void createScanRuleSet(@NotNull String sql);

    /**
    * 更新
    * @param scanRuleSet
    */
    void updateScanRuleSet(@NotNull @Valid ScanRuleSet scanRuleSet);



    /**
    * 删除
    * @param id
    */
    void deleteScanRuleSet(@NotNull String id);

    /**
     * 条件删除扫描结果
     * @param  key  删除条件字段
     * @param value
     */
    void deleteScanRuleSetByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    ScanRuleSet findOne(@NotNull String id);

    @FindList
    List<ScanRuleSet> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    ScanRuleSet findScanRuleSet(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ScanRuleSet> findAllScanRuleSet();

    /**
    * 查询列表
    * @param scanRuleSetQuery
    * @return
    */
    List<ScanRuleSet> findScanRuleSetList(ScanRuleSetQuery scanRuleSetQuery);

    /**
    * 按分页查询
    * @param scanRuleSetQuery
    * @return
    */
    Pagination<ScanRuleSet> findScanRuleSetPage(ScanRuleSetQuery scanRuleSetQuery);

    /**
     * 通过扫描方案id 查询扫描规则集
     * @param schemeId
     * @return
     */
    List<ScanRuleSet> findScanRuleSetBySchemeId(String schemeId);

    /**
     * 查询没有添加到当前方案的规则集
     * @param schemeId
     * @return
     */
    List<ScanRuleSet> findScanRuleSetNotScheme(String schemeId);
}