package io.tiklab.sourcefare.scan.service;


import io.tiklab.core.page.Pagination;
import io.tiklab.sourcefare.scan.model.IssueStatistic;
import io.tiklab.sourcefare.scan.model.IssueStatisticQuery;
import io.tiklab.sourcefare.scan.model.ProjectCover;
import io.tiklab.sourcefare.scan.model.ProjectCoverQuery;
import io.tiklab.toolkit.join.annotation.FindAll;
import io.tiklab.toolkit.join.annotation.FindList;
import io.tiklab.toolkit.join.annotation.FindOne;
import io.tiklab.toolkit.join.annotation.JoinProvider;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.util.List;

/**
* IssueStatisticService-问题统计
*/
@JoinProvider(model = IssueStatistic.class)
public interface IssueStatisticService {

    /**
    * 创建
    * @param issueStatistic
    * @return
    */
    String createIssueStatistic(@NotNull @Valid IssueStatistic issueStatistic);

    /**
     * 创建
     * @param issueStatistic
     * @return
     */
    void createIssueStatistic(List<IssueStatistic> issueStatistic);

    /**
    * 更新
    * @param issueStatistic
    */
    void updateIssueStatistic(@NotNull @Valid IssueStatistic issueStatistic);

    /**
    * 删除
    * @param id
    */
    void deleteIssueStatistic(@NotNull String id);

    /**
     * 条件删除扫描结果
     * @param  key  删除条件字段
     * @param value
     */
    void deleteIssueStatisticByCondition(@NotNull String key,@NotNull String value);

    @FindOne
    IssueStatistic findOne(@NotNull String id);

    @FindList
    List<IssueStatistic> findList(List<String> idList);

    /**
    * 查找
    * @param id
    * @return
    */

    IssueStatistic findIssueStatistic(@NotNull String id);

    /**
    * 查找所有
    * @return
    */
    @FindAll
    List<IssueStatistic> findAllIssueStatistic();

    /**
    * 查询列表
    * @param issueStatisticQuery
    * @return
    */
    List<IssueStatistic> findIssueStatisticList(IssueStatisticQuery issueStatisticQuery);

    /**
     * 按分页查询
     * @param issueStatisticQuery issueStatisticQuery
     */
    Pagination<IssueStatistic> findIssueStatisticPage(IssueStatisticQuery issueStatisticQuery);

    /**
     * 条件查询问题统计类型的数量
     * @param issueStatisticQuery issueStatisticQuery
     */
    Object findIssueStatisticCount(IssueStatisticQuery issueStatisticQuery);


    /**
     * 条件查询问题统计类型的数量
     * @param recordId 扫描记录的id
     */
    Object findIssueTypeStatisticCount(String recordId);
}