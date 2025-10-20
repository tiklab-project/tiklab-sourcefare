package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.DeployEnvEntity;
import io.tiklab.sourcefare.scan.entity.IssueStatisticEntity;
import io.tiklab.sourcefare.scan.model.IssueStatistic;
import io.tiklab.sourcefare.scan.model.IssueStatisticQuery;
import io.tiklab.sourcefare.scan.model.RecordDuplicated;
import io.tiklab.sourcefare.scan.model.RecordInstance;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.BatchPreparedStatementSetter;
import org.springframework.jdbc.core.BeanPropertyRowMapper;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.namedparam.NamedParameterJdbcTemplate;
import org.springframework.stereotype.Repository;

import java.sql.SQLException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * IssueStatisticDao-扫描问题统计数据库访问
 */
@Repository
public class IssueStatisticDao {

    private static Logger logger = LoggerFactory.getLogger(IssueStatisticDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param issueStatisticEntity
     * @return
     */
    public String createIssueStatistic(IssueStatisticEntity issueStatisticEntity) {
        return jpaTemplate.save(issueStatisticEntity,String.class);
    }

    /**
     * 更新
     * @param issueStatisticEntity
     */
    public void updateIssueStatistic(IssueStatisticEntity issueStatisticEntity){
        jpaTemplate.update(issueStatisticEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteIssueStatistic(String id){
        jpaTemplate.delete(IssueStatisticEntity.class,id);
    }

    /**
     * 条件删除问题统计
     * @param deleteCondition
     */
    public void deleteIssueStatistic(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public IssueStatisticEntity findIssueStatistic(String id){
        return jpaTemplate.findOne(IssueStatisticEntity.class,id);
    }

    /**
    * 查询所有问题统计
    * @return
    */
    public List<IssueStatisticEntity> findAllIssueStatistic() {
        return jpaTemplate.findAll(IssueStatisticEntity.class);
    }

    /**
     * 通过ids查询问题统计
     * @param idList
     * @return List <IssueStatisticEntity>
     */
    public List<IssueStatisticEntity> findIssueStatisticList(List<String> idList) {
        return jpaTemplate.findList(IssueStatisticEntity.class,idList);
    }

    /**
     * 条件查询问题统计
     * @param issueStatisticQuery issueStatisticQuery
     * @return List <IssueStatisticEntity>
     */
    public List<IssueStatisticEntity> findIssueStatisticList(IssueStatisticQuery issueStatisticQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(IssueStatisticEntity.class)
                .eq("projectId",issueStatisticQuery.getProjectId())
                .eq("filePath",issueStatisticQuery.getFilePath())
                .eq("ruleName", issueStatisticQuery.getRuleName())
                .eq("problemLine",issueStatisticQuery.getProblemLine())
                .eq("problemState",issueStatisticQuery.getProblemState())
                .eq("ruleType",issueStatisticQuery.getRuleType())
                .eq("problemLevel",issueStatisticQuery.getProblemLevel())
                .orders(issueStatisticQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, IssueStatisticEntity.class);
    }

    /**
     * 条件分页查询问题统计
     * @param issueStatisticQuery issueStatisticQuery
     * @return List <IssueStatisticEntity>
     */
    public Pagination<IssueStatisticEntity> findIssueStatisticPage(IssueStatisticQuery issueStatisticQuery) {

        QueryCondition queryCondition = QueryBuilders.createQuery(IssueStatisticEntity.class)
                .eq("projectId",issueStatisticQuery.getProjectId())
                .eq("filePath",issueStatisticQuery.getFilePath())
                .eq("ruleName", issueStatisticQuery.getRuleName())
                .eq("problemLine",issueStatisticQuery.getProblemLine())
                .eq("problemState",issueStatisticQuery.getProblemState())
                .eq("ruleType",issueStatisticQuery.getRuleType())
                .eq("problemLevel",issueStatisticQuery.getProblemLevel())
                .orders(issueStatisticQuery.getOrderParams())
                .pagination(issueStatisticQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, IssueStatisticEntity.class);
    }


    /**
     * 创建
     * @param issueStatistic
     * @return
     */
    public void createIssueStatistic(List<IssueStatistic> issueStatistic) {
        String insertSQL = "INSERT INTO wair_issue_statistic (" +
                "id, project_id, file_path, problem_level, problem_line, rule_name, rule_type, problem_state, problem_desc,create_time) " +
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?,?)";
        jpaTemplate.getJdbcTemplate().batchUpdate(insertSQL, new BatchPreparedStatementSetter() {
            @Override
            public void setValues(java.sql.PreparedStatement ps, int i) throws SQLException {
                IssueStatistic statistic = issueStatistic.get(i);
                ps.setString(1, statistic.getId());
                ps.setString(2, statistic.getProjectId());
                ps.setString(3, statistic.getFilePath());
                ps.setInt(4, statistic.getProblemLevel());
                ps.setInt(5, statistic.getProblemLine());
                ps.setString(6, statistic.getRuleName());
                ps.setString(7, statistic.getRuleType());
                ps.setInt(8, statistic.getProblemState());
                ps.setString(9, statistic.getProblemDesc());
                ps.setTimestamp(10, statistic.getCreateTime());

            }

            @Override
            public int getBatchSize() {
                return issueStatistic.size();
            }
        });
    }

}