package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.dao.ProjectEnvDao;
import io.tiklab.sourcefare.project.entity.ProjectEnvEntity;
import io.tiklab.sourcefare.project.model.ProjectEnv;
import io.tiklab.sourcefare.project.model.ProjectEnvQuery;
import io.tiklab.sourcefare.scan.model.DeployEnv;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import io.tiklab.user.dmUser.service.DmUserService;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* ProjectEnvServiceImpl-项目环境关联信息
*/
@Service
@Exporter
public class ProjectEnvServiceImpl implements ProjectEnvService {

    @Autowired
    ProjectEnvDao projectEnvDao;


    @Autowired
    JoinTemplate joinTemplate;





    @Override
    public String createProjectEnv(@NotNull @Valid ProjectEnv projectEnv) {


        ProjectEnvEntity projectEnvEntity = BeanMapper.map(projectEnv, ProjectEnvEntity.class);

        String repositoryRep = projectEnvDao.createProjectEnv(projectEnvEntity);


        return repositoryRep;
    }

    @Override
    public String createProjectEnv(String projectId, String envId,String type) {
        ProjectEnv projectEnv = new ProjectEnv();
        projectEnv.setProjectId(projectId);
        projectEnv.setType(type);
        DeployEnv deployEnv = new DeployEnv();
        deployEnv.setId(envId);
        projectEnv.setDeployEnv(deployEnv);
        String projectEnvId = this.createProjectEnv(projectEnv);
        return projectEnvId;
    }

    @Override
    public void updateProjectEnv(@NotNull @Valid ProjectEnv projectEnv) {
        ProjectEnvEntity projectEnvEntity = BeanMapper.map(projectEnv, ProjectEnvEntity.class);

        projectEnvDao.updateProjectEnv(projectEnvEntity);
    }

    @Override
    public void deleteProjectEnv(@NotNull String id) {
        projectEnvDao.deleteProjectEnv(id);
    }

    @Override
    public void deleteProjectEnvByRecord(String type,String data) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ProjectEnvEntity.class)
                .eq(type, data)
                .get();
        projectEnvDao.deleteProjectEnv(deleteCondition);
    }

    @Override
    public ProjectEnv findOne(String id) {
        ProjectEnvEntity projectEnvEntity = projectEnvDao.findProjectEnv(id);

        ProjectEnv projectEnv = BeanMapper.map(projectEnvEntity, ProjectEnv.class);
        return projectEnv;
    }

    @Override
    public List<ProjectEnv> findList(List<String> idList) {
        List<ProjectEnvEntity> projectEnvEntityList =  projectEnvDao.findProjectEnvList(idList);

        List<ProjectEnv> projectEnvList =  BeanMapper.mapList(projectEnvEntityList, ProjectEnv.class);
        return projectEnvList;
    }

    @Override
    public ProjectEnv findProjectEnv(@NotNull String id) {
        ProjectEnv projectEnv = findOne(id);

        joinTemplate.joinQuery(projectEnv,new String[]{"deployEnv"});

        return projectEnv;
    }

    @Override
    public List<ProjectEnv> findAllProjectEnv() {
        List<ProjectEnvEntity> projectEnvEntityList =  projectEnvDao.findAllProjectEnv();

        List<ProjectEnv> projectEnvList =  BeanMapper.mapList(projectEnvEntityList, ProjectEnv.class);

        joinTemplate.joinQuery(projectEnvList,new String[]{"deployEnv"});


        return projectEnvList;
    }

    @Override
    public List<ProjectEnv> findProjectEnvList(ProjectEnvQuery ProjectEnvQuery) {
        List<ProjectEnvEntity> projectEnvEntityList = projectEnvDao.findProjectEnvList(ProjectEnvQuery);

        List<ProjectEnv> projectEnvList = BeanMapper.mapList(projectEnvEntityList, ProjectEnv.class);

        joinTemplate.joinQuery(projectEnvList,new String[]{"deployEnv"});

        return projectEnvList;
    }

}