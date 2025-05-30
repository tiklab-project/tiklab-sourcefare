package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.sourcefare.scan.dao.ScanRuleDao;
import io.tiklab.sourcefare.scan.entity.ScanRuleEntity;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.ObjectUtils;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;

/**
* ScanRuleServiceImpl-扫描规则接口实现
*/
@Service
@Exporter
public class ScanRuleServiceImpl implements ScanRuleService {

    @Autowired
    ScanRuleDao scanRuleDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    ScanSchemeRuleSetService scanSchemeRuleSetService;

    @Autowired
    ScanSchemeRuleService scanSchemeRuleService;

    @Override
    public String createScanRule(@NotNull @Valid ScanRule scanRule) {

        ScanRuleEntity ruleEntity = BeanMapper.map(scanRule, ScanRuleEntity.class);
        ruleEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String scanRuleId= scanRuleDao.createScanRule(ruleEntity);
        scanRule.setId(scanRuleId);

        List<ScanSchemeRuleSet> schemeRuleSetList = scanSchemeRuleSetService.findScanSchemeRuleSetList(new ScanSchemeRuleSetQuery().setRuleSetId(scanRule.getRuleSetId()));
        if (CollectionUtils.isNotEmpty(schemeRuleSetList)){
            for (ScanSchemeRuleSet schemeRuleSet:schemeRuleSetList){
                ScanSchemeRule scanSchemeRule = new ScanSchemeRule();

                scanSchemeRule.setSchemeRulesetId(schemeRuleSet.getId());
                scanSchemeRule.setScanRule(scanRule);
                scanSchemeRule.setProblemLevel(scanRule.getProblemLevel());
                scanSchemeRule.setScanSchemeId(schemeRuleSet.getScanSchemeId());
                scanSchemeRuleService.createScanSchemeRule(scanSchemeRule);
            }
        }
        return scanRuleId;
    }

    @Override
    public void updateScanRule(@NotNull @Valid ScanRule openRecord) {
        ScanRuleEntity openRecordEntity = BeanMapper.map(openRecord, ScanRuleEntity.class);

        scanRuleDao.updateScanRule(openRecordEntity);
    }

    @Override
    public void deleteScanRule(@NotNull String id) {
        scanSchemeRuleService.deleteScanSchemeRuleByCondition("ruleId",id);

        scanRuleDao.deleteScanRule(id);
    }

    @Override
    public void deleteScanRuleByCondition(String key, String value) {

    }

    @Override
    public ScanRule findOne(String id) {
        ScanRuleEntity openRecordEntity = scanRuleDao.findScanRule(id);

        ScanRule openRecord = BeanMapper.map(openRecordEntity, ScanRule.class);
        return openRecord;
    }

    @Override
    public List<ScanRule> findList(List<String> idList) {
        List<ScanRuleEntity> openRecordEntityList =  scanRuleDao.findScanRuleList(idList);

        List<ScanRule> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanRule.class);
        return openRecordList;
    }

    @Override
    public ScanRule findScanRule(@NotNull String id) {
        ScanRule openRecord = findOne(id);

        joinTemplate.joinQuery(openRecord);

        return openRecord;
    }

    @Override
    public List<ScanRule> findAllScanRule() {
        List<ScanRuleEntity> openRecordEntityList =  scanRuleDao.findAllScanRule();

        List<ScanRule> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanRule.class);

        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public List<ScanRule> findScanRuleList(ScanRuleQuery ScanRuleQuery) {
        List<ScanRuleEntity> openRecordEntityList = scanRuleDao.findScanRuleList(ScanRuleQuery);

        List<ScanRule> openRecordList = BeanMapper.mapList(openRecordEntityList, ScanRule.class);
        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public Pagination<ScanRule> findScanRulePage(ScanRuleQuery ScanRuleQuery) {
        //查询所有等级的规则
        if (!ObjectUtils.isEmpty(ScanRuleQuery.getProblemLevel())&&ScanRuleQuery.getProblemLevel()==0){
            ScanRuleQuery.setProblemLevel(null);
        }
        //查询所有工具的规则
        if (!ObjectUtils.isEmpty(ScanRuleQuery.getScanTool())&&("all").equals(ScanRuleQuery.getScanTool())){
            ScanRuleQuery.setScanTool(null);
        }

        Pagination<ScanRuleEntity>  pagination = scanRuleDao.findScanRulePage(ScanRuleQuery);

        List<ScanRule> openRecordList = BeanMapper.mapList(pagination.getDataList(), ScanRule.class);
        joinTemplate.joinQuery(openRecordList);

        return PaginationBuilder.build(pagination,openRecordList);
    }
}