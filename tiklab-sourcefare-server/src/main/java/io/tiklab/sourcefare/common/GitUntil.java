package io.tiklab.sourcefare.common;


import com.alibaba.fastjson.JSONObject;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import org.eclipse.jgit.api.Git;
import org.eclipse.jgit.api.TransportConfigCallback;
import org.eclipse.jgit.api.errors.GitAPIException;
import org.eclipse.jgit.transport.HttpTransport;
import org.eclipse.jgit.transport.Transport;
import org.eclipse.jgit.transport.UsernamePasswordCredentialsProvider;
import org.springframework.http.ResponseEntity;
import org.springframework.web.client.RestTemplate;


import java.io.*;

import static io.tiklab.sourcefare.common.SourceFareServerFinal.*;


/**
 * git仓库操作
 */

public class GitUntil {

    /**
     *  getThreeUserInfo 获取第三方用户信息
     * @param repositoryServer repositoryServer
     */
    public static String getThreeUserInfo(RepositoryServer repositoryServer){
        if ((GITEE).equals(repositoryServer.getServerType())){
            String userPath = GITEE_USER_URL + "?access_token=" + repositoryServer.getSecretKey();
            RestTemplate restTemplate = new RestTemplate();
            ResponseEntity<JSONObject> forEntity = restTemplate.getForEntity(userPath, JSONObject.class);

            JSONObject body = forEntity.getBody();
            String account = String.valueOf(body.get("login"));
            return account;
        }

        return null;
    }

    /**
     * 克隆仓库
     * @param repositoryServer repositoryServer
     * @param branch 分支
     * @param repPath 仓库路径
     * @param cloneAddress  本地存储地址
     * @throws GitAPIException 克隆失败
     */
    public static void cloneRepository(RepositoryServer repositoryServer,String repPath, String branch, String cloneAddress) throws GitAPIException {
        String localPath = SourceFareUtil.SystemTypeAddress(cloneAddress);
        File folder = new File(localPath);
        if (!folder.exists() && !folder.isDirectory()) {
            folder.mkdirs();
        }

        String serverType = repositoryServer.getServerType();
        UsernamePasswordCredentialsProvider credentialsProvider;
        if((PRI_GITLAB).equals(serverType)){
            credentialsProvider= new UsernamePasswordCredentialsProvider("access_token", repositoryServer.getSecretKey());
        }else if((GITEE).equals(serverType)) {
            credentialsProvider= new UsernamePasswordCredentialsProvider(getThreeUserInfo(repositoryServer),repositoryServer.getSecretKey());
        }else  {
            //密码认证
            if (!("key").equals(repositoryServer.getAuthType())) {
                credentialsProvider = new UsernamePasswordCredentialsProvider(repositoryServer.getAccount(), repositoryServer.getPassWord());
            }else {
                credentialsProvider=null;
            }
        }


        Git git = Git.cloneRepository()
                .setURI(repPath)
                .setDirectory(folder)
                .setBranch(branch)
                .setCredentialsProvider(credentialsProvider)
                .setTransportConfigCallback(new TransportConfigCallback() {
                    @Override
                    public void configure(Transport transport) {
                        if (transport instanceof HttpTransport) {
                            HttpTransport httpTransport = (HttpTransport) transport;
                            httpTransport.setTimeout(10); // 设置连接超时为 10 秒
                        }
                    }
                })
                .call();
        git.close();


    }

    /**
     * 克隆所有分支的仓库
     * @param repositoryAddress 仓库地址
     * @param cloneAddress  克隆地址
     * @throws GitAPIException 克隆失败
     */
    public static void cloneAllBranchRepository(String repositoryAddress,String cloneAddress) throws GitAPIException {
        File folder = new File(cloneAddress);
        if (!folder.exists() && !folder.isDirectory()) {
            folder.mkdirs();
        }
        Git git = Git.cloneRepository()
                .setURI(repositoryAddress)
                .setDirectory(folder)
                .setCloneAllBranches(true)
                .call();
        git.close();
    }
}
