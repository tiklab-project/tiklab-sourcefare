package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.scan.model.ScanResult;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.ServletInputStream;

public interface AcceptClientService {


    void acceptClient(ScanResult scanResult);

    void acceptScanCode(MultipartFile file);
}
