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

}
