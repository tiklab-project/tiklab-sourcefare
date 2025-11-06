package io.tiklab.sourcefare.server.service;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import io.tiklab.core.exception.ApplicationException;
import io.tiklab.core.exception.SystemException;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.common.SourceFareServerFinal;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.sourcefare.server.model.RepositoryServerQuery;
import io.tiklab.sourcefare.server.model.ThirdBranch;
import io.tiklab.sourcefare.server.model.ThirdRepository;
import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.http.client.ClientHttpRequestFactory;
import org.springframework.http.client.SimpleClientHttpRequestFactory;
import org.springframework.stereotype.Service;
import org.springframework.util.CollectionUtils;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.util.ObjectUtils;
import org.springframework.web.client.RestTemplate;

import java.util.*;

import static io.tiklab.sourcefare.common.SourceFareServerFinal.*;

@Service
public class ServerGitPukServiceImpl implements ServerGitPukService {
    private static Logger logger = LoggerFactory.getLogger(ServerGitPukServiceImpl.class);

    @Autowired
    RepositoryServerService repositoryServerService;

    @Override
    public List<ThirdRepository> findRepositoryList(RepositoryServer repositoryServer) {

        List<ThirdRepository> gitPukRepo;
        switch (repositoryServer.getServerType()){

            case GITEE->{
                gitPukRepo = findGitEeRepo(repositoryServer);
            }
            case PRI_GITLAB->{
                gitPukRepo = findGitLabRepo(repositoryServer);
            }
            default->{
                gitPukRepo = findGitPukRepo(repositoryServer);
            }
        }
        return gitPukRepo;
    }

    @Override
    public List<ThirdBranch> findRepositoryBranchList(RepositoryServerQuery serverQuery) {
        RepositoryServer repositoryServer = repositoryServerService.findRepositoryServer(serverQuery.getRepServerId());


        List<ThirdBranch> branchList;
        switch (repositoryServer.getServerType()){
            case GITEE->{
                branchList = findGitEeBranch(serverQuery,repositoryServer.getSecretKey());
            }
            case PRI_GITLAB->{
                branchList = findGitLabBranch(serverQuery,repositoryServer);
            }
            default->{
                branchList = findGitPukBranch(serverQuery,repositoryServer.getAddress());
            }
        }
        return branchList;
    }


    /**
     * 查询gitEe仓库
     * @param server server
     */
    public List<ThirdRepository> findGitEeRepo(RepositoryServer server){
        List<ThirdRepository> houseList = new ArrayList<>();
        String path=  GITEE_API_URL+"?access_token="+server.getSecretKey()+
                "&sort=full_name&per_page=20&page=1";

        if (StringUtils.isNotEmpty(server.getRepName())){
            path=path+"&q="+server.getRepName();
        }
        //RestTemplate 调用接口
        ResponseEntity<List> restTemplate = SourceFareUtil.getRestTemplate(path);
        if (restTemplate.getStatusCode().value()==200){
            //仓库列表数据
            List body = restTemplate.getBody();
            if (!CollectionUtils.isEmpty(body)){
                for (Object value:body){
                    //拼接结果
                    ThirdRepository thirdRepository = new ThirdRepository();

                    JSONObject jsonObject = (JSONObject) JSON.toJSON(value);
                    thirdRepository.setId(jsonObject.get("id").toString());
                    String repoName = jsonObject.get("name").toString();
                    thirdRepository.setName(repoName);

                    //仓库组名字
                    JSONObject namespace = (JSONObject) jsonObject.get("namespace");
                    String groupName = namespace.get("path").toString();

                    String pathSpace = namespace.get("path").toString();
                    thirdRepository.setNameWithSpace(pathSpace);

                    thirdRepository.setPathWithSpace(groupName+"/"+repoName);

                    //默认分支
                    Object branch = jsonObject.get("default_branch");
                    if (!ObjectUtils.isEmpty(branch)){
                        thirdRepository.setDefaultBranch(branch.toString());
                    }


                    //仓库路径
                    Object htmlUrl = jsonObject.get("html_url");
                    thirdRepository.setHouseWebUrl(htmlUrl.toString());
                    Object sshUrl = jsonObject.get("ssh_url");
                    thirdRepository.setHouseSshUrl(sshUrl.toString());

                    houseList.add(thirdRepository);
                }
            }
        }
        return houseList;
    }

