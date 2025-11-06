package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.exception.ApplicationException;
import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.scan.dao.DeployEnvDao;
import io.tiklab.sourcefare.scan.entity.DeployEnvEntity;
import io.tiklab.sourcefare.scan.model.DeployEnv;
import io.tiklab.sourcefare.scan.model.DeployEnvQuery;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.Timestamp;
import java.util.Date;
import java.util.List;

import static io.tiklab.sourcefare.scanner.common.SourceFareFinal.SCAN_TYPE_PYTHON;
import static io.tiklab.sourcefare.scanner.common.SourceFareFinal.SCAN_TYPE_PYTHON3;

/**
* DeployEnvServiceImpl-部署环境的记录接口实现
*/
@Service
@Exporter
public class DeployEnvServiceImpl implements DeployEnvService {

    @Autowired
    DeployEnvDao deployEnvDao;


    @Autowired
    JoinTemplate joinTemplate;


    @Override
    public String createDeployEnv(@NotNull @Valid DeployEnv deployEnv) {

        DeployEnvEntity deployEnvEntity = BeanMapper.map(deployEnv, DeployEnvEntity.class);
        deployEnvEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));

        if (deployEnv.getInstallWay()!=0){
            SourceFareUtil.validFile(deployEnv);
        }

        String deployEnvId= deployEnvDao.createDeployEnv(deployEnvEntity);

        return deployEnvId;
    }

    @Override
    public void updateDeployEnv(@NotNull @Valid DeployEnv deployEnv) {
        DeployEnvEntity deployEnvEntity = BeanMapper.map(deployEnv, DeployEnvEntity.class);

        SourceFareUtil.validFile(deployEnv);
        deployEnvDao.updateDeployEnv(deployEnvEntity);
    }

    @Override
    public void deleteDeployEnv(@NotNull String id) {
        deployEnvDao.deleteDeployEnv(id);
    }

    @Override
    public void deleteDeployEnvByRecord(String repositoryId) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(DeployEnvEntity.class)
                .eq("repositoryId", repositoryId)
                .get();
        deployEnvDao.deleteDeployEnv(deleteCondition);
    }

    @Override
    public DeployEnv findOne(String id) {
        DeployEnvEntity deployEnvEntity = deployEnvDao.findDeployEnv(id);

        DeployEnv deployEnv = BeanMapper.map(deployEnvEntity, DeployEnv.class);
        return deployEnv;
    }

    @Override
    public List<DeployEnv> findList(List<String> idList) {
        List<DeployEnvEntity> deployEnvEntityList =  deployEnvDao.findDeployEnvList(idList);

        List<DeployEnv> deployEnvList =  BeanMapper.mapList(deployEnvEntityList, DeployEnv.class);
        return deployEnvList;
    }

    @Override
    public DeployEnv findDeployEnv(@NotNull String id) {
        DeployEnv deployEnv = findOne(id);

        joinTemplate.joinQuery(deployEnv);

        return deployEnv;
    }

    @Override
    public List<DeployEnv> findAllDeployEnv() {
        List<DeployEnvEntity> deployEnvEntityList =  deployEnvDao.findAllDeployEnv();

        List<DeployEnv> deployEnvList =  BeanMapper.mapList(deployEnvEntityList, DeployEnv.class);

        joinTemplate.joinQuery(deployEnvList);

        return deployEnvList;
    }

    @Override
    public List<DeployEnv> findDeployEnvList(DeployEnvQuery DeployEnvQuery) {
        List<DeployEnvEntity> deployEnvEntityList = deployEnvDao.findDeployEnvList(DeployEnvQuery);

        List<DeployEnv> deployEnvList = BeanMapper.mapList(deployEnvEntityList, DeployEnv.class);



        joinTemplate.joinQuery(deployEnvList);

        return deployEnvList;
    }

    @Override
    public Pagination<DeployEnv> findDeployEnvPage(DeployEnvQuery DeployEnvQuery) {
        Pagination<DeployEnvEntity>  pagination = deployEnvDao.findDeployEnvPage(DeployEnvQuery);

        List<DeployEnv> deployEnvList = BeanMapper.mapList(pagination.getDataList(), DeployEnv.class);
        joinTemplate.joinQuery(pagination.getDataList());

        return PaginationBuilder.build(pagination,deployEnvList);
    }

    @Override
    public String detectionEnv(String type) {
        switch (type) {
            case "net" ->{
                return  detectDotnet();
            }
        }
        String envVersion = ProjectUtil.getEnvPath(type);
        if (StringUtils.isBlank(envVersion)){
            throw new ApplicationException("全局路径不存在");
        }


        if (type.equals(SCAN_TYPE_PYTHON)&&(envVersion.contains("not found")||envVersion.contains("no python"))){
            envVersion= ProjectUtil.getEnvPath(SCAN_TYPE_PYTHON3);
        }
        if (envVersion.contains("not found")||envVersion.contains("no python")){
            throw new ApplicationException("未查询到全局的"+type);
        }
        envVersion=StringUtils.substringBeforeLast(envVersion,"/");
        return envVersion;
    }

    private static String detectDotnet() {
        try {
            ProcessBuilder builder = new ProcessBuilder("dotnet", "--version");
            builder.redirectErrorStream(true);
            Process process = builder.start();
            try (BufferedReader reader = new BufferedReader(
                    new InputStreamReader(process.getInputStream()))) {
                String line = reader.readLine();
                if (line != null && line.matches("\\d+\\.\\d+(\\.\\d+)?")) {
                    String version = line.trim();
                    String dotnet = SourceFareUtil.getCommandPath("dotnet");
                    return dotnet;
                }
            }
        }catch (IOException ignored){}
        return "false";
    }

}