package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.ScanDoor;
import io.tiklab.sourcefare.scan.model.ScanDoorQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ScanDoorService-扫描门禁
*/
@JoinProvider(model = ScanDoor.class)
public interface ScanDoorService {

    /**
    * 创建
    * @param scanDoor
    * @return
    */
    String createScanDoor(@NotNull @Valid ScanDoor scanDoor);


    /**
    * 更新
    * @param scanDoor
    */
    void updateScanDoor(@NotNull @Valid ScanDoor scanDoor);

    /**
    * 删除
    * @param id
    */
    void deleteScanDoor(@NotNull String id);

    /**
     * 条件删除扫描结果
     * @param  key  删除条件字段
     * @param value
     */
    void deleteScanDoorByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    ScanDoor findOne(@NotNull String id);

    @FindList
    List<ScanDoor> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    ScanDoor findScanDoor(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<ScanDoor> findAllScanDoor();

    /**
    * 查询列表
    * @param scanDoorQuery
    * @return
    */
    List<ScanDoor> findScanDoorList(ScanDoorQuery scanDoorQuery);

    /**
     * 通过项目ID 查询扫描门禁
     * @param projectId 项目id
     */
    ScanDoor findScanDoorByProjectId(String projectId);
}