package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.eam.common.context.LoginContext;
import io.tiklab.privilege.dmRole.service.DmRoleService;
import io.tiklab.privilege.role.model.PatchUser;
import io.tiklab.privilege.role.model.RoleUser;
import io.tiklab.privilege.role.service.RoleUserService;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.common.FareMessageService;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.common.SourceWairServerFinal;
import io.tiklab.sourcefare.project.dao.ProjectDao;
import io.tiklab.sourcefare.project.entity.ProjectEntity;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.project.model.ProjectQuery;
import io.tiklab.sourcefare.scanner.common.SourceFareFinal;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.ObjectUtils;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.HashMap;
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

    @Autowired
    private DmRoleService dmRoleService;

    @Autowired
    RoleUserService roleUserService;

    @Autowired
    FareMessageService fareMessageService;



    @Override
    public String createProject(@NotNull @Valid Project project) {

        ProjectEntity projectEntity = BeanMapper.map(project, ProjectEntity.class);
        projectEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        // 生成0到4之间的随机数
        int randomNum = SourceFareUtil.getRandomNum(5);
        projectEntity.setColor(randomNum);

        String projectId= projectDao.createProject(projectEntity);
        projectEntity.setId(projectId);

        String userId;
        //初始化示例仓库用户id 取Repository里面用户
        if (!ObjectUtils.isEmpty(project.getUser())&& StringUtils.isNotEmpty(project.getUser().getId())){
            userId = project.getUser().getId();
        }else {
            userId = LoginContext.getLoginId();
        }
        List<PatchUser> List = new ArrayList<>();
        PatchUser patchUser = new PatchUser();
        RoleUser userRoleAdmin = roleUserService.findUserRoleAdmin();
        //给系统超级管理员设置成项目超级管理员
        patchUser.setUserId(userRoleAdmin.getUser().getId());
        patchUser.setRoleType(2);
        List.add(patchUser);

        //超级管理员和创建者不同 ，给创建者设置为管理员角色
        if (!(userId).equals(userRoleAdmin.getUser().getId())){
            PatchUser patchUser1 = new PatchUser();
            patchUser1.setUserId(userId);
            patchUser1.setRoleType(2);
            List.add(patchUser1);
        }
        dmRoleService.initPatchDmRole(projectId, List);

        //发送消息日志
        sendMessLog(projectEntity,"create",null);
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

    /**
     *操作仓库发送消息
     * @param project 操作的项目
     * @param type  操作类型
     * @param  updateName 更新名字
     */
    public void sendMessLog(ProjectEntity project,String type,String updateName){

        HashMap<String, Object> map = fareMessageService.initMessageAndLogMap();

        map.put("projectName", project.getProjectName());
        map.put("projectId",project.getId());
        map.put("action",project.getProjectName());

        //创建仓库发送消息和日志
        //map.put("repositoryPath",project.getAddress());
        if (("create").equals(type)){
            map.put("message", project.getProjectName());
            map.put("link", SourceWairServerFinal.LOG_RPY_CREATE);
            map.put("qywxurl",SourceWairServerFinal.LOG_RPY_CREATE);
            fareMessageService.deployMessage(map, SourceWairServerFinal.LOG_TYPE_CREATE);
            fareMessageService.deployLog(map, SourceWairServerFinal.LOG_TYPE_CREATE,"project");
        }
    }

}