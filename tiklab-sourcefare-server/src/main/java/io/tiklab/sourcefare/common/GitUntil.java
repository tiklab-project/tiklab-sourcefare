package io.tiklab.sourcefare.common;


import io.tiklab.sourcefare.server.model.RepositoryServer;
import org.eclipse.jgit.api.Git;
import org.eclipse.jgit.api.TransportConfigCallback;
import org.eclipse.jgit.api.errors.GitAPIException;
import org.eclipse.jgit.transport.HttpTransport;
import org.eclipse.jgit.transport.Transport;
import org.eclipse.jgit.transport.UsernamePasswordCredentialsProvider;


import java.io.*;



/**
 * git仓库操作
 */

public class GitUntil {


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

        UsernamePasswordCredentialsProvider credentialsProvider;
        credentialsProvider= new UsernamePasswordCredentialsProvider(repositoryServer.getAccount(),repositoryServer.getPassWord());

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
