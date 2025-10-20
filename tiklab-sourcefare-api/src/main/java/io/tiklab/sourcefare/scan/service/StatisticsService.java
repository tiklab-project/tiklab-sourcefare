package io.tiklab.sourcefare.scan.service;

import io.tiklab.sourcefare.scan.model.StatisticsQuery;

public interface StatisticsService {

    /**
     * 问题统计
     * @param statisticsQuery
     */
    Object issueStat(StatisticsQuery statisticsQuery);

    /**
     * 重复率统计
     * @param statisticsQuery
     */
    Object duplicatedStat(StatisticsQuery statisticsQuery);

    /**
     * 复杂度统计
     * @param statisticsQuery
     */
    Object complexityStat(StatisticsQuery statisticsQuery);

    /**
     * 复杂度统计
     * @param statisticsQuery statisticsQuery
     */
    Object coverStat(StatisticsQuery statisticsQuery);
}
