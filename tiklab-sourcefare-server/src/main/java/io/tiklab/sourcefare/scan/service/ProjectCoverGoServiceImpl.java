package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.dao.ProjectCoverGoDao;
import io.tiklab.sourcefare.scan.entity.ProjectCoverGoEntity;
import io.tiklab.sourcefare.scan.model.ProjectCoverGo;
import io.tiklab.sourcefare.scan.model.ProjectCoverGoQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
* ProjectCoverGoServiceImpl-go项目覆盖率
*/
@Service
@Exporter
public class ProjectCoverGoServiceImpl implements ProjectCoverGoService {

    @Autowired
    ProjectCoverGoDao ProjectCoverGoDao;

    @Autowired
    JoinTemplate joinTemplate;


    @Autowired
    PathSetService pathSetService;

    @Override
    public String createProjectCoverGo(ProjectCoverGo projectCoverGo) {

        ProjectCoverGoEntity projectCoverGoEntity = BeanMapper.map(projectCoverGo, ProjectCoverGoEntity.class);
        projectCoverGoEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String projectCoverGoId= ProjectCoverGoDao.createProjectCoverGo(projectCoverGoEntity);

        return projectCoverGoId;
    }

    @Override
    public void updateProjectCoverGo(@NotNull @Valid ProjectCoverGo projectCoverGo) {
        ProjectCoverGoEntity projectCoverGoEntity = BeanMapper.map(projectCoverGo, ProjectCoverGoEntity.class);

        ProjectCoverGoDao.updateProjectCoverGo(projectCoverGoEntity);
    }

    @Override
    public void deleteProjectCoverGo(@NotNull String id) {
        ProjectCoverGoDao.deleteProjectCoverGo(id);
    }

    @Override
    public void deleteProjectCoverGoByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ProjectCoverGoEntity.class)
                .eq(key,value)
                .get();
        ProjectCoverGoDao.deleteProjectCoverGo(deleteCondition);
    }




    @Override
    public ProjectCoverGo findOne(String id) {
        ProjectCoverGoEntity projectCoverGoEntity = ProjectCoverGoDao.findProjectCoverGo(id);

        ProjectCoverGo projectCoverGo = BeanMapper.map(projectCoverGoEntity, ProjectCoverGo.class);
        return projectCoverGo;
    }

    @Override
    public List<ProjectCoverGo> findList(List<String> idList) {
        List<ProjectCoverGoEntity> projectCoverGoEntityList =  ProjectCoverGoDao.findProjectCoverGoList(idList);

        List<ProjectCoverGo> projectCoverGoList =  BeanMapper.mapList(projectCoverGoEntityList, ProjectCoverGo.class);
        return projectCoverGoList;
    }

    @Override
    public ProjectCoverGo findProjectCoverGo(@NotNull String id) {
        ProjectCoverGo projectCoverGo = findOne(id);

        joinTemplate.joinQuery(projectCoverGo);

        return projectCoverGo;
    }

    @Override
    public List<ProjectCoverGo> findAllProjectCoverGo() {
        List<ProjectCoverGoEntity> projectCoverGoEntityList =  ProjectCoverGoDao.findAllProjectCoverGo();

        List<ProjectCoverGo> projectCoverGoList =  BeanMapper.mapList(projectCoverGoEntityList, ProjectCoverGo.class);

        joinTemplate.joinQuery(projectCoverGoList);

        return projectCoverGoList;
    }

    @Override
    public List<ProjectCoverGo> findProjectCoverGoList(ProjectCoverGoQuery ProjectCoverGoQuery) {
        List<ProjectCoverGoEntity> projectCoverGoEntityList = ProjectCoverGoDao.findProjectCoverGoList(ProjectCoverGoQuery);

        List<ProjectCoverGo> projectCoverGoList = BeanMapper.mapList(projectCoverGoEntityList, ProjectCoverGo.class);
        joinTemplate.joinQuery(projectCoverGoList);
        if (CollectionUtils.isNotEmpty(projectCoverGoList)){
            projectCoverGoList = projectCoverGoList.stream().sorted(Comparator.comparing(ProjectCoverGo::getCreateTime).reversed()).collect(Collectors.toList());
        }

        return projectCoverGoList;
    }

    @Override
    public Pagination<ProjectCoverGo> findProjectCoverGoPage(ProjectCoverGoQuery ProjectCoverGoQuery) {

        Pagination<ProjectCoverGoEntity>  pagination = ProjectCoverGoDao.findProjectCoverGoPage(ProjectCoverGoQuery);

        List<ProjectCoverGo> projectCoverGoList = BeanMapper.mapList(pagination.getDataList(), ProjectCoverGo.class);
        joinTemplate.joinQuery(projectCoverGoList);


        return PaginationBuilder.build(pagination,projectCoverGoList);
    }



}