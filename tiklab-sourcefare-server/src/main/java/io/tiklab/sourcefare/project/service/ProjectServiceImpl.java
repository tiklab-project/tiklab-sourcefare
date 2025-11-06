package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.eam.common.context.LoginContext;
import io.tiklab.privilege.dmRole.service.DmRoleService;
import io.tiklab.privilege.permission.service.PermissionService;
import io.tiklab.privilege.role.model.PatchUser;
import io.tiklab.privilege.role.model.RoleUser;
import io.tiklab.privilege.role.service.RoleUserService;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.common.FareMessageService;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.common.SourceFareServerFinal;
import io.tiklab.sourcefare.project.dao.ProjectDao;
import io.tiklab.sourcefare.project.entity.ProjectEntity;
import io.tiklab.sourcefare.project.model.*;
import io.tiklab.sourcefare.scan.model.ScanDoor;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.service.*;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import io.tiklab.user.dmUser.model.DmUser;
import io.tiklab.user.dmUser.model.DmUserQuery;
import io.tiklab.user.dmUser.service.DmUserService;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;
import org.springframework.util.ObjectUtils;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.io.File;
import java.io.IOException;
import java.sql.Timestamp;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import static io.tiklab.sourcefare.common.SourceFareServerFinal.PROJECT_DELETE;
import static io.tiklab.sourcefare.common.SourceFareServerFinal.PROJECT_UPDATE;

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

    @Autowired
    ProjectRepService projectRepService;

    @Autowired
    ProjectRepUploadService projectRepUploadService;

    @Autowired
    PermissionService permissionService;

    @Autowired
    ProjectEnvService projectEnvService;

    @Autowired
    ProjectCollectService projectCollectService;

    @Autowired
    RecordOpenService recordOpenService;

    @Autowired
    DmUserService dmUserService;


    @Autowired
    ScanDoorService scanDoorService;

    @Autowired
    PathSetService pathSetService;

    @Autowired
    IssueStatisticService issueStatisticService;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    RecordComplexityService complexityService;

    @Autowired
    RecordDuplicatedService duplicatedService;

    @Autowired
    RecordInstanceService instanceService;

    @Autowired
    RecordInstanceCondService instanceCondService;

    @Autowired
    ProjectCoverService projectCoverService;

    @Autowired
    ScanRecordLogService recordLogService;


    @Override
    public String createProject(@NotNull @Valid Project project) {

        ProjectEntity projectEntity = BeanMapper.map(project, ProjectEntity.class);
        projectEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        // 生成0到4之间的随机数
        int randomNum = SourceFareUtil.getRandomNum(5);
        projectEntity.setColor(randomNum);

        String projectId= projectDao.createProject(projectEntity);
        projectEntity.setId(projectId);

        //创建服务端扫描
        if (("server").equals(project.getScanWay())){
            ProjectRep projectRep = new ProjectRep();
            projectRep.setProjectId(projectId);
            projectRep.setRepositoryAddress(project.getRepositoryAddress());
            projectRep.setRepositoryName(project.getRepositoryName());
            projectRep.setBranch(project.getBranch());
            projectRep.setRepositoryCode(project.getRepositoryCode());
            projectRep.setRepositoryServer(new RepositoryServer().setId(project.getRepositoryServerId()));
            projectRepService.createProjectRep(projectRep);
        }

        //创建扫描环境
        if (StringUtils.isNotBlank(project.getExcEnv())){
            projectEnvService.createProjectEnv(projectId,project.getExcEnv(),"exec");
        }

        //创建jdk
        if (StringUtils.isNotBlank(project.getJdkEnv())){
            projectEnvService.createProjectEnv(projectId,project.getJdkEnv(),"jdk");
        }

        //创建python
        if (StringUtils.isNotBlank(project.getPython())){
            projectEnvService.createProjectEnv(projectId,project.getPython(),"python");
        }

        //创建默认的扫描门禁
        ScanDoor aDefault = scanDoorService.findScanDoor("default");
        aDefault.setProjectId(projectId);
        scanDoorService.createScanDoor(aDefault);


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

        if (!("demo").equals(project.getCategory())){
            //发送消息日志
            sendMessLog(projectEntity,"create",null);
        }

        return projectId;
    }

    @Override
    public void updateProject(@NotNull @Valid Project project) {
        project.setUpdateTime(new Timestamp(System.currentTimeMillis()));
        ProjectEntity projectEntity = BeanMapper.map(project, ProjectEntity.class);

        projectDao.updateProject(projectEntity);
    }

    @Override
    public void deleteProject(@NotNull String id) {
        projectDao.deleteProject(id);

        //删除项目的仓库信息
        projectRepService.deleteProjectRepByRecord("projectId",id);

        //删除项目上传代码信息
        projectRepUploadService.deleteProjectRepUploadByRecord("projectId",id);

        //删除项目的环境
        projectEnvService.deleteProjectEnvByRecord("projectId",id);

        //删除项目收藏信息
        projectCollectService.deleteProjectCollectByRecord("projectId",id);

        //删除打开记录
        recordOpenService.deleteRecordOpenByRecord(id);

        //删除问题
        issueStatisticService.deleteIssueStatisticByCondition("projectId",id);

        //删除扫描记录
        scanRecordService.deleteScanRecordByCondition("projectId",id);

        //删除复杂度
        complexityService.deleteRecordComplexityByCondition("projectId",id);

        //删除重复率
        duplicatedService.deleteRecordDuplicatedByCondition("projectId",id);

        //删除问题实例
        instanceService.deleteScanRecordInstanceByCondition("projectId",id);

        //删除问题实例
        instanceCondService.deleteRecordInstanceCondByCondition("projectId",id);

        //删除覆盖率
        projectCoverService.deleteProjectCoverByCondition("projectId",id);


        //删除日志
        recordLogService.deleteScanRecordLogByCondition("projectId",id);
        Thread thread = new Thread() {
            public void run() {
                //删除项目的代码
                String projectPath = pathSetService.codePath()+"/"+id;
                try {
                    FileUtils.deleteDirectory(new File(projectPath));
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }

            }};
        thread.start();
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

        joinTemplate.joinQuery(repository,new String[]{"scanScheme"});

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

        Pagination<Project> projectPagination;
        //查询我自己创建的
        if (("oneself").equals(projectQuery.getFindType())){
            Pagination<ProjectEntity> pagination = projectDao.findProjectPage(projectQuery);
            List<Project> projects = BeanMapper.mapList(pagination.getDataList(), Project.class);
            joinTemplate.joinQuery(projects,new String[]{"user"});
             projectPagination = PaginationBuilder.build(pagination, projects);
           /*  return projectPagination;*/
        }else {

            List<ProjectEntity> projectEntityList =  projectDao.findProjectList(projectQuery);

            List<Project> projectList =  BeanMapper.mapList(projectEntityList, Project.class);

            projectPagination=findViewProject(projectList,projectQuery);
        }

        List<ProjectCollect> collectList = projectCollectService.findProjectCollectList(new ProjectCollectQuery().setUserId(projectQuery.getUserId()));

        //查询项目的权限
        List<Project> dataList = projectPagination.getDataList();
        if (!CollectionUtils.isEmpty(dataList)){

            //查询类型不为关联仓库
            if (!("relevancyRepo").equals(projectQuery.getFindType())){
                List<String> ids = dataList.stream().map(Project::getId).collect(Collectors.toList());
                Map<String, Set<String>> permissions = permissionService.findDomainListPermissions(projectQuery.getUserId(), ids);

                for (Project project:dataList){
                    String time = ObjectUtils.isEmpty(project.getScanTime()) ? null : SourceFareUtil.time(project.getScanTime(), "project") + "前";
                    project.setNewScanTime(time);

                    //查询项目收藏
                    List<ProjectCollect> projectCollects = collectList.stream().filter(a -> project.getId().equals(a.getProjectId()))
                            .collect(Collectors.toList());

                    boolean collect = CollectionUtils.isEmpty(projectCollects) ? false : true;
                    project.setCollect(collect);

                    Set<String> stringSet = permissions.get(project.getId());
                    if (org.apache.commons.collections.CollectionUtils.isNotEmpty(stringSet)){
                        List<String> deletes = stringSet.stream().filter(a -> PROJECT_DELETE.equals(a)).collect(Collectors.toList());
                        List<String> updates = stringSet.stream().filter(a -> PROJECT_UPDATE.equals(a)).collect(Collectors.toList());
                        boolean delete = org.apache.commons.collections.CollectionUtils.isNotEmpty(deletes) ? true : false;
                        boolean update = org.apache.commons.collections.CollectionUtils.isNotEmpty(updates) ? true : false;
                        project.setDelete(delete);
                        project.setUpdate(update);
                    }
                }
            }
        }
        return PaginationBuilder.build(projectPagination,dataList);
    }

    @Override
    public List<Project> findDemoProjectList() {

        List<ProjectEntity> projectEntityList= projectDao.findDemoProjectList();

        List<Project> projectList = BeanMapper.mapList(projectEntityList, Project.class);

        return projectList;
    }

    @Override
    public List<Project> findProjectList(ProjectQuery projectQuery) {
        List<ProjectEntity> projectEntityList= projectDao.findProjectList(projectQuery);

        List<Project> projectList = BeanMapper.mapList(projectEntityList, Project.class);

        joinTemplate.joinQuery(projectList);

        return projectList;
    }

    @Override
    public Object findProjectNum(String userId) {
        Map<String, Object> hashMap = new HashMap<>();
        List<ProjectEntity> projectEntityList =  projectDao.findAllProject();

        List<Project> projectList =  BeanMapper.mapList(projectEntityList, Project.class);

        if (CollectionUtils.isEmpty(projectList)){
            return null;
        }

        //我创建的数量
        List<Project> projects = projectList.stream().filter(a -> a.getUser().getId().equals(userId)).collect(Collectors.toList());
        int createNum = CollectionUtils.isEmpty(projects) ? 0 : projects.size();
        hashMap.put("createNum",createNum);

        //总数量
        List<String> projectIds = findHaveAccessProjectIds(projectList, userId);
        hashMap.put("allNum",projectIds.size());

        //收藏数量
        List<ProjectCollect> collectList = projectCollectService.findProjectCollectList(new ProjectCollectQuery().setUserId(userId));
        List<String> collectProjectIds = collectList.stream().map(ProjectCollect::getProjectId).collect(Collectors.toList());
        projectIds.retainAll(collectProjectIds);
        hashMap.put("colletNum",projectIds.size());

        return hashMap;
    }

    /**
     * 查询有权限的项目
     * @param projectList projectList
     * @param projectQuery projectQuery
     */
    public Pagination<Project> findViewProject(List<Project> projectList,ProjectQuery projectQuery){

        if (CollectionUtils.isEmpty(projectList)){
            return PaginationBuilder.build(new Pagination<>(),null);
        }

        List<String> projectIds = findHaveAccessProjectIds(projectList, projectQuery.getUserId());
        //查询我收藏的
        if (("collect").equals(projectQuery.getFindType())){
            List<String> rpyIds = projectList.stream().map(Project::getId).collect(Collectors.toList());
            String[] rpyIdsArray = rpyIds.toArray(new String[rpyIds.size()]);
            List<ProjectCollect> projectCollectList = projectCollectService.findRepositoryCollectList(rpyIdsArray, projectQuery.getUserId());
            if (CollectionUtils.isEmpty(projectCollectList)){
                return PaginationBuilder.build(new Pagination<>(),null);
            }
            List<String> prCollectIds = projectCollectList.stream()
                    .map(ProjectCollect::getProjectId).collect(Collectors.toList());

            //获取重复的
            projectIds=projectIds.stream()
                    .filter(prCollectIds::contains)
                    .collect(Collectors.toList());
        }

        //查询
        if (CollectionUtils.isEmpty(projectIds)){
            return PaginationBuilder.build(new Pagination<>(),null);
        }

        //通过项目ids查询项目
        String[] idsArray = projectIds.toArray(new String[projectIds.size()]);
        Pagination<ProjectEntity> pagination = projectDao.findProjectPage(projectQuery, idsArray);
        List<Project> repositoryList = BeanMapper.mapList(pagination.getDataList(), Project.class);
        joinTemplate.joinQuery(repositoryList,new String[]{"user"});

        return PaginationBuilder.build(pagination,repositoryList);
    }


    /**
     *查询公共和有权限的项目ids
     * @param projectList 所有项目的ids
     * @param userId  用户id
     */
    public List<String> findHaveAccessProjectIds(List<Project> projectList,String userId){

        //公共的仓库Id
        List<String> canViewRpyId = projectList.stream().filter(a -> ("public").equals(a.getRules()))
                .map(Project::getId)
                .collect(Collectors.toList());

        //私有仓库id
        List<String> priProjectIds = projectList.stream().filter(a -> ("private").equals(a.getRules()))
                .map(Project::getId)
                .collect(Collectors.toList());

        if (!CollectionUtils.isEmpty(priProjectIds)){
            //根据用户id 查询关联的项目
            DmUserQuery dmUserQuery = new DmUserQuery();
            dmUserQuery.setUserId(userId);
            List<DmUser> dmUserList = dmUserService.findDmUserList(dmUserQuery);

            //存在项目成员
            if (!CollectionUtils.isEmpty(dmUserList)){
                List<String> dmRpyId = dmUserList.stream().map(DmUser::getDomainId).collect(Collectors.toList());

                //查询私有相同的仓库id
                List<String> canViewPriRpyId = priProjectIds.stream().filter(dmRpyId::contains).collect(Collectors.toList());

                canViewRpyId = Stream.concat(canViewPriRpyId.stream(), canViewRpyId.stream()).collect(Collectors.toList());
            }
        }
        return canViewRpyId;
    }


    /**
     *操作仓库发送消息
     * @param project 操作的项目
     * @param type  操作类型
     * @param  updateName 更新名字
     */
    public void sendMessLog(ProjectEntity project,String type,String updateName){
        Thread thread = new Thread() {
            public void run() {
                HashMap<String, Object> map = fareMessageService.initMessageAndLogMap();

                map.put("projectName", project.getName());
                map.put("projectId",project.getId());
                map.put("action",project.getName());

                //创建仓库发送消息和日志
                //map.put("repositoryPath",project.getAddress());
                if (("create").equals(type)){
                    map.put("message", project.getName());
                    map.put("link", SourceFareServerFinal.LOG_RPY_CREATE);
                    map.put("qywxurl", SourceFareServerFinal.LOG_RPY_CREATE);
                    fareMessageService.deployMessage(map, SourceFareServerFinal.LOG_TYPE_CREATE);
                    fareMessageService.deployLog(map, SourceFareServerFinal.LOG_TYPE_CREATE,"project");
                }
            }};
        thread.start();
    }

}