package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanPlayQuery;
import io.tiklab.sourcefare.scan.model.ScanPlay;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ScanPlayService-扫描计划
*/
@JoinProvider(model = ScanPlay.class)
public interface ScanPlayService {

    /**
    * 创建
    * @param scanPlay
    * @return
    */
    String createScanPlay(@NotNull @Valid ScanPlay scanPlay);

    /**
    * 更新
    * @param scanPlay
    */
    void updateScanPlay(@NotNull @Valid ScanPlay scanPlay);

    /**
    * 删除
    * @param id
    */
    void deleteScanPlay(@NotNull String id);

    /**
     * 条件删除扫描结果
     * @param  key  删除条件字段
     * @param value
     */
    void deleteScanPlayByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    ScanPlay findOne(@NotNull String id);

    @FindList
    List<ScanPlay> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    ScanPlay findScanPlay(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ScanPlay> findAllScanPlay();

    /**
    * 查询列表
    * @param scanPlayQuery
    * @return
    */
    List<ScanPlay> findScanPlayList(ScanPlayQuery scanPlayQuery);

    /**
    * 按分页查询
    * @param scanPlayQuery
    * @return
    */
    Pagination<ScanPlay> findScanPlayPage(ScanPlayQuery scanPlayQuery);

}