package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.sourcefare.scan.entity.ScanRecordInstanceEntity;
import io.tiklab.sourcefare.scan.dao.ScanRecordInstanceDao;
import io.tiklab.sourcefare.scan.model.ScanPlay;
import io.tiklab.sourcefare.scan.model.ScanRecordInstance;
import io.tiklab.sourcefare.scan.model.ScanRecordInstanceQuery;
import io.tiklab.sourcefare.scan.model.ScanScheme;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.lang3.ObjectUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
* ScanRecordInstanceServiceImpl-扫描记录实例接口实现
*/
@Service
@Exporter
public class ScanRecordInstanceServiceImpl implements ScanRecordInstanceService {

    @Autowired
    ScanRecordInstanceDao scanRecordInstanceDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanPlayService scanPlayService;

    @Override
    public String createScanRecordInstance(@NotNull @Valid ScanRecordInstance openRecord) {

        ScanRecordInstanceEntity openRecordEntity = BeanMapper.map(openRecord, ScanRecordInstanceEntity.class);
        openRecordEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String openRecordId= scanRecordInstanceDao.createScanRecordInstance(openRecordEntity);

        return openRecordId;
    }

    @Override
    public void updateScanRecordInstance(@NotNull @Valid ScanRecordInstance openRecord) {
        ScanRecordInstanceEntity openRecordEntity = BeanMapper.map(openRecord, ScanRecordInstanceEntity.class);

        scanRecordInstanceDao.updateScanRecordInstance(openRecordEntity);
    }

    @Override
    public void deleteScanRecordInstance(@NotNull String id) {
        scanRecordInstanceDao.deleteScanRecordInstance(id);

    }

    @Override
    public void deleteScanRecordInstanceByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ScanRecordInstanceEntity.class)
                .eq(key,value)
                .get();
        scanRecordInstanceDao.deleteScanRecordInstance(deleteCondition);
    }

    @Override
    public ScanRecordInstance findOne(String id) {
        ScanRecordInstanceEntity openRecordEntity = scanRecordInstanceDao.findScanRecordInstance(id);

        ScanRecordInstance openRecord = BeanMapper.map(openRecordEntity, ScanRecordInstance.class);
        return openRecord;
    }

    @Override
    public List<ScanRecordInstance> findList(List<String> idList) {
        List<ScanRecordInstanceEntity> openRecordEntityList =  scanRecordInstanceDao.findScanRecordInstanceList(idList);

        List<ScanRecordInstance> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanRecordInstance.class);
        return openRecordList;
    }

    @Override
    public ScanRecordInstance findScanRecordInstance(@NotNull String id) {
        ScanRecordInstance openRecord = findOne(id);

        joinTemplate.joinQuery(openRecord);

        return openRecord;
    }

    @Override
    public List<ScanRecordInstance> findAllScanRecordInstance() {
        List<ScanRecordInstanceEntity> openRecordEntityList =  scanRecordInstanceDao.findAllScanRecordInstance();

        List<ScanRecordInstance> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanRecordInstance.class);

        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public List<ScanRecordInstance> findScanRecordInstanceList(ScanRecordInstanceQuery ScanRecordInstanceQuery) {
        List<ScanRecordInstanceEntity> openRecordEntityList = scanRecordInstanceDao.findScanRecordInstanceList(ScanRecordInstanceQuery);

        List<ScanRecordInstance> openRecordList = BeanMapper.mapList(openRecordEntityList, ScanRecordInstance.class);
        joinTemplate.joinQuery(openRecordList);
        if (CollectionUtils.isNotEmpty(openRecordList)){
            openRecordList = openRecordList.stream().sorted(Comparator.comparing(ScanRecordInstance::getCreateTime).reversed()).collect(Collectors.toList());
        }

        return openRecordList;
    }

    @Override
    public Pagination<ScanRecordInstance> findScanRecordInstancePage(ScanRecordInstanceQuery ScanRecordInstanceQuery) {
        Pagination<ScanRecordInstanceEntity>  pagination = scanRecordInstanceDao.findScanRecordInstancePage(ScanRecordInstanceQuery);

        List<ScanRecordInstance> openRecordList = BeanMapper.mapList(pagination.getDataList(), ScanRecordInstance.class);
        joinTemplate.joinQuery(openRecordList);


        return PaginationBuilder.build(pagination,openRecordList);
    }

    @Override
    public Pagination<ScanRecordInstance> findRecordInstancePageByPlay(ScanRecordInstanceQuery scanRecordInstanceQuery) {
        //扫描计划中的扫描方案
        ScanPlay scanPlay = scanPlayService.findOne(scanRecordInstanceQuery.getScanPlayId());
        ScanScheme scanScheme = scanPlay.getScanScheme();

        Pagination<ScanRecordInstance> scanRecordInstancePage=null;
        /*if (("sonar").equals(scanScheme.getScanWay())){
           scanRecordInstancePage = scanSonarService.findScanIssuesBySonar(scanRecordInstanceQuery);
        }*/
        if (("rule").equals(scanScheme.getScanWay())){
             scanRecordInstancePage = this.findScanRecordInstancePage(scanRecordInstanceQuery);
        }


        if (ObjectUtils.isEmpty(scanRecordInstancePage)){
            return null;
        }
        List<ScanRecordInstance> instances = scanRecordInstancePage.getDataList();
     /*   if (CollectionUtils.isNotEmpty(instances)){
            try {
                String repositoryAddress = RepositoryUtil.findRepositoryAddress(yamlDataMaService.repositoryAddress(),scanPlay.getRepository().getRpyId()) ;
                Git git = Git.open(new File(repositoryAddress));
                Repository repository = git.getRepository();
                ObjectId objectId = GitBranchUntil.findObjectId(repository, scanPlay.getBranch(), "branch");
                for (ScanRecordInstance recordInstance:instances) {
                    String fileName = recordInstance.getFileName();
                    //通过sonar 扫描获取的结果实例
                    if (("sonar").equals(scanScheme.getScanWay())){
                        if (fileName.startsWith(scanPlay.getRepository().getName()+":")){
                            fileName = fileName.substring(fileName.indexOf(":") + 1);
                        }
                    }
                    //通过扫描包扫描 获取的结果实例
                    if (("rule").equals(scanScheme.getScanWay())){
                        List<String> allFile = RepositoryFileUtil.findRepositoryAllFile(git, scanPlay.getBranch());
                        if(CollectionUtils.isNotEmpty(allFile)){
                            continue;
                        }
                        List<String> collect = allFile.stream().filter(a -> a.endsWith(recordInstance.getFileName())).collect(Collectors.toList());
                        if (CollectionUtils.isNotEmpty(collect)){
                            fileName = collect.get(0);
                        }
                    }
                    List<Map<String, String>> mapList = GitCommitUntil.gitFileCommitLog(git, objectId.getName(),fileName );
                    Map<String, String> stringMap = mapList.get(mapList.size()-1);
                    long data = Long.parseLong(stringMap.get("date"));
                    recordInstance.setImportTime(new Timestamp(data));
                }
            }catch (Exception e){
                throw new ApplicationException( "获取信息失败：" + e.getMessage());
            }

        }*/

        return scanRecordInstancePage;
    }
}