package io.tiklab.sourcefare.project.service;

import io.tiklab.core.context.AppHomeContext;
import io.tiklab.sourcefare.project.service.PathSetService;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;

import java.io.File;

@Service
public class PathSetServiceImpl implements PathSetService {

    @Value("${spotbugs.address:null}")
    private static String spotbugsAddress;

    @Value("${DATA_HOME}")
    private  String DATA_HOME;

    @Override
    public  String spotbugsAddress() {
        String appHome = AppHomeContext.getAppHome();
        String path;
        if ("null".equals(spotbugsAddress)){
            path = new File(appHome).getParentFile().getParent()+"/embbed/spotbugs-4.8.1/bin";
        }else {
            path = appHome + spotbugsAddress;
        }
        return  path;
    }


    /**
     * 拉取扫描的代码的地址
     */
    @Override
    public  String codePath() {
        String path = DATA_HOME + "/scan/repository";
        File file = new File(path);
        if (!file.exists()){
            file.mkdirs();
        }
        return  path;
    }
}