    /**
     * 查询gitLab仓库
     * @param repositoryServer repositoryServer
     */
    public List<ThirdRepository> findGitLabRepo(RepositoryServer repositoryServer){
        List<ThirdRepository> houseList = new ArrayList<>();

        String address = repositoryServer.getAddress();
        if (address.endsWith("/")){
            address= StringUtils.substringBeforeLast(address,"/");
        }
        String s = address + "/api/v4/projects";

        // owned=true 自己创建的; simple=true 获取简化的数据
        String path=  s+"?min_access_level=10&page=1&private_token="+repositoryServer.getSecretKey();
        //RestTemplate 调用接口
        ResponseEntity<List> restTemplate =SourceFareUtil.getRestTemplate(path);
        if (restTemplate.getStatusCode().value()==200){
            //仓库列表数据
            List body = restTemplate.getBody();

            if (!CollectionUtils.isEmpty(body)){
                for (Object value:body){
                    //拼接结果
                    ThirdRepository thirdRepository = new ThirdRepository();
                    JSONObject jsonObject = (JSONObject) JSON.toJSON(value);

                    thirdRepository.setId(jsonObject.get("id").toString());

                    String repoName = jsonObject.get("name").toString();
                    thirdRepository.setName(repoName);
                    //仓库组/仓库名字
                    thirdRepository.setPathWithSpace(jsonObject.get("path_with_namespace").toString());

                    //仓库组名字
                    JSONObject namespace = (JSONObject) jsonObject.get("namespace");
                    String groupName = namespace.get("name").toString();
                    thirdRepository.setNameWithSpace(groupName);

                    String pathSpace = namespace.get("path").toString();
                    thirdRepository.setPathWithSpace(pathSpace+"/"+repoName);

                    //仓库路径
                    Object urlToRepo = jsonObject.get("http_url_to_repo");
                    thirdRepository.setHouseWebUrl(urlToRepo.toString());
                    Object sshPath =  jsonObject.get("ssh_url_to_repo");
                    thirdRepository.setHouseSshUrl(sshPath.toString());

                    ///默认分支
                    Object defaultBranch =  jsonObject.get("default_branch");
                    if (!ObjectUtils.isEmpty(defaultBranch)){
                        thirdRepository.setDefaultBranch(defaultBranch.toString());
                    }

                    houseList.add(thirdRepository);
                }}
        }
        return houseList;
    }

    /**
     * 查询gitPuk仓库
     * @param repositoryServer repositoryServer
     */
    public List<ThirdRepository> findGitPukRepo(RepositoryServer repositoryServer){

        String serverAddress = repositoryServer.getAddress();
        try {
            //查询仓库地址
            String findPath = serverAddress + SourceFareServerFinal.FIND_REPOSITORY_GIT_PUK;
            ResponseEntity<JSONObject> response = SourceFareUtil.restTemplateGitPuk(repositoryServer, findPath);
            JSONObject jsonObject = response.getBody();
            JSONArray jsonArray = validBody(jsonObject, JSONArray.class);
            List<ThirdRepository> houseList = new ArrayList<>();

            for (Object o : jsonArray) {
                JSONObject parseObject = JSONObject.parseObject(String.valueOf(o));
                ThirdRepository thirdHouse = joinGitPukRepoData(parseObject);
                houseList.add(thirdHouse);
            }



            return houseList;

        }catch (Throwable throwable){
            String message = throwable.getMessage();
            logger.error(" 连接异常：{}", message);
            if (message.contains("timed out") ){
                throw new ApplicationException(58001,"请求超时！");
            }
            if (throwable instanceof ApplicationException){
                throw new ApplicationException(message);
            }
            throw new ApplicationException("无法连接到：" + serverAddress);
        }
    }



    public List<ThirdBranch> findGitEeBranch(RepositoryServerQuery serverQuery,String accessToken){
        List<ThirdBranch> branchList = new ArrayList<>();

        String path = GITEE_BRANCH_API_URL + serverQuery.getOwner() + "/" + serverQuery.getRepo()+"/branches";
        String s = path + "?access_token=" + accessToken+"&direction=asc&page=1";
        //RestTemplate 调用接口
        ResponseEntity<List> restTemplate =SourceFareUtil.getRestTemplate(s);
        if (restTemplate.getStatusCode().value()==200){
            //仓库列表数据
            List body = restTemplate.getBody();
            if (!CollectionUtils.isEmpty(body)){
                for (int a = 0; a < body.size(); a++) {
                    Object value = body.get(a);
                    JSONObject jsonObject = (JSONObject) JSON.toJSON(value);

                    ThirdBranch thirdBranch = new ThirdBranch();

                    thirdBranch.setId(jsonObject.get("name").toString());

                    boolean b=a==0?true:false;
                    thirdBranch.setDefault(b);
                    thirdBranch.setName(jsonObject.get("name").toString());
                    branchList.add(thirdBranch);
                }
            }
        }
        return branchList;
    }
    /**
     * 查询gitLab仓库的分支
     * @param serverQuery serverQuery
     */
    public List<ThirdBranch> findGitLabBranch(RepositoryServerQuery serverQuery, RepositoryServer repositoryServer){
        List<ThirdBranch> branchList = new ArrayList<>();

        String address = repositoryServer.getAddress();
        if (!address.endsWith("/")){
            address=address+"/";
        }
        String s = address + "api/v4/projects/" + serverQuery.getRepo() + "/repository/branches?min_access_level=10&page=1&private_token=" + repositoryServer.getSecretKey();
        //RestTemplate 调用接口
        ResponseEntity<List> restTemplate =SourceFareUtil.getRestTemplate(s);
        if (restTemplate.getStatusCode().value()==200){
            //仓库列表数据
            List body = restTemplate.getBody();

            if (!CollectionUtils.isEmpty(body)){
                for (Object value:body) {
                    JSONObject jsonObject = (JSONObject) JSON.toJSON(value);

                    ThirdBranch thirdBranch = new ThirdBranch();
                    thirdBranch.setId(jsonObject.get("name").toString());
                    thirdBranch.setName(jsonObject.get("name").toString());

                    String aDefault = jsonObject.get("default").toString();
                    boolean check = aDefault.equals("false") ? false : true;
                    thirdBranch.setDefault(check);
                    branchList.add(thirdBranch);
                }
            }}
        return branchList;
    }

