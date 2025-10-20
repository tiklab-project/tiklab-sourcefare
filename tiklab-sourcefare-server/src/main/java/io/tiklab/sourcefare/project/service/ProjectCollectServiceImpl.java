package io.tiklab.sourcefare.project.service;

import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.dao.ProjectCollectDao;
import io.tiklab.sourcefare.project.entity.ProjectCollectEntity;
import io.tiklab.sourcefare.project.entity.ProjectEnvEntity;
import io.tiklab.sourcefare.project.model.ProjectCollect;
import io.tiklab.sourcefare.project.model.ProjectCollectQuery;
import io.tiklab.sourcefare.scan.model.DeployEnv;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;

/**
* ProjectCollectServiceImpl-项目收藏信息
*/
@Service
@Exporter
public class ProjectCollectServiceImpl implements ProjectCollectService {

    @Autowired
    ProjectCollectDao projectCollectDao;


    @Autowired
    JoinTemplate joinTemplate;



    @Override
    public String createProjectCollect(@NotNull @Valid ProjectCollect projectCollect) {


        ProjectCollectEntity projectCollectEntity = BeanMapper.map(projectCollect, ProjectCollectEntity.class);

        projectCollectEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String repositoryRep = projectCollectDao.createProjectCollect(projectCollectEntity);


        return repositoryRep;
    }

  
    @Override
    public void updateProjectCollect(@NotNull @Valid ProjectCollect projectCollect) {
        ProjectCollectEntity projectCollectEntity = BeanMapper.map(projectCollect, ProjectCollectEntity.class);

        projectCollectDao.updateProjectCollect(projectCollectEntity);
    }

    @Override
    public void deleteProjectCollect(@NotNull String id) {
        projectCollectDao.deleteProjectCollect(id);
    }

    @Override
    public void deleteCollect(String projectId, String userId) {
        projectCollectDao.deleteCollect(projectId,userId);
    }

    @Override
    public void deleteProjectCollectByRecord(String type,String data) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ProjectCollectEntity.class)
                .eq(type, data)
                .get();
        projectCollectDao.deleteProjectCollect(deleteCondition);
    }

    @Override
    public ProjectCollect findOne(String id) {
        ProjectCollectEntity projectCollectEntity = projectCollectDao.findProjectCollect(id);

        ProjectCollect projectCollect = BeanMapper.map(projectCollectEntity, ProjectCollect.class);
        return projectCollect;
    }

    @Override
    public List<ProjectCollect> findList(List<String> idList) {
        List<ProjectCollectEntity> projectCollectEntityList =  projectCollectDao.findProjectCollectList(idList);

        List<ProjectCollect> projectCollectList =  BeanMapper.mapList(projectCollectEntityList, ProjectCollect.class);
        return projectCollectList;
    }

    @Override
    public ProjectCollect findProjectCollect(@NotNull String id) {
        ProjectCollect projectCollect = findOne(id);

        joinTemplate.joinQuery(projectCollect,new String[]{"user"});

        return projectCollect;
    }

    @Override
    public List<ProjectCollect> findRepositoryCollectList(String[] projectIds, String userId) {
        List<ProjectCollectEntity> collectList = projectCollectDao.findProjectCollectList(projectIds, userId);
        List<ProjectCollect> projectCollectList = BeanMapper.mapList(collectList, ProjectCollect.class);

        return projectCollectList;
    }

    @Override
    public List<ProjectCollect> findAllProjectCollect() {
        List<ProjectCollectEntity> projectCollectEntityList =  projectCollectDao.findAllProjectCollect();

        List<ProjectCollect> projectCollectList =  BeanMapper.mapList(projectCollectEntityList, ProjectCollect.class);

        joinTemplate.joinQuery(projectCollectList,new String[]{"user"});


        return projectCollectList;
    }

    @Override
    public List<ProjectCollect> findProjectCollectList(ProjectCollectQuery ProjectCollectQuery) {
        List<ProjectCollectEntity> projectCollectEntityList = projectCollectDao.findProjectCollectList(ProjectCollectQuery);

        List<ProjectCollect> projectCollectList = BeanMapper.mapList(projectCollectEntityList, ProjectCollect.class);

        joinTemplate.joinQuery(projectCollectList,new String[]{"user"});

        return projectCollectList;
    }

}