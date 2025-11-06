package io.tiklab.sourcefare.project.service;

import io.tiklab.core.exception.SystemException;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.project.dao.ProjectRepUploadDao;
import io.tiklab.sourcefare.project.entity.ProjectRepUploadEntity;
import io.tiklab.sourcefare.project.model.ProjectRepUpload;
import io.tiklab.sourcefare.project.model.ProjectRepUploadQuery;
import io.tiklab.sourcefare.scan.model.DeployEnv;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.io.FileUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.ObjectUtils;
import org.springframework.web.multipart.MultipartFile;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.io.File;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.sql.Timestamp;
import java.util.List;

/**
* ProjectRepUploadServiceImpl-扫描项目上传代码信息
*/
@Service
@Exporter
public class ProjectRepUploadServiceImpl implements ProjectRepUploadService {

    @Autowired
    ProjectRepUploadDao projectRepUploadDao;


    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    PathSetService pathSetService;

    @Override
    public String createProjectRepUpload(@NotNull @Valid ProjectRepUpload projectRepUpload) {

        ProjectRepUploadEntity projectRepUploadEntity = BeanMapper.map(projectRepUpload, ProjectRepUploadEntity.class);
        projectRepUploadEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));

        String repositoryRep = projectRepUploadDao.createProjectRepUpload(projectRepUploadEntity);

        return repositoryRep;
    }

    @Override
    public void updateProjectRepUpload(@NotNull @Valid ProjectRepUpload projectRepUpload) {
        ProjectRepUploadEntity projectRepUploadEntity = BeanMapper.map(projectRepUpload, ProjectRepUploadEntity.class);

        projectRepUploadDao.updateProjectRepUpload(projectRepUploadEntity);
    }

    @Override
    public void deleteProjectRepUpload(@NotNull String id) {
        projectRepUploadDao.deleteProjectRepUpload(id);
    }

    @Override
    public void deleteProjectRepUploadByRecord(String type,String data) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ProjectRepUploadEntity.class)
                .eq(type, data)
                .get();
        projectRepUploadDao.deleteProjectRepUpload(deleteCondition);
    }

    @Override
    public ProjectRepUpload findOne(String id) {
        ProjectRepUploadEntity projectRepUploadEntity = projectRepUploadDao.findProjectRepUpload(id);

        ProjectRepUpload projectRepUpload = BeanMapper.map(projectRepUploadEntity, ProjectRepUpload.class);
        return projectRepUpload;
    }

    @Override
    public List<ProjectRepUpload> findList(List<String> idList) {
        List<ProjectRepUploadEntity> projectRepUploadEntityList =  projectRepUploadDao.findProjectRepUploadList(idList);

        List<ProjectRepUpload> projectRepUploadList =  BeanMapper.mapList(projectRepUploadEntityList, ProjectRepUpload.class);
        return projectRepUploadList;
    }

    @Override
    public ProjectRepUpload findProjectRepUpload(@NotNull String id) {
        ProjectRepUpload projectRepUpload = findOne(id);

        return projectRepUpload;
    }

    @Override
    public List<ProjectRepUpload> findAllProjectRepUpload() {
        List<ProjectRepUploadEntity> projectRepUploadEntityList =  projectRepUploadDao.findAllProjectRepUpload();

        List<ProjectRepUpload> projectRepUploadList =  BeanMapper.mapList(projectRepUploadEntityList, ProjectRepUpload.class);

        return projectRepUploadList;
    }

    @Override
    public List<ProjectRepUpload> findProjectRepUploadList(ProjectRepUploadQuery ProjectRepUploadQuery) {
        List<ProjectRepUploadEntity> projectRepUploadEntityList = projectRepUploadDao.findProjectRepUploadList(ProjectRepUploadQuery);

        List<ProjectRepUpload> projectRepUploadList = BeanMapper.mapList(projectRepUploadEntityList, ProjectRepUpload.class);
        String codePath = pathSetService.codePath();



        return projectRepUploadList;
    }

    @Override
    public ProjectRepUpload findProjectRepUploadByRepId(String projectId) {
        List<ProjectRepUpload> projectRepUploadList = findProjectRepUploadList(new ProjectRepUploadQuery().setProjectId(projectId));
        if (CollectionUtils.isNotEmpty(projectRepUploadList)){
            String outputFolderPath = pathSetService.codePath() +"/"+ projectId;
            File file = new File(outputFolderPath);
            if (!file.exists()){
                return null;
            }
            return projectRepUploadList.get(0);
        }
        return null;
    }

    @Override
    public String upload(MultipartFile uploadFile, String projectId) {
        try {
            InputStream inputStream = uploadFile.getInputStream();
            String fileName = uploadFile.getOriginalFilename();

            String codePath = pathSetService.codePath();

            //文件地址
            String filePath = codePath + "/" + fileName;
            File file = new File(filePath);
            if (!file.exists()){
                file.createNewFile();
            }

            //用字节流写入文件
            FileOutputStream outputStream = new FileOutputStream(filePath);
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = inputStream.read(buffer)) != -1) {
                outputStream.write(buffer, 0, bytesRead);
            }
            outputStream.flush();


            //解压
            String outputFolderPath = pathSetService.codePath() +"/"+ projectId;
            //存在
            if (new File(outputFolderPath).exists()){
                FileUtils.deleteDirectory(new File(outputFolderPath));
            }

            SourceFareUtil.decompressionZip(filePath,outputFolderPath);
            new File(filePath).delete();

            //创建上传记录
            ProjectRepUpload repUpload = this.findProjectRepUploadByRepId(projectId);
            if (ObjectUtils.isEmpty(repUpload)){
                ProjectRepUpload projectRepUpload = new ProjectRepUpload();
                projectRepUpload.setProjectId(projectId);
                String fileNames = StringUtils.substringBeforeLast(fileName, ".zip");
                projectRepUpload.setCodeName(fileNames);
                this.createProjectRepUpload(projectRepUpload);
            }
            return "ok";
        }catch (Exception e){
            e.printStackTrace();
            throw new SystemException(e.getMessage());
        }
    }
}