package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.exception.ApplicationException;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.model.ScanResult;

import javax.servlet.http.HttpServletRequest;
import java.util.Map;


public interface CodeScanService {

    /**
     * 代码扫描
     * @param projectId
     * @return 执行状态 true:成功 false:失败
     * @throws ApplicationException 运行失败
     */
    ScanRecord codeScanExec(String  projectId);




    /**
     * 接受客户端扫描的结果
     * @param request request
     */
    void  acceptScanResult(HttpServletRequest request);

    /**
     * 查询扫描日志
     * @param recordId recordId
     */
    Map<String,Object> findScanState(String project,String recordId);
}
