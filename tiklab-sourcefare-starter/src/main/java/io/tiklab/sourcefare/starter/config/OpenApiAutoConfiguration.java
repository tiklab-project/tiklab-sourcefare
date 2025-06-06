package io.tiklab.sourcefare.starter.config;

import io.tiklab.openapi.config.AllowConfig;
import io.tiklab.openapi.config.AllowConfigBuilder;
import io.tiklab.openapi.config.OpenApiConfig;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class OpenApiAutoConfiguration {
    @Value("${soular.address:null}")
    String authAddress;

    @Value("${soular.embbed.enable:false}")
    Boolean enableEam;

    //路由
    @Bean
    OpenApiConfig openApiConfig(AllowConfig allowConfig){
        OpenApiConfig openApiConfig = new OpenApiConfig();
        openApiConfig.setAllowConfig(allowConfig);

        return openApiConfig;
    }
    //路由配置
    @Bean
    AllowConfig allowConfig(){
        String[] s =  new String[]{};

        if (enableEam){
            s = new String[]{};
        }
        return AllowConfigBuilder.instance()
                .allowUrls(s)
                .get();
    }
}
