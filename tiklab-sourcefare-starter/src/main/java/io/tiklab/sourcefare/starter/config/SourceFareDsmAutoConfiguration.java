package io.tiklab.sourcefare.starter.config;


import io.tiklab.dsm.model.DsmConfig;
import io.tiklab.dsm.model.DsmVersion;
import io.tiklab.dsm.support.DsmVersionBuilder;
import io.tiklab.sourcefare.project.service.InitAuthority;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;

@Component
public class SourceFareDsmAutoConfiguration {

    @Autowired
    InitAuthority initAuthority;

    @Bean
    DsmConfig dsmConfig(){
        DsmConfig dsmConfig = new DsmConfig();

        dsmConfig.setVersionList(versionList());
        return dsmConfig;
    }

    /**
     * 初始化Dsm版本列表
     * @return
     */
    List<DsmVersion> versionList() {
        List<DsmVersion> versionList = new ArrayList<>();
        DsmVersion dsmVersion = DsmVersionBuilder.instance()
                .version("1.0.0")
                .db(new String[]{
                        "user_1.0.0",
                        //PrivilegeDsm
                        "privilege_1.0.0",
                        //LicenceDsm
                        "app-authorization_1.0.0",
                        //MessageDsm
                        "message_1.0.0",
                        //SecurityDsm
                        "oplog_1.0.0",
                        //TodoTaskDsm
                        "todotask_1.0.0",
                        "openapi_1.0.0",

                        "scan_1.0.0",
                        "scan-message_1.0.0",
                        "scan-role_1.0.0",
                }).get();
        versionList.add(dsmVersion);

        dsmVersion = DsmVersionBuilder.instance()
                .version("1.0.1")
                .db(new String[]{
                        "scan_1.0.1",
                }).get();
        versionList.add(dsmVersion);

        dsmVersion = DsmVersionBuilder.instance()
                .version("1.2.0")
                .db(new String[]{
                        "scan_1.0.2"
                }).get();
        versionList.add(dsmVersion);
        dsmVersion = DsmVersionBuilder.instance()
                .version("1.2.2")
                .db(new String[]{
                        "scan_1.0.4"
                }).get();
        versionList.add(dsmVersion);
        dsmVersion = DsmVersionBuilder.instance()
                .version("1.2.3")
                .db(new String[]{
                        "scan_1.0.5"
                }).get();
        versionList.add(dsmVersion);
        dsmVersion = DsmVersionBuilder.instance()
                .version("1.2.4")
                .db(new String[]{
                        "scan_1.0.6"
                }).get();
        versionList.add(dsmVersion);
        dsmVersion = DsmVersionBuilder.instance()
                .version("1.2.5")
                .db(new String[]{
                        "scan_1.0.7"
                }).get();
        versionList.add(dsmVersion);
        dsmVersion = DsmVersionBuilder.instance()
                .version("1.2.8")
                .db(new String[]{
                        "scan_1.0.8"
                }).get();
        versionList.add(dsmVersion);
        dsmVersion = DsmVersionBuilder.instance()
                .version("1.2.9")
                .db(new String[]{
                        "scan_1.0.9"
                }).get();
        versionList.add(dsmVersion);
        dsmVersion = DsmVersionBuilder.instance()
                .version("1.3.0")
                .db(new String[]{
                        "scan_1.1.0"
                }).get();
        versionList.add(dsmVersion);
        dsmVersion = DsmVersionBuilder.instance()
                .version("1.3.1")
                .db(new String[]{
                        "scan_1.1.1"
                }).get();
        versionList.add(dsmVersion);



        dsmVersion = DsmVersionBuilder.instance()
                .version("user_2.0.0")
                .db(new String[]{
                        "user_2.0.0",
                        "user_2.0.1",
                }).get();
        versionList.add(dsmVersion);

        DsmVersion message_109 = DsmVersionBuilder.instance()
                .version("message_1.0.9")
                .db(new String[]{
                        "message_1.0.9",
                }).get();
        versionList.add(message_109);

        dsmVersion = DsmVersionBuilder.instance()
                .version("prvilege_plat")
                .db(new String[]{
                        "privilege-gorup_1.0.0",
                        "prvilege-system_1.0.0",
                        "prvilege-project_1.0.0",
                })
                .task(initAuthority)
                .get();
        versionList.add(dsmVersion);

        dsmVersion = DsmVersionBuilder.instance()
                .version("message_2.0.0")
                .db(new String[]{
                        "message_2.0.0",
                }).get();
        versionList.add(dsmVersion);

        dsmVersion = DsmVersionBuilder.instance()
                .version("prvilege_source")
                .db(new String[]{
                        "source_prvilege-project_1.0.0",
                        "source_prvilege-system_1.0.0",
                        "licence_2.0.0",
                })
                .task(initAuthority)
                .get();
        versionList.add(dsmVersion);

        dsmVersion = DsmVersionBuilder.instance()
                .version("licence_2.0.0")
                .db(new String[]{
                        "licence_2.0.0",
                })
                .get();
        versionList.add(dsmVersion);
        return versionList;
    }
}
