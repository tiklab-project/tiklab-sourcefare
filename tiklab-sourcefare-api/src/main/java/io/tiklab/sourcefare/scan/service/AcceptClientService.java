package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.scan.model.ScanRecordLog;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.ServletInputStream;
import javax.servlet.http.HttpServletRequest;
import java.util.List;

public interface AcceptClientService {

    /**
     * 客户端开始执行扫描 初始化扫描记录
     * @param request request
     */
    List<ScanRecordLog> acceptMessage(HttpServletRequest request);





    /**
     * 接受客户端发送的代码
     * @param file 代码文件
     */
    void acceptScanCode(MultipartFile file);

}
