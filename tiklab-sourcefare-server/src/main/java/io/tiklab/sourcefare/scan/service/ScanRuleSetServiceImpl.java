package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.scan.dao.ScanRuleSetDao;
import io.tiklab.sourcefare.scan.entity.ScanRuleSetEntity;
import io.tiklab.sourcefare.scan.model.ScanRuleSet;
import io.tiklab.sourcefare.scan.model.ScanRuleSetQuery;
import io.tiklab.sourcefare.scan.model.ScanSchemeRuleSet;
import io.tiklab.sourcefare.scan.model.ScanSchemeRuleSetQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;
import java.util.stream.Collectors;

/**
* ScanRuleSetServiceImpl-扫描计划集接口实现
*/
@Service
@Exporter
public class ScanRuleSetServiceImpl implements ScanRuleSetService {

    @Autowired
    ScanRuleSetDao scanRuleSetDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanSchemeRuleSetService scanSchemeRuleSetService;


    @Override
    public String createScanRuleSet(@NotNull @Valid ScanRuleSet openRecord) {

        ScanRuleSetEntity openRecordEntity = BeanMapper.map(openRecord, ScanRuleSetEntity.class);
        openRecordEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String openRecordId= scanRuleSetDao.createScanRuleSet(openRecordEntity);

        return openRecordId;
    }

    @Override
    public void createScanRuleSet(String sql) {
        scanRuleSetDao.execSql(sql);
    }

    @Override
    public void updateScanRuleSet(@NotNull @Valid ScanRuleSet openRecord) {
        ScanRuleSetEntity openRecordEntity = BeanMapper.map(openRecord, ScanRuleSetEntity.class);

        scanRuleSetDao.updateScanRuleSet(openRecordEntity);
    }

    @Override
    public void deleteScanRuleSet(@NotNull String id) {
        scanRuleSetDao.deleteScanRuleSet(id);
    }

    @Override
    public void deleteScanRuleSetByCondition(String key, String value) {

    }

    @Override
    public ScanRuleSet findOne(String id) {
        ScanRuleSetEntity openRecordEntity = scanRuleSetDao.findScanRuleSet(id);

        ScanRuleSet openRecord = BeanMapper.map(openRecordEntity, ScanRuleSet.class);
        return openRecord;
    }

    @Override
    public List<ScanRuleSet> findList(List<String> idList) {
        List<ScanRuleSetEntity> openRecordEntityList =  scanRuleSetDao.findScanRuleSetList(idList);

        List<ScanRuleSet> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanRuleSet.class);
        return openRecordList;
    }

    @Override
    public ScanRuleSet findScanRuleSet(@NotNull String id) {
        ScanRuleSet openRecord = findOne(id);

        joinTemplate.joinQuery(openRecord);

        return openRecord;
    }

    @Override
    public List<ScanRuleSet> findAllScanRuleSet() {
        List<ScanRuleSetEntity> openRecordEntityList =  scanRuleSetDao.findAllScanRuleSet();

        List<ScanRuleSet> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanRuleSet.class);

        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public List<ScanRuleSet> findScanRuleSetList(ScanRuleSetQuery ScanRuleSetQuery) {
        List<ScanRuleSetEntity> openRecordEntityList = scanRuleSetDao.findScanRuleSetList(ScanRuleSetQuery);

        List<ScanRuleSet> openRecordList = BeanMapper.mapList(openRecordEntityList, ScanRuleSet.class);
        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public Pagination<ScanRuleSet> findScanRuleSetPage(ScanRuleSetQuery ScanRuleSetQuery) {
        Pagination<ScanRuleSetEntity>  pagination = scanRuleSetDao.findScanRuleSetPage(ScanRuleSetQuery);

        List<ScanRuleSet> openRecordList = BeanMapper.mapList(pagination.getDataList(), ScanRuleSet.class);
        joinTemplate.joinQuery(pagination.getDataList());


        return PaginationBuilder.build(pagination,openRecordList);
    }

    @Override
    public List<ScanRuleSet> findScanRuleSetBySchemeId(String schemeId) {
        List<ScanRuleSet> scanRuleSets=null;
        List<ScanSchemeRuleSet> schemeRuleList = scanSchemeRuleSetService.findScanSchemeRuleSetList(new ScanSchemeRuleSetQuery().setScanSchemeId(schemeId));
        if(CollectionUtils.isNotEmpty(schemeRuleList)){
           scanRuleSets = schemeRuleList.stream().map(ScanSchemeRuleSet::getScanRuleSet).collect(Collectors.toList());
        }
        return scanRuleSets;
    }

    @Override
    public List<ScanRuleSet> findScanRuleSetNotScheme(String schemeId) {
        List<ScanRuleSet> scanRuleSets = this.findAllScanRuleSet();

        List<ScanSchemeRuleSet> schemeRuleList = scanSchemeRuleSetService.findScanSchemeRuleSetList(new ScanSchemeRuleSetQuery().setScanSchemeId(schemeId));
        if (CollectionUtils.isNotEmpty(schemeRuleList)){
             scanRuleSets = scanRuleSets.stream().filter(ruleSet -> schemeRuleList.stream().
                    allMatch(schemeRule -> !ruleSet.getId().equals(schemeRule.getScanRuleSet().getId()))).collect(Collectors.toList());
        }
        return scanRuleSets;
    }
}