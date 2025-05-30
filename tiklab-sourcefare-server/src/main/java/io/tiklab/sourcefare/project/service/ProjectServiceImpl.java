package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.dao.ProjectDao;
import io.tiklab.sourcefare.project.entity.ProjectEntity;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.project.model.ProjectQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;

/**
* ProjectServiceImpl 项目
*/
@Service
@Exporter
public class ProjectServiceImpl implements ProjectService {
    private static Logger logger = LoggerFactory.getLogger(ProjectServiceImpl.class);

    @Autowired
    ProjectDao projectDao;
    

    @Autowired
    JoinTemplate joinTemplate;


    @Override
    public String createProject(@NotNull @Valid Project project) {

        ProjectEntity projectEntity = BeanMapper.map(project, ProjectEntity.class);
        projectEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));

        String projectId= projectDao.createProject(projectEntity);
        return projectId;
    }

    @Override
    public void updateProject(@NotNull @Valid Project project) {
        ProjectEntity projectEntity = BeanMapper.map(project, ProjectEntity.class);

        projectDao.updateProject(projectEntity);
    }

    @Override
    public void deleteProject(@NotNull String id) {
        projectDao.deleteProject(id);
    }


    @Override
    public Project findOne(String id) {
        ProjectEntity projectEntity = projectDao.findProject(id);

        Project project = BeanMapper.map(projectEntity, Project.class);

        return project;
    }

    @Override
    public Project findProject(@NotNull String id) {
        Project repository = findOne(id);

        joinTemplate.joinQuery(repository);

        return repository;
    }

    @Override
    public List<Project> findList(List<String> idList) {
        List<ProjectEntity> projectEntityList =  projectDao.findProjectList(idList);

        List<Project> projectList =  BeanMapper.mapList(projectEntityList,Project.class);

        return projectList;
    }

    @Override
    public List<Project> findAllProject() {
        List<ProjectEntity> projectEntityList =  projectDao.findAllProject();

        List<Project> projectList =  BeanMapper.mapList(projectEntityList, Project.class);

        joinTemplate.joinQuery(projectList);


        return projectList;
    }


    @Override
    public Pagination<Project> findProjectPage(ProjectQuery projectQuery) {
        Pagination<ProjectEntity> projectPage = projectDao.findProjectPage(projectQuery);

        List<Project> openRecordList = BeanMapper.mapList(projectPage.getDataList(), Project.class);

        joinTemplate.joinQuery(openRecordList);

        return PaginationBuilder.build(projectPage,openRecordList);
    }

    @Override
    public List<Project> findProjectList(ProjectQuery projectQuery) {
        List<ProjectEntity> projectEntityList= projectDao.findProjectList(projectQuery);

        List<Project> projectList = BeanMapper.mapList(projectEntityList, Project.class);

        joinTemplate.joinQuery(projectList);

        return projectList;
    }


}