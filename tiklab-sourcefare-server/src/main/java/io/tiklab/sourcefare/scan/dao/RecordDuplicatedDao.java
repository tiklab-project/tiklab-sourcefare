package io.tiklab.sourcefare.scan.dao;

import io.tiklab.core.page.Pagination;
import io.tiklab.dal.jpa.JpaTemplate;
import io.tiklab.dal.jpa.criterial.condition.DeleteCondition;
import io.tiklab.dal.jpa.criterial.condition.QueryCondition;
import io.tiklab.dal.jpa.criterial.conditionbuilder.QueryBuilders;
import io.tiklab.sourcefare.scan.entity.RecordDuplicatedEntity;
import io.tiklab.sourcefare.scan.model.RecordDuplicated;
import io.tiklab.sourcefare.scan.model.RecordDuplicatedQuery;
import io.tiklab.sourcefare.scan.model.RecordInstance;
import io.tiklab.sourcefare.scan.model.ScanRule;
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
 * RecordDuplicatedDao-项目扫描记录的重复度
 */
@Repository
public class RecordDuplicatedDao {

    private static Logger logger = LoggerFactory.getLogger(RecordDuplicatedDao.class);

    @Autowired
    JpaTemplate jpaTemplate;

    /**
     * 创建
     * @param recordDuplicatedEntity
     * @return
     */
    public String createRecordDuplicated(RecordDuplicatedEntity recordDuplicatedEntity) {
        return jpaTemplate.save(recordDuplicatedEntity,String.class);
    }



    /**
     * 更新
     * @param recordDuplicatedEntity
     */
    public void updateRecordDuplicated(RecordDuplicatedEntity recordDuplicatedEntity){
        jpaTemplate.update(recordDuplicatedEntity);
    }

    /**
     * 删除
     * @param id
     */
    public void deleteRecordDuplicated(String id){
        jpaTemplate.delete(RecordDuplicatedEntity.class,id);
    }

    /**
     * 条件删除项目扫描记录的重复度
     * @param deleteCondition
     */
    public void deleteRecordDuplicated(DeleteCondition deleteCondition){
        jpaTemplate.delete(deleteCondition);
    }

    /**
     * 查找
     * @param id
     * @return
     */
    public RecordDuplicatedEntity findRecordDuplicated(String id){
        return jpaTemplate.findOne(RecordDuplicatedEntity.class,id);
    }

    /**
    * 查询所有项目扫描记录的重复度
    * @return
    */
    public List<RecordDuplicatedEntity> findAllRecordDuplicated() {
        return jpaTemplate.findAll(RecordDuplicatedEntity.class);
    }

    /**
     * 通过ids项目扫描记录的重复度
     * @param idList
     * @return List <RecordDuplicatedEntity>
     */
    public List<RecordDuplicatedEntity> findRecordDuplicatedList(List<String> idList) {
        return jpaTemplate.findList(RecordDuplicatedEntity.class,idList);
    }

    /**
     * 条件查询项目扫描记录的重复度
     * @param coverQuery
     * @return List <RecordDuplicatedEntity>
     */
    public List<RecordDuplicatedEntity> findRecordDuplicatedList(RecordDuplicatedQuery coverQuery) {
        QueryCondition queryCondition = QueryBuilders.createQuery(RecordDuplicatedEntity.class)
                .eq("recordId",coverQuery.getScanRecordId())
                .eq("projectId",coverQuery.getProjectId())
                .eq("path",coverQuery.getPath())
                .orders(coverQuery.getOrderParams())
                .get();
        return jpaTemplate.findList(queryCondition, RecordDuplicatedEntity.class);
    }

    /**
     * 条件分页查询项目扫描记录的重复度
     * @param coverQuery
     * @return Pagination <RecordDuplicatedEntity>
     */
    public Pagination<RecordDuplicatedEntity> findRecordDuplicatedPage(RecordDuplicatedQuery coverQuery) {
        QueryCondition queryCondition =QueryBuilders.createQuery(RecordDuplicatedEntity.class)
                .eq("recordId", coverQuery.getScanRecordId())
                .eq("projectId", coverQuery.getProjectId())
                .eq("path",coverQuery.getPath())
                .pagination(coverQuery.getPageParam())
                .get();
        return jpaTemplate.findPage(queryCondition, RecordDuplicatedEntity.class);
    }


    public void createRecordDuplicated(List<RecordDuplicated> recordDuplicated) {

        String insertSQL = "INSERT INTO wair_scan_record_duplicated (" +
                "id, project_id, record_id, path, start_line, end_line, lines, grouping, create_time) " +
                "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)";
        jpaTemplate.getJdbcTemplate().batchUpdate(insertSQL, new BatchPreparedStatementSetter() {
            @Override
            public void setValues(java.sql.PreparedStatement ps, int i) throws SQLException {
                RecordDuplicated duplicated = recordDuplicated.get(i);
                ps.setString(1, duplicated.getId());
                ps.setString(2, duplicated.getProjectId());
                ps.setString(3, duplicated.getRecordId());
                ps.setString(4, duplicated.getPath());
                ps.setInt(5, duplicated.getStartLine());
                ps.setInt(6, duplicated.getEndLine());
                ps.setInt(7, duplicated.getLines());
                ps.setString(8, duplicated.getGroup());
                ps.setTimestamp(9, duplicated.getCreateTime());
            }

            @Override
            public int getBatchSize() {
                return recordDuplicated.size();
            }
        });
    }


    public List<RecordDuplicated> findRecordDuplicatedByCon(String value,String type) {
        NamedParameterJdbcTemplate jdbc = new NamedParameterJdbcTemplate(getJdbcTemplate());
        Map<String, Object> paramMap = new HashMap<String, Object>();
        paramMap.put(type,value);

        String sql;
        if (("recordId").equals(type)){
             sql="SELECT * FROM  wair_scan_record_duplicated WHERE record_id=:"+type;
        }else {
             sql="SELECT * FROM  wair_scan_record_duplicated WHERE project_id=:"+type;
        }

        List<RecordDuplicated> query =jdbc.query(sql, paramMap, new BeanPropertyRowMapper(RecordDuplicated.class));
        return query;

    }

    public JdbcTemplate getJdbcTemplate() {

        return jpaTemplate.getJdbcTemplate();
    }
}