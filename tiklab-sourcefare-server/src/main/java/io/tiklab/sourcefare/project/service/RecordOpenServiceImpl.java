package io.tiklab.sourcefare.project.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.project.dao.RecordOpenDao;
import io.tiklab.sourcefare.project.entity.RecordOpenEntity;
import io.tiklab.sourcefare.project.model.RecordOpen;
import io.tiklab.sourcefare.project.model.RecordOpenQuery;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.service.ScanRecordService;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import io.tiklab.user.dmUser.model.DmUser;
import io.tiklab.user.dmUser.model.DmUserQuery;
import io.tiklab.user.dmUser.service.DmUserService;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
* RecordOpenServiceImpl-打开仓库的记录接口实现
*/
@Service
@Exporter
public class RecordOpenServiceImpl implements RecordOpenService {

    @Autowired
    RecordOpenDao recordOpenDao;

    @Autowired
    private DmUserService dmUserService;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanRecordService scanRecordService;



    @Override
    public String createRecordOpen(@NotNull @Valid RecordOpen openRecord) {

        String openRecordId=null;
        RecordOpenEntity openRecordEntity = BeanMapper.map(openRecord, RecordOpenEntity.class);

        List<RecordOpenEntity> recordList = recordOpenDao.findRecordOpenList(new RecordOpenQuery().setUserId(openRecord.getUserId())
                .setProjectId(openRecord.getProject().getId()));
        if (CollectionUtils.isNotEmpty(recordList)){
            RecordOpenEntity record = recordList.get(0);
            record.setNewOpenTime(new Timestamp(System.currentTimeMillis()));
            recordOpenDao.updateRecordOpen(record);
            openRecordId=record.getId();
        }else {
            openRecordEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
            openRecordEntity.setNewOpenTime(new Timestamp(System.currentTimeMillis()));
            openRecordId= recordOpenDao.createRecordOpen(openRecordEntity);
        }

        return openRecordId;
    }

    @Override
    public void updateRecordOpen(@NotNull @Valid RecordOpen openRecord) {
        RecordOpenEntity openRecordEntity = BeanMapper.map(openRecord, RecordOpenEntity.class);

        recordOpenDao.updateRecordOpen(openRecordEntity);
    }

    @Override
    public void deleteRecordOpen(@NotNull String id) {
        recordOpenDao.deleteRecordOpen(id);
    }

    @Override
    public void deleteRecordOpenByRecord(String repositoryId) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(RecordOpenEntity.class)
                .eq("projectId", repositoryId)
                .get();
        recordOpenDao.deleteRecordOpen(deleteCondition);
    }

    @Override
    public RecordOpen findOne(String id) {
        RecordOpenEntity openRecordEntity = recordOpenDao.findRecordOpen(id);

        RecordOpen openRecord = BeanMapper.map(openRecordEntity, RecordOpen.class);
        return openRecord;
    }

    @Override
    public List<RecordOpen> findList(List<String> idList) {
        List<RecordOpenEntity> openRecordEntityList =  recordOpenDao.findRecordOpenList(idList);

        List<RecordOpen> openRecordList =  BeanMapper.mapList(openRecordEntityList, RecordOpen.class);
        return openRecordList;
    }

    @Override
    public RecordOpen findRecordOpen(@NotNull String id) {
        RecordOpen openRecord = findOne(id);

        joinTemplate.joinQuery(openRecord);

        return openRecord;
    }

    @Override
    public List<RecordOpen> findAllRecordOpen() {
        List<RecordOpenEntity> openRecordEntityList =  recordOpenDao.findAllRecordOpen();

        List<RecordOpen> openRecordList =  BeanMapper.mapList(openRecordEntityList, RecordOpen.class);

        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public List<RecordOpen> findRecordOpenList(RecordOpenQuery RecordOpenQuery) {
        List<RecordOpenEntity> openRecordEntityList = recordOpenDao.findRecordOpenList(RecordOpenQuery);

        List<RecordOpen> openRecordList = BeanMapper.mapList(openRecordEntityList, RecordOpen.class);
        joinTemplate.joinQuery(openRecordList,new String[]{"project"});

        List<RecordOpen> publicRep = openRecordList.stream().filter(a -> ("public").equals(a.getProject().getRules())).collect(Collectors.toList());

        //查询私有库
        List<RecordOpen> privateRep = openRecordList.stream().filter(a -> ("private").equals(a.getProject().getRules())).collect(Collectors.toList());
        if (CollectionUtils.isNotEmpty(privateRep)){
            //查询用户id 查询关联的项目
            DmUserQuery dmUserQuery = new DmUserQuery();
            dmUserQuery.setUserId(RecordOpenQuery.getUserId());
            List<DmUser> dmUserList = dmUserService.findDmUserList(dmUserQuery);
            List<RecordOpen> arrayList = new ArrayList<>();
            for (DmUser dmUser:dmUserList){
                List<RecordOpen> repositories = privateRep.stream().filter(a -> dmUser.getDomainId().equals(a.getProject().getId())).collect(Collectors.toList());
                if (CollectionUtils.isNotEmpty(repositories)){
                    arrayList.add(repositories.get(0));
                }
            }
            publicRep.addAll(arrayList);
        }

        List<RecordOpen> recordOpenList = publicRep.stream().sorted(Comparator.comparing(RecordOpen::getNewOpenTime).reversed()).collect(Collectors.toList());
        //取前面6位
        List<RecordOpen> recordOpens = recordOpenList.stream().limit(6).collect(Collectors.toList());
        for (RecordOpen recordOpen:recordOpens){
           //成员数量
            DmUserQuery dmUserQuery = new DmUserQuery();
            dmUserQuery.setDomainId(recordOpen.getProject().getId());
            List<DmUser> dmUserList = dmUserService.findDmUserList(dmUserQuery);
            recordOpen.setMemberNum(dmUserList.size());

            List<ScanRecord> recordList = scanRecordService.findScanRecordListByProjectId(recordOpen.getProject().getId());
            int num = CollectionUtils.isNotEmpty(recordList) ? recordList.size() : 0;
            recordOpen.setExecNum(num);

        }
        return recordOpenList;

    }

    @Override
    public Pagination<RecordOpen> findRecordOpenPage(RecordOpenQuery RecordOpenQuery) {
        Pagination<RecordOpenEntity>  pagination = recordOpenDao.findRecordOpenPage(RecordOpenQuery);

        List<RecordOpen> openRecordList = BeanMapper.mapList(pagination.getDataList(), RecordOpen.class);
        joinTemplate.joinQuery(pagination.getDataList());

        return PaginationBuilder.build(pagination,openRecordList);
    }
}