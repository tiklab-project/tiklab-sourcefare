package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.dao.ProjectCoverDao;
import io.tiklab.sourcefare.scan.dao.ProjectCoverGoDao;
import io.tiklab.sourcefare.scan.entity.ProjectCoverEntity;
import io.tiklab.sourcefare.scan.model.ProjectCover;
import io.tiklab.sourcefare.scan.model.ProjectCoverGo;
import io.tiklab.sourcefare.scan.model.ProjectCoverGoQuery;
import io.tiklab.sourcefare.scan.model.ProjectCoverQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.io.File;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
* ProjectCoverServiceImpl-项目覆盖率
*/
@Service
@Exporter
public class ProjectCoverServiceImpl implements ProjectCoverService {

    @Autowired
    ProjectCoverDao ProjectCoverDao;

    @Autowired
    ProjectCoverGoDao projectCoverGoDao;

    @Autowired
    JoinTemplate joinTemplate;


    @Autowired
    PathSetService pathSetService;

    @Override
    public String createProjectCover(ProjectCover projectCover) {

        ProjectCoverEntity projectCoverEntity = BeanMapper.map(projectCover, ProjectCoverEntity.class);
        projectCoverEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String projectCoverId= ProjectCoverDao.createProjectCover(projectCoverEntity);

        return projectCoverId;
    }

    @Override
    public void updateProjectCover(@NotNull @Valid ProjectCover projectCover) {
        ProjectCoverEntity projectCoverEntity = BeanMapper.map(projectCover, ProjectCoverEntity.class);

        ProjectCoverDao.updateProjectCover(projectCoverEntity);
    }

    @Override
    public void deleteProjectCover(@NotNull String id) {
        ProjectCoverDao.deleteProjectCover(id);
    }

    @Override
    public void deleteProjectCoverByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ProjectCoverEntity.class)
                .eq(key,value)
                .get();
        ProjectCoverDao.deleteProjectCover(deleteCondition);
    }




    @Override
    public ProjectCover findOne(String id) {
        ProjectCoverEntity projectCoverEntity = ProjectCoverDao.findProjectCover(id);

        ProjectCover projectCover = BeanMapper.map(projectCoverEntity, ProjectCover.class);
        return projectCover;
    }

    @Override
    public List<ProjectCover> findList(List<String> idList) {
        List<ProjectCoverEntity> projectCoverEntityList =  ProjectCoverDao.findProjectCoverList(idList);

        List<ProjectCover> projectCoverList =  BeanMapper.mapList(projectCoverEntityList, ProjectCover.class);
        return projectCoverList;
    }

    @Override
    public ProjectCover findProjectCover(@NotNull String id) {
        ProjectCover projectCover = findOne(id);

        joinTemplate.joinQuery(projectCover);

        return projectCover;
    }

    @Override
    public List<ProjectCover> findAllProjectCover() {
        List<ProjectCoverEntity> projectCoverEntityList =  ProjectCoverDao.findAllProjectCover();

        List<ProjectCover> projectCoverList =  BeanMapper.mapList(projectCoverEntityList, ProjectCover.class);

        joinTemplate.joinQuery(projectCoverList);

        return projectCoverList;
    }

    @Override
    public List<ProjectCover> findProjectCoverList(ProjectCoverQuery ProjectCoverQuery) {
        List<ProjectCoverEntity> projectCoverEntityList = ProjectCoverDao.findProjectCoverList(ProjectCoverQuery);

        List<ProjectCover> projectCoverList = BeanMapper.mapList(projectCoverEntityList, ProjectCover.class);
        joinTemplate.joinQuery(projectCoverList);
        if (CollectionUtils.isNotEmpty(projectCoverList)){
            projectCoverList = projectCoverList.stream().sorted(Comparator.comparing(ProjectCover::getCreateTime).reversed()).collect(Collectors.toList());
        }

        return projectCoverList;
    }

    @Override
    public Pagination<ProjectCover> findProjectCoverPage(ProjectCoverQuery ProjectCoverQuery) {
        Pagination<ProjectCoverEntity>  pagination = ProjectCoverDao.findProjectCoverPage(ProjectCoverQuery);
        List<ProjectCover> projectCoverList = BeanMapper.mapList(pagination.getDataList(), ProjectCover.class);
        joinTemplate.joinQuery(projectCoverList);
        return PaginationBuilder.build(pagination,projectCoverList);
    }

}