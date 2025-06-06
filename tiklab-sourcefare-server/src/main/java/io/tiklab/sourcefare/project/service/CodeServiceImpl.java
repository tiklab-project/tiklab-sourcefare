package io.tiklab.sourcefare.project.service;

import io.tiklab.core.exception.SystemException;
import org.apache.commons.io.FileUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.io.File;
import java.io.IOException;
import java.nio.file.Path;
import java.nio.file.Paths;

@Service
public class CodeServiceImpl implements CodeService {

    @Autowired
    PathSetService pathSetService;


    @Override
    public String findCodeData(String filePath) {
        //代码文件的详细位置
        String path = pathSetService.codePath()+"/"+filePath;
        File file = new File(path);
        if (!file.exists()){
            throw new SystemException(5000,"文件不存在");
        }

        try {
            String s = FileUtils.readFileToString(new File(path));
            return s;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}
