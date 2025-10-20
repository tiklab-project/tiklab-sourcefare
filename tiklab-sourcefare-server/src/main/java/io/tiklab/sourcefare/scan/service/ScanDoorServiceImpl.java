package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.scan.dao.ScanDoorDao;
import io.tiklab.sourcefare.scan.entity.ScanDoorEntity;
import io.tiklab.sourcefare.scan.model.ScanDoor;
import io.tiklab.sourcefare.scan.model.ScanDoorQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;
import org.springframework.util.ObjectUtils;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;

/**
* ScanDoorServiceImpl-扫描门禁接口实现
*/
@Service
@Exporter
public class ScanDoorServiceImpl implements ScanDoorService {

    @Autowired
    ScanDoorDao scanDoorDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    ScanSchemeRuleSetService scanSchemeRuleSetService;

    @Autowired
    ScanSchemeRuleService scanSchemeRuleService;

    @Override
    public String createScanDoor(@NotNull @Valid ScanDoor scanDoor) {

        ScanDoorEntity ruleEntity = BeanMapper.map(scanDoor, ScanDoorEntity.class);
        ruleEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String scanDoorId= scanDoorDao.createScanDoor(ruleEntity);
        scanDoor.setId(scanDoorId);

        return scanDoorId;
    }



    @Override
    public void updateScanDoor(@NotNull @Valid ScanDoor openRecord) {
        ScanDoorEntity openRecordEntity = BeanMapper.map(openRecord, ScanDoorEntity.class);

        scanDoorDao.updateScanDoor(openRecordEntity);
    }

    @Override
    public void deleteScanDoor(@NotNull String id) {
        scanSchemeRuleService.deleteScanSchemeRuleByCondition("ruleId",id);

        scanDoorDao.deleteScanDoor(id);
    }

    @Override
    public void deleteScanDoorByCondition(String key, String value) {

    }

    @Override
    public ScanDoor findOne(String id) {
        ScanDoorEntity openRecordEntity = scanDoorDao.findScanDoor(id);

        ScanDoor openRecord = BeanMapper.map(openRecordEntity, ScanDoor.class);
        return openRecord;
    }

    @Override
    public List<ScanDoor> findList(List<String> idList) {
        List<ScanDoorEntity> openRecordEntityList =  scanDoorDao.findScanDoorList(idList);

        List<ScanDoor> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanDoor.class);
        return openRecordList;
    }

    @Override
    public ScanDoor findScanDoor(@NotNull String id) {
        ScanDoor openRecord = findOne(id);

        joinTemplate.joinQuery(openRecord);

        return openRecord;
    }

    @Override
    public List<ScanDoor> findAllScanDoor() {
        List<ScanDoorEntity> openRecordEntityList =  scanDoorDao.findAllScanDoor();

        List<ScanDoor> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanDoor.class);

        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public List<ScanDoor> findScanDoorList(ScanDoorQuery ScanDoorQuery) {
        List<ScanDoorEntity> openRecordEntityList = scanDoorDao.findScanDoorList(ScanDoorQuery);

        List<ScanDoor> openRecordList = BeanMapper.mapList(openRecordEntityList, ScanDoor.class);
        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public ScanDoor findScanDoorByProjectId(String projectId) {
        ScanDoor scanDoor;
        List<ScanDoor> scanDoorList = findScanDoorList(new ScanDoorQuery().setProjectId(projectId));
        if (CollectionUtils.isEmpty(scanDoorList)){
              scanDoor = this.findScanDoor("default");
        }else {
             scanDoor = scanDoorList.get(0);
        }
        return scanDoor;
    }

}