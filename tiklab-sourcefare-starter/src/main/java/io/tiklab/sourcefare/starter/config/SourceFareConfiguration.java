package io.tiklab.sourcefare.starter.config;

import io.tiklab.dal.boot.starter.annotation.EnableDal;
import io.tiklab.dcs.boot.starter.annotation.EnableDcsClient;
import io.tiklab.dcs.boot.starter.annotation.EnableDcsServer;
import io.tiklab.dsm.boot.starter.annotation.EnableDsm;
import io.tiklab.eam.boot.starter.annotation.EnableEamClient;
import io.tiklab.eam.boot.starter.annotation.EnableEamServer;
import io.tiklab.gateway.boot.starter.annotation.EnableGateway;
import io.tiklab.install.runner.TiklabApplicationRunner;
import io.tiklab.install.spring.boot.starter.EnableInstallServer;
import io.tiklab.licence.boot.starter.annotation.EnableLicenceServer;
import io.tiklab.messsage.boot.starter.annotation.EnableMessageServer;
import io.tiklab.openapi.boot.starter.annotation.EnableOpenApi;
import io.tiklab.postgresql.spring.boot.starter.EnablePostgresql;
import io.tiklab.postin.client.openapi.ParamConfig;
import io.tiklab.postin.client.openapi.ParamConfigBuilder;
import io.tiklab.postin.client.openapi.PostInClientConfig;
import io.tiklab.privilege.boot.starter.annotation.EnablePrivilegeServer;
import io.tiklab.rpc.boot.starter.annotation.EnableRpc;
import io.tiklab.security.boot.stater.annotation.EnableSecurityServer;
import io.tiklab.sourcefare.EnableSourceFareServer;
import io.tiklab.sourcefare.project.service.InitializeService;
import io.tiklab.toolkit.boot.starter.annotation.EnableToolkit;
import io.tiklab.user.boot.starter.annotation.EnableUserClient;
import io.tiklab.user.boot.starter.annotation.EnableUserServer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.stereotype.Component;

import java.util.HashMap;


@Configuration
@EnableToolkit
//内嵌数据库
@EnablePostgresql
@EnableDal
@EnableRpc
@EnableGateway
@EnableOpenApi
@EnableDcsClient
@EnableDcsServer
@EnableDsm
//用户中心
@EnableUserServer
@EnableUserClient
@EnableInstallServer

//登录,认证
@EnableEamClient
@EnableEamServer

//消息,日志,待办
@EnableMessageServer
@EnableSecurityServer
//权限中心
@EnablePrivilegeServer
@EnableLicenceServer


@EnableSourceFareServer
@ComponentScan(value = "io.tiklab.sourcefare")
public class SourceFareConfiguration {


    @Configuration
    public class PostInClientAutoConfiguration {

        @Bean
        PostInClientConfig postInClientConfig(ParamConfig paramConfig){
            PostInClientConfig config = new PostInClientConfig();
            config.setParamConfig(paramConfig);

            return config;
        }

        @Bean
        ParamConfig paramConfig(){
            //设置请求头，属性名称：属性描述
            HashMap<String,String> headers = new HashMap<>();
            headers.put("accessToken","设置的apiKey");

            return ParamConfigBuilder.instance()
                    .setScanPackage("io.tiklab.sourcefare") //设置扫描的包路径
                    .prePath("/api")             //设置额外的前缀
                    .setHeaders(headers)               //设置请求头
                    .get();
        }

    }


    //初始化数据
    @Component()
    public class InitializeData implements TiklabApplicationRunner {

        @Autowired
        InitializeService sampleService;



      /*  *//*   @Override
           public void run(ApplicationArguments args) throws Exception {
               // 在这里执行需要最后加载的操作，例如创建和初始化特定Bean
               sampleService.createSampleData();
           }
       */
        @Override
        public void run() {

            // 初始化数据
            sampleService.initData();


            //更新仓库角色
            sampleService.updateRepRole();
        }
    }
}
