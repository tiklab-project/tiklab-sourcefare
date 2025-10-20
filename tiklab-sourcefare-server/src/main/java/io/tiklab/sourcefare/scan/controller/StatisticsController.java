package io.tiklab.sourcefare.scan.controller;

import io.tiklab.core.Result;
import io.tiklab.postin.annotation.Api;
import io.tiklab.postin.annotation.ApiMethod;
import io.tiklab.postin.annotation.ApiParam;
import io.tiklab.sourcefare.scan.model.ScanRecord;
import io.tiklab.sourcefare.scan.model.ScanSchemeRuleSet;
import io.tiklab.sourcefare.scan.model.StatisticsQuery;
import io.tiklab.sourcefare.scan.service.OverviewService;
import io.tiklab.sourcefare.scan.service.StatisticsService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;

@RestController
@RequestMapping("/statistics")
//@Api(name = "StatisticsController",desc = "统计")
public class StatisticsController {

    @Autowired
    StatisticsService statisticsService;


    @RequestMapping(path="/issueStat",method = RequestMethod.POST)
    @ApiMethod(name = "issueStat",desc = "问题统计")
    @ApiParam(name = "statisticsQuery",desc = "statisticsQuery",required = true)
    public Result<Object> issueStat(@RequestBody @Valid @NotNull StatisticsQuery statisticsQuery){
        Object scanRecord = statisticsService.issueStat(statisticsQuery);

        return Result.ok(scanRecord);
    }

    @RequestMapping(path="/duplicatedStat",method = RequestMethod.POST)
    @ApiMethod(name = "duplicatedStat",desc = "重复率统计")
    @ApiParam(name = "statisticsQuery",desc = "statisticsQuery",required = true)
    public Result<Object> duplicatedStat(@RequestBody @Valid @NotNull StatisticsQuery statisticsQuery){
        Object scanRecord = statisticsService.duplicatedStat(statisticsQuery);

        return Result.ok(scanRecord);
    }

    @RequestMapping(path="/complexityStat",method = RequestMethod.POST)
    @ApiMethod(name = "complexityStat",desc = "复杂度统计")
    @ApiParam(name = "statisticsQuery",desc = "statisticsQuery",required = true)
    public Result<Object> complexityStat(@RequestBody @Valid @NotNull StatisticsQuery statisticsQuery){
        Object scanRecord = statisticsService.complexityStat(statisticsQuery);

        return Result.ok(scanRecord);
    }

    @RequestMapping(path="/coverStat",method = RequestMethod.POST)
    @ApiMethod(name = "coverStat",desc = "覆盖率统计")
    @ApiParam(name = "statisticsQuery",desc = "statisticsQuery",required = true)
    public Result<Object> coverStat(@RequestBody @Valid @NotNull StatisticsQuery statisticsQuery){
        Object scanRecord = statisticsService.coverStat(statisticsQuery);

        return Result.ok(scanRecord);
    }
}
