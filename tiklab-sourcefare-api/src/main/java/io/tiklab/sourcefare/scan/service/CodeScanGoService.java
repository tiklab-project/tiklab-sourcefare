package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.scan.model.ScanPlay;

/*
* go语言扫描 service
* */
public interface CodeScanGoService {

    /**
     * 扫描JavaScript的代码
     * @param scanPlay 扫描计划
     */
    void codeScan( ScanPlay scanPlay);
}