    /**
     * 查询gitPuk仓库的分支
     * @param serverQuery serverQuery
     * @param serverAddress 服务地址
     */
    public List<ThirdBranch> findGitPukBranch(RepositoryServerQuery serverQuery,String serverAddress){
        try {
            //查询仓库地址
            String findPath = serverAddress + SourceFareServerFinal.FIND_REPOSITORY_BRANCH_GIT_PUK;


            Map<String, String> hashMap = new HashMap<>();
            hashMap.put("accessToken", SourceFareServerFinal.ACCESS_TOKEN);

            // 创建请求头对象
            HttpHeaders headers = SourceFareUtil.initHeaders(MediaType.APPLICATION_JSON, hashMap);

            // 请求参数
            MultiValueMap<String, Object> valueMap = new LinkedMultiValueMap<>();
            valueMap.add("rpyId",serverQuery.getRepo());
            // 创建 HttpEntity 包含请求体和请求头
            HttpEntity<MultiValueMap<String, Object>> requestEntity = new HttpEntity<>(valueMap, headers);

            //设置连接超时时间
            ClientHttpRequestFactory factory = new SimpleClientHttpRequestFactory();
            ((SimpleClientHttpRequestFactory) factory).setConnectTimeout(10000);
            RestTemplate restTemplate = new RestTemplate(factory);

            ResponseEntity<JSONObject> response = restTemplate.exchange(findPath, HttpMethod.POST, requestEntity, JSONObject.class);
            JSONObject jsonObject = response.getBody();
            JSONArray jsonArray = validBody(jsonObject, JSONArray.class);

            List<ThirdBranch> branchList = new ArrayList<>();
            for (Object o : jsonArray) {
                JSONObject parseObject = JSONObject.parseObject(String.valueOf(o));
                ThirdBranch thirdBranch = bindBranch(parseObject);
                branchList.add(thirdBranch);
            }
            return branchList;
        }catch (Throwable throwable){
            String message = throwable.getMessage();
            logger.error(" 连接异常：{}", message);
            if (message.contains("timed out") ){
                throw new ApplicationException(58001,"请求超时！");
            }
            if (throwable instanceof ApplicationException){
                throw new ApplicationException(message);
            }
            throw new ApplicationException("无法连接到：" + serverAddress);
        }
    }


    /**
     * 拼接仓库数据
     * @param jsonObject jsonObject
     */
    private ThirdRepository joinGitPukRepoData(JSONObject jsonObject){
        if (Objects.isNull(jsonObject)){
            return null;
        }
        String id = jsonObject.getString("rpyId");
        String fullPath = jsonObject.getString("fullPath");
        String path = jsonObject.getString("address");
        String defaultBranch = jsonObject.getString("defaultBranch");
        String name = jsonObject.getString("name");
        return new ThirdRepository().setId(id)
                .setHouseWebUrl(fullPath)
                .setNameWithSpace(name)
                .setPathWithSpace(path)
                .setName(name)
                .setDefaultBranch(defaultBranch);
    }

    private ThirdBranch bindBranch(JSONObject jsonObject){
        if (Objects.isNull(jsonObject)){
            return null;
        }

        Boolean defaultBranch = jsonObject.getBoolean("defaultBranch");
        String branchName = jsonObject.getString("branchName");

        return new ThirdBranch().
                setId(branchName)
                .setDefault(defaultBranch)
                .setName(branchName);
    }

    private <T> T validBody(JSONObject jsonObject,Class<T> tClass){
        if (Objects.isNull( jsonObject)){
            throw new SystemException("获取返回值为空！");
        }
        Integer code = jsonObject.getInteger("code");
        if (code != 0){
            String msg = jsonObject.getString("msg");
            if (code == 5000){
                throw new ApplicationException("用户效验失败！");
            }
            throw new ApplicationException("获取仓库列表失败！,Message："+msg);
        }
        return jsonObject.getObject("data",tClass);
    }
}
