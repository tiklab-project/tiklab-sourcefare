package io.tiklab.sourcefare.scan.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.DeleteBuilders;
import io.tiklab.rpc.annotation.Exporter;
import io.tiklab.sourcefare.scan.dao.IssueStatisticDao;
import io.tiklab.sourcefare.scan.entity.DeployEnvEntity;
import io.tiklab.sourcefare.scan.entity.IssueStatisticEntity;
import io.tiklab.sourcefare.scan.model.*;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

/**
* IssueStatisticServiceImpl-扫描问题统计
*/
@Service
@Exporter
public class IssueStatisticServiceImpl implements IssueStatisticService {

    @Autowired
    IssueStatisticDao issueStatisticDao;

    @Autowired
    JoinTemplate joinTemplate;

    @Autowired
    ScanRecordService scanRecordService;

    @Autowired
    ScanSchemeRuleSetService scanSchemeRuleSetService;

    @Autowired
    ScanSchemeRuleService scanSchemeRuleService;

    @Autowired
    RecordInstanceService recordInstanceService;
    private IssueStatistic issueStatistic;

    @Override
    public String createIssueStatistic(@NotNull @Valid IssueStatistic issueStatistic) {
        this.issueStatistic = issueStatistic;

        IssueStatisticEntity ruleEntity = BeanMapper.map(issueStatistic, IssueStatisticEntity.class);
        ruleEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        String issueStatisticId= issueStatisticDao.createIssueStatistic(ruleEntity);
        issueStatistic.setId(issueStatisticId);

        return issueStatisticId;
    }

    @Override
    public void createIssueStatistic(List<IssueStatistic> issueStatistic) {
        issueStatisticDao.createIssueStatistic(issueStatistic);
    }


    @Override
    public void updateIssueStatistic(@NotNull @Valid IssueStatistic issueStatistic) {
        IssueStatisticEntity issueStatisticEntity = BeanMapper.map(issueStatistic, IssueStatisticEntity.class);

        issueStatisticDao.updateIssueStatistic(issueStatisticEntity);
    }

    @Override
    public void deleteIssueStatistic(@NotNull String id) {
        scanSchemeRuleService.deleteScanSchemeRuleByCondition("ruleId",id);

        issueStatisticDao.deleteIssueStatistic(id);
    }

    @Override
    public void deleteIssueStatisticByCondition(String key, String value) {
        DeleteCondition deleteCondition = DeleteBuilders.createDelete(IssueStatisticEntity.class)
                .eq(key,value)
                .get();
        issueStatisticDao.deleteIssueStatistic(deleteCondition);
    }

    @Override
    public IssueStatistic findOne(String id) {
        IssueStatisticEntity issueStatisticEntity = issueStatisticDao.findIssueStatistic(id);

        IssueStatistic issueStatistic = BeanMapper.map(issueStatisticEntity, IssueStatistic.class);
        return issueStatistic;
    }

    @Override
    public List<IssueStatistic> findList(List<String> idList) {
        List<IssueStatisticEntity> issueStatisticEntityList =  issueStatisticDao.findIssueStatisticList(idList);

        List<IssueStatistic> issueStatisticList =  BeanMapper.mapList(issueStatisticEntityList, IssueStatistic.class);
        return issueStatisticList;
    }

    @Override
    public IssueStatistic findIssueStatistic(@NotNull String id) {
        IssueStatistic issueStatistic = findOne(id);

        return issueStatistic;
    }

    @Override
    public List<IssueStatistic> findAllIssueStatistic() {
        List<IssueStatisticEntity> issueStatisticEntityList =  issueStatisticDao.findAllIssueStatistic();

        List<IssueStatistic> issueStatisticList =  BeanMapper.mapList(issueStatisticEntityList, IssueStatistic.class);

        return issueStatisticList;
    }

    @Override
    public List<IssueStatistic> findIssueStatisticList(IssueStatisticQuery IssueStatisticQuery) {
        List<IssueStatisticEntity> issueStatisticEntityList = issueStatisticDao.findIssueStatisticList(IssueStatisticQuery);

        List<IssueStatistic> issueStatisticList = BeanMapper.mapList(issueStatisticEntityList, IssueStatistic.class);
        return issueStatisticList;
    }



    @Override
    public Pagination<IssueStatistic> findIssueStatisticPage(IssueStatisticQuery IssueStatisticQuery) {
        Pagination<IssueStatisticEntity>  pagination = issueStatisticDao.findIssueStatisticPage(IssueStatisticQuery);

        List<IssueStatistic> issueStatisticList = BeanMapper.mapList(pagination.getDataList(), IssueStatistic.class);


        return PaginationBuilder.build(pagination,issueStatisticList);
    }

    @Override
    public Object findIssueStatisticCount(IssueStatisticQuery issueStatisticQuery) {

        Map<String, Integer> resultMap = new HashMap<>();
        List<IssueStatistic> issueStatisticList = findIssueStatisticList(issueStatisticQuery);
        List<IssueStatistic> unsolvestatisticList = issueStatisticList.stream().filter(a -> a.getProblemState() == 0).collect(Collectors.toList());
        List<IssueStatistic> solveStatisticList = issueStatisticList.stream().filter(a -> a.getProblemState() == 1).collect(Collectors.toList());

        int size = CollectionUtils.isEmpty(issueStatisticList) ? 0 : issueStatisticList.size();
        int unSolve = CollectionUtils.isEmpty(unsolvestatisticList) ? 0 : unsolvestatisticList.size();
        int solve = CollectionUtils.isEmpty(solveStatisticList) ? 0 : solveStatisticList.size();
        resultMap.put("allNum",size);
        resultMap.put("unSolveNum",unSolve);
        resultMap.put("solveNum",solve);

        return resultMap;
    }

    @Override
    public Object findIssueTypeStatisticCount(String recordId) {
        Map<String, Integer> resultMap = new HashMap<>();
        List<RecordInstance> instanceList = recordInstanceService.findScanInstanceByCon(recordId,"recordId");
        if (!CollectionUtils.isEmpty(instanceList)){
            List<RecordInstance> function = instanceList.stream().filter(a -> a.getRuleType().equals("function")).collect(Collectors.toList());
            List<RecordInstance> norm = instanceList.stream().filter(a -> a.getRuleType().equals("norm")).collect(Collectors.toList());
            List<RecordInstance> security = instanceList.stream().filter(a -> a.getRuleType().equals("security")).collect(Collectors.toList());

            int functionNum = CollectionUtils.isEmpty(function) ? 0 : function.size();
            int securityNum = CollectionUtils.isEmpty(security) ? 0 : security.size();
            int normNum = CollectionUtils.isEmpty(norm) ? 0 : norm.size();

            resultMap.put("all",functionNum+securityNum+normNum);
            resultMap.put("function",functionNum);
            resultMap.put("norm",normNum);
            resultMap.put("security",securityNum);
        }
        return resultMap;
    }
}