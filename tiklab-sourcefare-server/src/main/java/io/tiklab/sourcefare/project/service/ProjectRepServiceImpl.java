package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.dao.ProjectRepDao;
import io.tiklab.sourcefare.project.entity.ProjectRepEntity;
import io.tiklab.sourcefare.project.model.ProjectRep;
import io.tiklab.sourcefare.project.model.ProjectRepQuery;
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
* ProjectRepServiceImpl-代码仓库信息
*/
@Service
@Exporter
public class ProjectRepServiceImpl implements ProjectRepService {

    @Autowired
    ProjectRepDao projectRepDao;

    @Autowired
    private DmUserService dmUserService;

    @Autowired
    JoinTemplate joinTemplate;





    @Override
    public String createProjectRep(@NotNull @Valid ProjectRep projectRep) {


        ProjectRepEntity projectRepEntity = BeanMapper.map(projectRep, ProjectRepEntity.class);

        String repositoryRep = projectRepDao.createProjectRep(projectRepEntity);


        return repositoryRep;
    }

    @Override
    public void updateProjectRep(@NotNull @Valid ProjectRep projectRep) {
        ProjectRepEntity projectRepEntity = BeanMapper.map(projectRep, ProjectRepEntity.class);

        projectRepDao.updateProjectRep(projectRepEntity);
    }

    @Override
    public void deleteProjectRep(@NotNull String id) {
        projectRepDao.deleteProjectRep(id);
    }

    @Override
    public void deleteProjectRepByRecord(String type,String data) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ProjectRepEntity.class)
                .eq(type, data)
                .get();
        projectRepDao.deleteProjectRep(deleteCondition);
    }

    @Override
    public ProjectRep findOne(String id) {
        ProjectRepEntity projectRepEntity = projectRepDao.findProjectRep(id);

        ProjectRep projectRep = BeanMapper.map(projectRepEntity, ProjectRep.class);
        return projectRep;
    }

    @Override
    public List<ProjectRep> findList(List<String> idList) {
        List<ProjectRepEntity> projectRepEntityList =  projectRepDao.findProjectRepList(idList);

        List<ProjectRep> projectRepList =  BeanMapper.mapList(projectRepEntityList, ProjectRep.class);
        return projectRepList;
    }

    @Override
    public ProjectRep findProjectRep(@NotNull String id) {
        ProjectRep projectRep = findOne(id);

        joinTemplate.joinQuery(projectRep);

        return projectRep;
    }

    @Override
    public List<ProjectRep> findAllProjectRep() {
        List<ProjectRepEntity> projectRepEntityList =  projectRepDao.findAllProjectRep();

        List<ProjectRep> projectRepList =  BeanMapper.mapList(projectRepEntityList, ProjectRep.class);

        joinTemplate.joinQuery(projectRepList);

        return projectRepList;
    }

    @Override
    public List<ProjectRep> findProjectRepList(ProjectRepQuery ProjectRepQuery) {
        List<ProjectRepEntity> projectRepEntityList = projectRepDao.findProjectRepList(ProjectRepQuery);

        List<ProjectRep> projectRepList = BeanMapper.mapList(projectRepEntityList, ProjectRep.class);

        joinTemplate.joinQuery(projectRepList,new String[]{"repositoryServer"});

        return projectRepList;
    }

    @Override
    public Pagination<ProjectRep> findProjectRepPage(ProjectRepQuery ProjectRepQuery) {
        Pagination<ProjectRepEntity>  pagination = projectRepDao.findProjectRepPage(ProjectRepQuery);

        List<ProjectRep> projectRepList = BeanMapper.mapList(pagination.getDataList(), ProjectRep.class);
        joinTemplate.joinQuery(pagination.getDataList());

        return PaginationBuilder.build(pagination,projectRepList);
    }

    @Override
    public ProjectRep findProjectRepByProjectId(String projectId) {
        ProjectRepQuery projectRepQuery = new ProjectRepQuery();
        projectRepQuery.setProjectId(projectId);
        List<ProjectRep> repositoryRepList = this.findProjectRepList(projectRepQuery);
        if (CollectionUtils.isNotEmpty(repositoryRepList)){
            return repositoryRepList.get(0);
        }
        return null;
    }

}