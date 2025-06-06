package io.tiklab.sourcefare.starter.config;

import io.tiklab.eam.client.author.config.TiklabApplicationRunner;
import io.tiklab.sourcefare.common.InitializeService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/*
 * 启动项目初始化示例仓库数据
 * */
@Component()
public class InitializeData implements TiklabApplicationRunner {

    @Autowired
    InitializeService sampleService;



 /*   @Override
    public void run(ApplicationArguments args) throws Exception {
        // 在这里执行需要最后加载的操作，例如创建和初始化特定Bean
        sampleService.createSampleData();
    }
*/
    @Override
    public void run() {
        // 添加扫描规则
        sampleService.addScanRule();
    }
}
