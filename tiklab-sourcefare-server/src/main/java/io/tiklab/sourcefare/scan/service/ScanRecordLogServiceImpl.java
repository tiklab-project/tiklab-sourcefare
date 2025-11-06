package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.project.service.PathSetService;
import io.tiklab.sourcefare.scan.dao.ScanRecordLogDao;
import io.tiklab.sourcefare.scan.entity.ScanRecordLogEntity;
import io.tiklab.sourcefare.scan.model.ScanRecordLog;
import io.tiklab.sourcefare.scan.model.ScanRecordLogQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

/**
* ScanRecordLogServiceImpl-扫描记录日志
*/
@Service
@Exporter
public class ScanRecordLogServiceImpl implements ScanRecordLogService {

    @Autowired
    ScanRecordLogDao ScanRecordLogDao;

    @Autowired
    JoinTemplate joinTemplate;


    @Autowired
    PathSetService pathSetService;

    @Override
    public String createScanRecordLog(@NotNull @Valid ScanRecordLog recordInstance) {

        ScanRecordLogEntity recordInstanceEntity = BeanMapper.map(recordInstance, ScanRecordLogEntity.class);
        String recordInstanceId= ScanRecordLogDao.createScanRecordLog(recordInstanceEntity);

        return recordInstanceId;
    }

    @Override
    public void updateScanRecordLog(@NotNull @Valid ScanRecordLog recordInstance) {
        ScanRecordLogEntity recordInstanceEntity = BeanMapper.map(recordInstance, ScanRecordLogEntity.class);

        ScanRecordLogDao.updateScanRecordLog(recordInstanceEntity);
    }

    @Override
    public void deleteScanRecordLog(@NotNull String id) {
        ScanRecordLogDao.deleteScanRecordLog(id);
    }

    @Override
    public void deleteScanRecordLogByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ScanRecordLogEntity.class)
                .eq(key,value)
                .get();
        ScanRecordLogDao.deleteScanRecordLog(deleteCondition);


    }




    @Override
    public ScanRecordLog findOne(String id) {
        ScanRecordLogEntity recordInstanceEntity = ScanRecordLogDao.findScanRecordLog(id);

        ScanRecordLog recordInstance = BeanMapper.map(recordInstanceEntity, ScanRecordLog.class);
        return recordInstance;
    }

    @Override
    public List<ScanRecordLog> findList(List<String> idList) {
        List<ScanRecordLogEntity> recordInstanceEntityList =  ScanRecordLogDao.findScanRecordLogList(idList);

        List<ScanRecordLog> recordInstanceList =  BeanMapper.mapList(recordInstanceEntityList, ScanRecordLog.class);
        return recordInstanceList;
    }

    @Override
    public ScanRecordLog findScanRecordLog(@NotNull String id) {
        ScanRecordLog recordInstance = findOne(id);

        joinTemplate.joinQuery(recordInstance);

        return recordInstance;
    }

    @Override
    public List<ScanRecordLog> findAllScanRecordLog() {
        List<ScanRecordLogEntity> recordInstanceEntityList =  ScanRecordLogDao.findAllScanRecordLog();

        List<ScanRecordLog> recordInstanceList =  BeanMapper.mapList(recordInstanceEntityList, ScanRecordLog.class);

        joinTemplate.joinQuery(recordInstanceList);

        return recordInstanceList;
    }

    @Override
    public List<ScanRecordLog> findScanRecordLogList(ScanRecordLogQuery ScanRecordLogQuery) {
        List<ScanRecordLogEntity> recordInstanceEntityList = ScanRecordLogDao.findScanRecordLogList(ScanRecordLogQuery);

        List<ScanRecordLog> recordInstanceList = BeanMapper.mapList(recordInstanceEntityList, ScanRecordLog.class);
        joinTemplate.joinQuery(recordInstanceList);

        return recordInstanceList;
    }

    @Override
    public Pagination<ScanRecordLog> findScanRecordLogPage(ScanRecordLogQuery ScanRecordLogQuery) {
        Pagination<ScanRecordLogEntity>  pagination = ScanRecordLogDao.findScanRecordLogPage(ScanRecordLogQuery);

        List<ScanRecordLog> recordInstanceList = BeanMapper.mapList(pagination.getDataList(), ScanRecordLog.class);
        joinTemplate.joinQuery(recordInstanceList);


        return PaginationBuilder.build(pagination,recordInstanceList);
    }

    /**
     * 创建扫描记录的日志
     * @param project project
     * @param recordId recordId
     */
    public List<ScanRecordLog> createRecordLog(Project project, String recordId){
        List<ScanRecordLog> arrayList = new ArrayList<>();
        List<String> logTypeList = new ArrayList<>(Arrays.asList("compile", "scan", "duplicated", "complexity"));

        //开启了覆盖率
        Integer cover = project.getCover();
        if (cover==1){
            logTypeList.add("cover");
        }
        for (String logType:logTypeList){

            ScanRecordLog recordLog = new ScanRecordLog();
            recordLog.setProjectId(project.getId());
            recordLog.setScanRecordId(recordId);
            recordLog.setTime("0秒");
            recordLog.setState(3);
            recordLog.setType(logType);
            recordLog.setScanType(project.getScanType());
            SourceFareUtil.addLogOrder(recordLog,logType);
            String logId = this.createScanRecordLog(recordLog);
            recordLog.setId(logId);
            arrayList.add(recordLog);
        }
        return arrayList;
    }
}