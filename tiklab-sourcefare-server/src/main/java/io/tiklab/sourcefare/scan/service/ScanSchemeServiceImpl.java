package io.tiklab.sourcefare.scan.service;

import dm.jdbc.util.StringUtil;
import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.scan.dao.ScanShemeDao;
import io.tiklab.sourcefare.scan.entity.ScanSchemeEntity;
import io.tiklab.sourcefare.scan.model.ScanScheme;
import io.tiklab.sourcefare.scan.model.ScanSchemeQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.collections.CollectionUtils;
import org.apache.commons.lang3.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

import static io.tiklab.sourcefare.common.SourceWairServerFinal.*;

/**
* ScanSchemeServiceImpl-扫描方案
*/
@Service
@Exporter
public class ScanSchemeServiceImpl implements ScanSchemeService {

    @Autowired
    ScanShemeDao scanSchemeDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanSchemeRuleSetService schemeRuleSetService;

    @Autowired
    ScanSchemeRuleService scanSchemeRuleService;

    @Override
    public String createScanScheme(@NotNull @Valid ScanScheme openRecord) {

        ScanSchemeEntity openRecordEntity = BeanMapper.map(openRecord, ScanSchemeEntity.class);
        openRecordEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String openRecordId= scanSchemeDao.createScanScheme(openRecordEntity);

        return openRecordId;
    }

    @Override
    public void updateScanScheme(@NotNull @Valid ScanScheme openRecord) {
        ScanSchemeEntity openRecordEntity = BeanMapper.map(openRecord, ScanSchemeEntity.class);

        scanSchemeDao.updateScanScheme(openRecordEntity);
    }

    @Override
    public void deleteScanScheme(@NotNull String id) {
        scanSchemeDao.deleteScanScheme(id);

        schemeRuleSetService.deleteScanSchemeRuleSetByCondition("scanSchemeId",id);

        scanSchemeRuleService.deleteScanSchemeRuleByCondition("scanSchemeId",id);
    }

    @Override
    public void deleteScanSchemeByCondition(String key, String value) {

    }

    @Override
    public ScanScheme findOne(String id) {
        ScanSchemeEntity openRecordEntity = scanSchemeDao.findScanScheme(id);

        ScanScheme openRecord = BeanMapper.map(openRecordEntity, ScanScheme.class);
        return openRecord;
    }

    @Override
    public List<ScanScheme> findList(List<String> idList) {
        List<ScanSchemeEntity> openRecordEntityList =  scanSchemeDao.findScanSchemeList(idList);

        List<ScanScheme> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanScheme.class);
        return openRecordList;
    }

    @Override
    public ScanScheme findScanScheme(@NotNull String id) {
        ScanScheme openRecord = findOne(id);

        joinTemplate.joinQuery(openRecord);

        return openRecord;
    }

    @Override
    public List<ScanScheme> findAllScanScheme() {
        List<ScanSchemeEntity> openRecordEntityList =  scanSchemeDao.findAllScanScheme();

        List<ScanScheme> openRecordList =  BeanMapper.mapList(openRecordEntityList, ScanScheme.class);

        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public List<ScanScheme> findScanSchemeList(ScanSchemeQuery ScanSchemeQuery) {
        List<ScanSchemeEntity> openRecordEntityList = scanSchemeDao.findScanSchemeList(ScanSchemeQuery);

        List<ScanScheme> openRecordList = BeanMapper.mapList(openRecordEntityList, ScanScheme.class);
        joinTemplate.joinQuery(openRecordList);

        return openRecordList;
    }

    @Override
    public Pagination<ScanScheme> findScanSchemePage(ScanSchemeQuery ScanSchemeQuery) {
        Pagination<ScanSchemeEntity>  pagination = scanSchemeDao.findScanSchemePage(ScanSchemeQuery);

        List<ScanScheme> openRecordList = BeanMapper.mapList(pagination.getDataList(), ScanScheme.class);
        joinTemplate.joinQuery(pagination.getDataList());

       openRecordList = openRecordList.stream().sorted(Comparator.comparing(ScanScheme::getCreateTime).reversed()).collect(Collectors.toList());
        return PaginationBuilder.build(pagination,openRecordList);
    }

    @Override
    public List<ScanScheme> findScanSchemeByLanguage(ScanSchemeQuery scanSchemeQuery) {
        List<ScanScheme> allScanScheme = findAllScanScheme();
        if (CollectionUtils.isNotEmpty(allScanScheme)){
            String lowerCase = scanSchemeQuery.getLanguage().toLowerCase();

            List<ScanScheme> scanSchemes = allScanScheme.stream().filter(a -> a.getLanguage().toLowerCase().equals(lowerCase)).collect(Collectors.toList());

            if (StringUtils.isNotBlank(scanSchemeQuery.getScanType())){
                if ((STATIC).equals(scanSchemeQuery.getScanType())){
                     scanSchemes = scanSchemes.stream().filter(a -> a.getSchemeName().contains("静态")).collect(Collectors.toList());
                }
                if ((COMPILE).equals(scanSchemeQuery.getScanType())){
                    scanSchemes = scanSchemes.stream().filter(a -> !a.getSchemeName().contains("静态")).collect(Collectors.toList());
                }
            }
            return scanSchemes;
        }
        return null;
    }
}