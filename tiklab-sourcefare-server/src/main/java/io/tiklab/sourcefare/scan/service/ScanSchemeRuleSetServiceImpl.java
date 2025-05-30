package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.sourcefare.scan.dao.ScanSchemeRuleSetDao;
import io.tiklab.sourcefare.scan.entity.ScanSchemeRuleSetEntity;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;

/**
* ScanSchemeRuleSetServiceImpl-扫描方案规则集关系
*/
@Service
@Exporter
public class ScanSchemeRuleSetServiceImpl implements ScanSchemeRuleSetService {

    @Autowired
    ScanSchemeRuleSetDao scanSchemeRuleSetDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    ScanSchemeRuleService scanSchemeRuleService;

    @Autowired
    ScanRuleService scanRuleService;


    @Override
    public String createScanSchemeRuleSet(@NotNull @Valid ScanSchemeRuleSet scanSchemeRuleSet) {

        ScanSchemeRuleSetEntity scanSchemeRuleSetEntity = BeanMapper.map(scanSchemeRuleSet, ScanSchemeRuleSetEntity.class);
        scanSchemeRuleSetEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String scanSchemeRuleSetId= scanSchemeRuleSetDao.createScanSchemeRuleSet(scanSchemeRuleSetEntity);


        List<ScanRule> scanRuleList = scanRuleService.findScanRuleList(new ScanRuleQuery().setRuleSetId(scanSchemeRuleSet.getScanRuleSet().getId()));
        if (CollectionUtils.isNotEmpty(scanRuleList)){
            ScanSchemeRule scanSchemeRule = new ScanSchemeRule();
            scanSchemeRule.setScanSchemeId(scanSchemeRuleSet.getScanSchemeId());
            scanSchemeRule.setSchemeRulesetId(scanSchemeRuleSetId);
            for (ScanRule scanRule:scanRuleList){
                scanSchemeRule.setScanRule(scanRule);
                scanSchemeRule.setProblemLevel(scanRule.getProblemLevel());
                scanSchemeRuleService.createScanSchemeRule(scanSchemeRule);
            }
        }
        return scanSchemeRuleSetId;
    }

    @Override
    public void updateScanSchemeRuleSet(@NotNull @Valid ScanSchemeRuleSet scanSchemeRuleSet) {
        ScanSchemeRuleSetEntity scanSchemeRuleSetEntity = BeanMapper.map(scanSchemeRuleSet, ScanSchemeRuleSetEntity.class);

        scanSchemeRuleSetDao.updateScanSchemeRuleSet(scanSchemeRuleSetEntity);
    }

    @Override
    public void deleteScanSchemeRuleSet(@NotNull String id) {
        scanSchemeRuleSetDao.deleteScanSchemeRuleSet(id);
    }

    @Override
    public void deleteScanSchemeRuleSetByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ScanSchemeRuleSetEntity.class)
                .eq(key, value)
                .get();
        scanSchemeRuleSetDao.deleteScanSchemeRuleSet(deleteCondition);
    }

    @Override
    public ScanSchemeRuleSet findOne(String id) {
        ScanSchemeRuleSetEntity scanSchemeRuleSetEntity = scanSchemeRuleSetDao.findScanSchemeRuleSet(id);

        ScanSchemeRuleSet scanSchemeRuleSet = BeanMapper.map(scanSchemeRuleSetEntity, ScanSchemeRuleSet.class);
        return scanSchemeRuleSet;
    }

    @Override
    public List<ScanSchemeRuleSet> findList(List<String> idList) {
        List<ScanSchemeRuleSetEntity> scanSchemeRuleSetEntityList =  scanSchemeRuleSetDao.findScanSchemeRuleSetList(idList);

        List<ScanSchemeRuleSet> scanSchemeRuleSetList =  BeanMapper.mapList(scanSchemeRuleSetEntityList, ScanSchemeRuleSet.class);
        return scanSchemeRuleSetList;
    }

    @Override
    public ScanSchemeRuleSet findScanSchemeRuleSet(@NotNull String id) {
        ScanSchemeRuleSet scanSchemeRuleSet = findOne(id);

        joinTemplate.joinQuery(scanSchemeRuleSet);

        return scanSchemeRuleSet;
    }

    @Override
    public List<ScanSchemeRuleSet> findAllScanSchemeRuleSet() {
        List<ScanSchemeRuleSetEntity> scanSchemeRuleSetEntityList =  scanSchemeRuleSetDao.findAllScanSchemeRuleSet();

        List<ScanSchemeRuleSet> scanSchemeRuleSetList =  BeanMapper.mapList(scanSchemeRuleSetEntityList, ScanSchemeRuleSet.class);

        joinTemplate.joinQuery(scanSchemeRuleSetList);

        return scanSchemeRuleSetList;
    }

    @Override
    public List<ScanSchemeRuleSet> findScanSchemeRuleSetList(ScanSchemeRuleSetQuery ScanSchemeRuleSetQuery) {
        List<ScanSchemeRuleSetEntity> scanSchemeRuleSetEntityList = scanSchemeRuleSetDao.findScanSchemeRuleSetList(ScanSchemeRuleSetQuery);

        List<ScanSchemeRuleSet> scanSchemeRuleSetList = BeanMapper.mapList(scanSchemeRuleSetEntityList, ScanSchemeRuleSet.class);
        joinTemplate.joinQuery(scanSchemeRuleSetList);
        if(CollectionUtils.isNotEmpty(scanSchemeRuleSetList)){
            for (ScanSchemeRuleSet ruleSet:scanSchemeRuleSetList){
                List<ScanSchemeRule> schemeRuleList = scanSchemeRuleService.findScanSchemeRuleList(new ScanSchemeRuleQuery().setSchemeRulesetId(ruleSet.getId()));
                int num = CollectionUtils.isNotEmpty(schemeRuleList) ? schemeRuleList.size() : 0;
                ruleSet.setRuleNum(num);
            }
        }

        return scanSchemeRuleSetList;
    }

    @Override
    public Pagination<ScanSchemeRuleSet> findScanSchemeRuleSetPage(ScanSchemeRuleSetQuery ScanSchemeRuleSetQuery) {
        Pagination<ScanSchemeRuleSetEntity>  pagination = scanSchemeRuleSetDao.findScanSchemeRuleSetPage(ScanSchemeRuleSetQuery);

        List<ScanSchemeRuleSet> scanSchemeRuleSetList = BeanMapper.mapList(pagination.getDataList(), ScanSchemeRuleSet.class);
        joinTemplate.joinQuery(scanSchemeRuleSetList);

        return PaginationBuilder.build(pagination,scanSchemeRuleSetList);
    }
}