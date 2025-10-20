package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Page;
import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.RecordInstanceEntity;
import io.tiklab.sourcefare.scan.model.RecordInstance;
import io.tiklab.sourcefare.scan.model.RecordInstanceCondQuery;
import io.tiklab.sourcefare.scan.model.RecordInstanceQuery;
import io.tiklab.sourcefare.scan.model.ScanRule;
import org.apache.commons.lang3.ObjectUtils;
import org.apache.commons.lang3.StringUtils;
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
 * ScanRecordInstanceDao-扫描记录实例数据库访问
 */
@Repository
public class RecordInstanceDao {

    private static Logger logger = LoggerFactory.getLogger(RecordInstanceDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param scanRecordInstanceEntity
     * @return
     */
    public String createScanRecordInstance(RecordInstanceEntity scanRecordInstanceEntity) {
        return jpaTemplate.save(scanRecordInstanceEntity,String.class);
    }

    /**
     * 更新
     * @param scanRecordInstanceEntity
     */
    public void updateScanRecordInstance(RecordInstanceEntity scanRecordInstanceEntity){
        jpaTemplate.update(scanRecordInstanceEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteScanRecordInstance(String id){
        jpaTemplate.delete(RecordInstanceEntity.class,id);
    }

    /**
     * 条件删除扫描记录实例
     * @param deleteCondition
     */
    public void deleteScanRecordInstance(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public RecordInstanceEntity findScanRecordInstance(String id){
        return jpaTemplate.findOne(RecordInstanceEntity.class,id);
    }

    /**
    * 查询所有扫描记录实例
    * @return
    */
    public List<RecordInstanceEntity> findAllScanRecordInstance() {
        return jpaTemplate.findAll(RecordInstanceEntity.class);
    }

    /**
     * 通过ids查询扫描记录实例
     * @param idList
     * @return List <ScanRecordInstanceEntity>
     */
    public List<RecordInstanceEntity> findScanRecordInstanceList(List<String> idList) {
        return jpaTemplate.findList(RecordInstanceEntity.class,idList);
    }

    /**
     * 条件查询扫描记录实例
     * @param scanRecordInstanceQuery
     * @return List <ScanRecordInstanceEntity>
     */
    public List<RecordInstanceEntity> findScanRecordInstanceList(RecordInstanceQuery scanRecordInstanceQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RecordInstanceEntity.class)
                .eq("scanRecordId",scanRecordInstanceQuery.getScanRecordId())
                .eq("projectId",scanRecordInstanceQuery.getProjectId())
                .eq("state",scanRecordInstanceQuery.getState())
                .eq("ruleType",scanRecordInstanceQuery.getRuleType())
                .eq("fileName",scanRecordInstanceQuery.getFileName())
                .eq("problemLine",scanRecordInstanceQuery.getProblemLine())
                .orders(scanRecordInstanceQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, RecordInstanceEntity.class);
    }

    /**
     * 条件分页查询扫描记录实例
     * @param scanRecordInstanceQuery
     * @return Pagination <ScanRecordInstanceEntity>
     */
    public Pagination<RecordInstanceEntity> findScanRecordInstancePage(RecordInstanceQuery scanRecordInstanceQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RecordInstanceEntity.class)
                .eq("scanRecordId",scanRecordInstanceQuery.getScanRecordId())
                .eq("projectId",scanRecordInstanceQuery.getProjectId())
                .eq("problemLevel",scanRecordInstanceQuery.getProblemLevel())
                .eq("state",scanRecordInstanceQuery.getState())
                .eq("ruleType",scanRecordInstanceQuery.getRuleType())
                .orders(scanRecordInstanceQuery.getOrderParams())
                .pagination(scanRecordInstanceQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, RecordInstanceEntity.class);
    }



    /**
     * 条件分页查询项目扫描记录
     * @param instanceQuery instanceQuery
     * @return Pagination <ScanRecordInstanceEntity>
     */
    public Pagination<RecordInstanceEntity> findProjectInstancePage(RecordInstanceQuery instanceQuery) {

        Pagination pagination = new Pagination();

        Page pageParam = instanceQuery.getPageParam();
        String projectId = instanceQuery.getProjectId();
        pagination.setCurrentPage(pageParam.getCurrentPage());
        NamedParameterJdbcTemplate jdbc = new NamedParameterJdbcTemplate(getJdbcTemplate());
        Map<String, Object> paramMap = new HashMap<String, Object>();
        paramMap.put("projectId",projectId);

        //查询数量
        String sizeSql="SELECT COUNT(DISTINCT( file_name, rule_name,problem_line,problem_level,rule_type)) AS count  FROM wair_scan_record_instance WHERE project_id=:projectId";

        String joinSql = joinSql(instanceQuery, paramMap, sizeSql);
        Integer integer = jdbc.queryForObject(joinSql, paramMap, Integer.class);
        pagination.setTotalRecord(integer);
        double result = Math.ceil(integer/pageParam.getPageSize());
        pagination.setTotalPage((int) result);


        String querySql= "SELECT file_name,rule_name,problem_line,create_time ,rule_type,problem_level,state,file_path " +
                "FROM (SELECT file_name,rule_name,problem_line,create_time,rule_type,problem_level,state,file_path," +
                " ROW_NUMBER() OVER (PARTITION BY file_name,rule_name,problem_line ORDER BY create_time DESC) AS rn" +
                " FROM wair_scan_record_instance WHERE project_id=:projectId";

        //拼接sql
        String joinedSql = joinSql(instanceQuery, paramMap, querySql);
        String lastFindSql = joinedSql + ") t " +
                "WHERE rn = 1 " +
                "ORDER BY problem_level " +
                "LIMIT :limit OFFSET :offset";

        int offset = (pageParam.getCurrentPage() - 1) * pageParam.getPageSize();
        paramMap.put("limit",pageParam.getPageSize());
        paramMap.put("offset",offset);
        List<RecordInstanceEntity> query = jdbc.query(lastFindSql, paramMap, new BeanPropertyRowMapper(RecordInstanceEntity.class));
        pagination.setDataList(query);
        return pagination;
    }

    /**
     * 条件分页查询项目扫描记录数量
     * @param instanceQuery instanceQuery
     * @return Pagination <ScanRecordInstanceEntity>
     */
    public void findProjectInstanceNum(RecordInstanceQuery instanceQuery) {



    }

    //拼接sql条件
    public String joinSql(RecordInstanceQuery instanceQuery,Map<String, Object> paramMap,String sql){
        String newSql=sql;
        if (ObjectUtils.isNotEmpty(instanceQuery.getProblemLevel())){
            newSql = newSql + " and  problem_level=:problemLevel";
            paramMap.put("problemLevel",instanceQuery.getProblemLevel());
        }
        if (ObjectUtils.isNotEmpty(instanceQuery.getRuleType())){
            newSql = newSql + " and  rule_type=:ruleType";
            paramMap.put("ruleType",instanceQuery.getRuleType());
        }
        return newSql;
    }

    public JdbcTemplate getJdbcTemplate() {

        return jpaTemplate.getJdbcTemplate();
    }

    public List<RecordInstance> findScanInstanceByCon(String value,String type) {
        NamedParameterJdbcTemplate jdbc = new NamedParameterJdbcTemplate(getJdbcTemplate());
        Map<String, Object> paramMap = new HashMap<String, Object>();
        paramMap.put(type,value);

        String sql;
        if (("recordId").equals(type)){
             sql="SELECT * FROM  wair_scan_record_instance WHERE scan_record_id=:recordId";
        }else {
            sql="SELECT * FROM  wair_scan_record_instance WHERE project_id=:"+type;
        }
        List<RecordInstance> query =jdbc.query(sql, paramMap, new BeanPropertyRowMapper(RecordInstance.class));
        return query;
    }

    public void addList(List<RecordInstance> recordInstanceList) {
        String insertSQL = "INSERT INTO wair_scan_record_instance (" +
                "id, scan_record_id, project_id, file_name, file_path, rule_type," +
                " state, problem_level, problem_line,rule_name,repair_overview," +
                "repair_desc,problem_overview,problem_desc,problem_state,import_user," +
                "import_time,create_time) " +
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?,?,?,?,?,?,?,?,?,?)";

        jpaTemplate.getJdbcTemplate().batchUpdate(insertSQL, new BatchPreparedStatementSetter() {
            @Override
            public void setValues(java.sql.PreparedStatement ps, int i) throws SQLException {
                RecordInstance instance = recordInstanceList.get(i);
                ps.setString(1, instance.getId());
                ps.setString(2, instance.getScanRecordId());
                ps.setString(3, instance.getProjectId());
                ps.setString(4, instance.getFileName());
                ps.setString(5, instance.getFilePath());
                ps.setString(6, instance.getRuleType());
                ps.setInt(7, instance.getState());
                ps.setInt(8, instance.getProblemLevel());
                ps.setInt(9, instance.getProblemLine());
                ps.setString(10, instance.getRuleName());
                ps.setString(11, instance.getRepairOverview());
                ps.setString(12, instance.getRepairDesc());
                ps.setString(13, instance.getProblemOverview());
                ps.setString(14, instance.getProblemDesc());
                ps.setString(15, instance.getProblemState());
                ps.setString(16, instance.getImportUser());
                ps.setTimestamp(17, instance.getImportTime());
                ps.setTimestamp(18, instance.getCreateTime());
            }

            @Override
            public int getBatchSize() {
                return recordInstanceList.size();
            }
        });
    }


}