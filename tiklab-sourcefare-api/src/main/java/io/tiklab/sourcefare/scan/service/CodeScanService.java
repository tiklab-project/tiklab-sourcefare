package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.exception.ApplicationException;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.model.ScanResult;


public interface CodeScanService {

    /**
     * 代码扫描
     * @param scanPlayId
     * @return 执行状态 true:成功 false:失败
     * @throws ApplicationException 运行失败
     */
    String codeScanExec(String  scanPlayId);



    /**
     * 查询代码扫描状态
     * @param scanPlayId 扫描计划
     * @param scanWay 扫描方式  rule、sonar
     * @return 执行状态 true:成功 false:失败
     * @throws ApplicationException 运行失败
     */
    ScanRecord findScanState(String scanPlayId, String scanWay);




}
