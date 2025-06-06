package io.tiklab.sourcefare.server.service;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import io.tiklab.core.exception.ApplicationException;
import io.tiklab.core.exception.SystemException;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.common.SourceWairServerFinal;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.sourcefare.server.model.ThirdBranch;
import io.tiklab.sourcefare.server.model.ThirdRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.*;
import org.springframework.http.client.ClientHttpRequestFactory;
import org.springframework.http.client.SimpleClientHttpRequestFactory;
import org.springframework.stereotype.Service;
import org.springframework.util.LinkedMultiValueMap;
import org.springframework.util.MultiValueMap;
import org.springframework.web.client.RestTemplate;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Objects;

@Service
public class ServerGitPukServiceImpl implements ServerGitPukService {
    private static Logger logger = LoggerFactory.getLogger(ServerGitPukServiceImpl.class);

    @Autowired
    RepositoryServerService repositoryServerService;

    @Override
    public List<ThirdRepository> findRepositoryList(RepositoryServer repositoryServer) {
        String serverAddress = repositoryServer.getAddress();

        try {
            //查询仓库地址
            String findPath = serverAddress + SourceWairServerFinal.FIND_REPOSITORY_GIT_PUK;

            // 创建请求头对象
            HttpHeaders headers = SourceFareUtil.initHeaders(MediaType.APPLICATION_JSON, new HashMap<>());

            // 请求参数
            MultiValueMap<String, Object> valueMap = new LinkedMultiValueMap<>();
            valueMap.add("account",repositoryServer.getAccount());
            valueMap.add("password",repositoryServer.getPassWord());
            valueMap.add("dirId","1");

            // 创建 HttpEntity 包含请求体和请求头
            HttpEntity<MultiValueMap<String, Object>> requestEntity = new HttpEntity<>(valueMap, headers);

            //设置连接超时时间
            ClientHttpRequestFactory factory = new SimpleClientHttpRequestFactory();
            ((SimpleClientHttpRequestFactory) factory).setConnectTimeout(10000);
            RestTemplate restTemplate = new RestTemplate(factory);

            ResponseEntity<JSONObject> response = restTemplate.exchange(findPath, HttpMethod.POST, requestEntity, JSONObject.class);
            JSONObject jsonObject = response.getBody();
            JSONArray jsonArray = validBody(jsonObject, JSONArray.class);
            List<ThirdRepository> houseList = new ArrayList<>();

            for (Object o : jsonArray) {
                JSONObject parseObject = JSONObject.parseObject(String.valueOf(o));
                ThirdRepository thirdHouse = bindHouse(parseObject);
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

    @Override
    public List<ThirdBranch> findRepositoryBranchList(String repId, String repServerId) {
        RepositoryServer repositoryServer = repositoryServerService.findRepositoryServer(repServerId);
        String serverAddress = repositoryServer.getAddress();

        try {
            //查询仓库地址
            String findPath = serverAddress + SourceWairServerFinal.FIND_REPOSITORY_BRANCH_GIT_PUK;

            // 创建请求头对象
            HttpHeaders headers = SourceFareUtil.initHeaders(MediaType.APPLICATION_JSON, new HashMap<>());

            // 请求参数
            MultiValueMap<String, Object> valueMap = new LinkedMultiValueMap<>();
            valueMap.add("rpyId",repId);
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

    private ThirdRepository bindHouse(JSONObject jsonObject){
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
        String id = jsonObject.getString("branchId");
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
