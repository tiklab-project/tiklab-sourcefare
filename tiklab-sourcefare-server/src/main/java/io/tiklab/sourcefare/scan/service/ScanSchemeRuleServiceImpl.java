package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.scan.dao.ScanSchemeRuleDao;
import io.tiklab.sourcefare.scan.entity.ScanSchemeRuleEntity;
import io.tiklab.sourcefare.scan.model.ScanSchemeRule;
import io.tiklab.sourcefare.scan.model.ScanSchemeRuleQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;

/**
* ScanSchemeRuleServiceImpl-扫描方案规则关系
*/
@Service
@Exporter
public class ScanSchemeRuleServiceImpl implements ScanSchemeRuleService {

    @Autowired
    ScanSchemeRuleDao scanSchemeRuleDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanRecordService scanRecordService;

    @Override
    public String createScanSchemeRule(@NotNull @Valid ScanSchemeRule scanSchemeRule) {

        ScanSchemeRuleEntity scanSchemeRuleEntity = BeanMapper.map(scanSchemeRule, ScanSchemeRuleEntity.class);
        scanSchemeRuleEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String scanSchemeRuleId= scanSchemeRuleDao.createScanSchemeRule(scanSchemeRuleEntity);

        return scanSchemeRuleId;
    }

    @Override
    public void updateScanSchemeRule(@NotNull @Valid ScanSchemeRule scanSchemeRule) {
        ScanSchemeRuleEntity scanSchemeRuleEntity = BeanMapper.map(scanSchemeRule, ScanSchemeRuleEntity.class);

        scanSchemeRuleDao.updateScanSchemeRule(scanSchemeRuleEntity);
    }

    @Override
    public void deleteScanSchemeRule(@NotNull String id) {
        scanSchemeRuleDao.deleteScanSchemeRule(id);
    }

    @Override
    public void deleteScanSchemeRuleByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(ScanSchemeRuleEntity.class)
                .eq(key, value)
                .get();
        scanSchemeRuleDao.deleteScanSchemeRule(deleteCondition);
    }

    @Override
    public ScanSchemeRule findOne(String id) {
        ScanSchemeRuleEntity scanSchemeRuleEntity = scanSchemeRuleDao.findScanSchemeRule(id);

        ScanSchemeRule scanSchemeRule = BeanMapper.map(scanSchemeRuleEntity, ScanSchemeRule.class);
        return scanSchemeRule;
    }

    @Override
    public List<ScanSchemeRule> findList(List<String> idList) {
        List<ScanSchemeRuleEntity> scanSchemeRuleEntityList =  scanSchemeRuleDao.findScanSchemeRuleList(idList);

        List<ScanSchemeRule> scanSchemeRuleList =  BeanMapper.mapList(scanSchemeRuleEntityList, ScanSchemeRule.class);
        return scanSchemeRuleList;
    }

    @Override
    public ScanSchemeRule findScanSchemeRule(@NotNull String id) {
        ScanSchemeRule scanSchemeRule = findOne(id);

        joinTemplate.joinQuery(scanSchemeRule);

        return scanSchemeRule;
    }

    @Override
    public List<ScanSchemeRule> findAllScanSchemeRule() {
        List<ScanSchemeRuleEntity> scanSchemeRuleEntityList =  scanSchemeRuleDao.findAllScanSchemeRule();

        List<ScanSchemeRule> scanSchemeRuleList =  BeanMapper.mapList(scanSchemeRuleEntityList, ScanSchemeRule.class);

        joinTemplate.joinQuery(scanSchemeRuleList);

        return scanSchemeRuleList;
    }

    @Override
    public List<ScanSchemeRule> findScanSchemeRuleList(ScanSchemeRuleQuery ScanSchemeRuleQuery) {
        List<ScanSchemeRuleEntity> scanSchemeRuleEntityList = scanSchemeRuleDao.findScanSchemeRuleList(ScanSchemeRuleQuery);

        List<ScanSchemeRule> scanSchemeRuleList = BeanMapper.mapList(scanSchemeRuleEntityList, ScanSchemeRule.class);
        joinTemplate.joinQuery(scanSchemeRuleList);

        return scanSchemeRuleList;
    }

    @Override
    public Pagination<ScanSchemeRule> findScanSchemeRulePage(ScanSchemeRuleQuery ScanSchemeRuleQuery) {
        Pagination<ScanSchemeRuleEntity>  pagination = scanSchemeRuleDao.findScanSchemeRulePage(ScanSchemeRuleQuery);

        List<ScanSchemeRule> scanSchemeRuleList = BeanMapper.mapList(pagination.getDataList(), ScanSchemeRule.class);
        joinTemplate.joinQuery(scanSchemeRuleList);

        return PaginationBuilder.build(pagination,scanSchemeRuleList);
    }

}