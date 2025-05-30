package io.tiklab.sourcefare.starter.config;

import io.tiklab.eam.author.Authenticator;
import io.tiklab.eam.client.author.config.AuthorConfig;
import io.tiklab.eam.client.author.config.AuthorConfigBuilder;
import io.tiklab.eam.client.author.handler.AuthorHandler;
import io.tiklab.gateway.router.Router;
import io.tiklab.gateway.router.RouterBuilder;
import io.tiklab.gateway.router.config.RouterConfig;
import io.tiklab.gateway.router.config.RouterConfigBuilder;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class GatewayFilterAutoConfiguration {

    //路由
    @Bean
    Router router(RouterConfig routerConfig){
        return RouterBuilder.newRouter(routerConfig);
    }

    //认证filter
    @Bean
    AuthorHandler authorFilter(Authenticator authenticator, AuthorConfig ignoreConfig){
        return new AuthorHandler()
                .setAuthenticator(authenticator)
                .setAuthorConfig(ignoreConfig);
    }

    @Bean
    public AuthorConfig authorConfig(){
        return AuthorConfigBuilder.instance()
                .ignoreTypes(new String[]{
                        ".ico",
                        ".jpg",
                        ".jpeg",
                        ".png",
                        ".gif",
                        ".html",
                        ".js",
                        ".css",
                        ".json",
                        ".xml",
                        ".ftl",
                        ".map",
                        ".gz",
                        "svg",
                        ".txt"
                })
                .ignoreUrls(new String[]{
                        "/",
                        "/eam/auth/login",
                        "/eam/auth/logout",
                        "/eam/auth/valid",
                        "/auth/valid",
                        "/document/view",
                        "/comment/view",
                        "/share/verifyAuthCode",
                        "/share/judgeAuthCode",
                        "/user/user/findAllUser",
                        "/user/orga/findAllOrga",
                        "/userOrga/findAllUserOrga",
                        "/dingding/passport/login",
                        "/user/dingdingcfg/findId",
                        "/dingding/passport/logout",
                        "/dingding/passport/valid",
                        "/user/wechatcfg/findWechatById",
                        "/wechat/passport/login",
                        "/wechat/passport/logout",
                        "/wechat/passport/internallogin",
                        "/wechat/passport/internalacclogin",
                        "/ldap/passport/login",
                        "/ldap/passport/logout",
                        "/version/getVersion",
                        "/licence/import",
                        "/wechatCallback/instruct",
                        "/alterSql/updateId",
                        "/gui",
                        "/gitignoreFile/createGitignoreFile",

                        "/message/messageItem/syncUpdateMessage",
                        "/message/messageItem/syncDeleteMessage",
                        "/permission/findPermissions",
                        "/RepWeb/createRepWebHook",
                        "/init/install/findStatus",
                        "/state/apply/findApply",
                        "/openapi/doc",

                        "/souecewair/handler"
                })
                .ignorePreUrls(new String[]{
                        "/service",
                        "/apis/list",
                        "/apis/detail",
                        "/file",
                        "/plugin",
                        "/authConfig",
                        "/ws",
                        "/socket",
                        "/start",
                        "/eas",
                        "/gittok",
                        "/backups",
                        "/codeScan",
                        "/message",
                        "/acceptClient"
                })
                .get();
    }


    //路由转发配置
    @Value("${soular.address:null}")
    String authAddress;

    @Value("${soular.embbed.enable:false}")
    Boolean enableEam;

    //gateway路由配置
    @Bean
    RouterConfig routerConfig(){
        String[] s = new String[]{};

        return RouterConfigBuilder.instance()
                .preRoute(s, authAddress)
                .get();
    }

}
