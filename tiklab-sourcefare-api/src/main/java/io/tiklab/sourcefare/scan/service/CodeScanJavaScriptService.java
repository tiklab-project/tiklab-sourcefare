package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.scan.model.ScanPlay;

public interface CodeScanJavaScriptService {

    /**
     * 扫描JavaScript的代码
     * @param scanPlay 扫描计划
     */
    void codeScan( ScanPlay scanPlay);
}
