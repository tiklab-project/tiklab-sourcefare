package io.tiklab.sourcefare.server.service;

import com.alibaba.fastjson.JSONObject;
import io.tiklab.core.exception.ApplicationException;
import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.sourcefare.common.SourceFareServerFinal;
import io.tiklab.sourcefare.common.SourceFareUtil;
import io.tiklab.sourcefare.server.dao.RepositoryServerDao;
import io.tiklab.sourcefare.server.entity.RepositoryServerEntity;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.sourcefare.server.model.RepositoryServerQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.apache.commons.lang.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;

import static io.tiklab.sourcefare.common.SourceFareServerFinal.*;

/**
* RepositoryServerServiceImpl 仓库服务
*/
@Service
public class RepositoryServerServiceImpl implements RepositoryServerService {
    private static Logger logger = LoggerFactory.getLogger(RepositoryServerServiceImpl.class);

    @Autowired
    RepositoryServerDao RepositoryServerDao;
    

    @Autowired
    JoinTemplate joinTemplate;


    @Override
    public String createRepositoryServer(@NotNull @Valid RepositoryServer server) {

        RepositoryServerEntity RepositoryServerEntity = BeanMapper.map(server, RepositoryServerEntity.class);
        RepositoryServerEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));
        if ((GITEE).equals(server.getServerType())){
            RepositoryServerEntity.setAddress(GITEE_PARH);
        }
        try {
            String path;
            switch (server.getServerType()){
                case GITEE->{
                    path=  GITEE_API_URL+"?access_token="+server.getSecretKey()+
                            "&sort=full_name&per_page=1&page=1";;
                }
                case PRI_GITLAB->{
                    String address = server.getAddress();
                    if (address.endsWith("/")){
                        address= StringUtils.substringBeforeLast(address,"/");
                    }
                    path = address + "/api/v4/projects?min_access_level=10&page=1&private_token="+server.getSecretKey();
                }
                default->{
                    path = server.getAddress()+SourceFareServerFinal.FIND_REPOSITORY_GIT_PUK;
                }
            }

            if (GIT_PUK.equals(server.getServerType())){
                ResponseEntity<JSONObject> response = SourceFareUtil.restTemplateGitPuk(server, path);
                JSONObject jsonObject = response.getBody();
                if (!("200").equals(jsonObject.get("code").toString())){
                    throw new ApplicationException(jsonObject.get("msg").toString());
                }
            }else {
              SourceFareUtil.getRestTemplate(path);
            }

            String RepositoryServerId= RepositoryServerDao.createRepositoryServer(RepositoryServerEntity);
            return RepositoryServerId;
        }catch (Exception e){
            e.printStackTrace();
            String message = e.getMessage();
            if (message.contains("timed out") ){
                throw new ApplicationException(58001,"请求超时,请检查服务地址");
            }
            if (message.contains("401 Unauthorized: Access token does not exist")){
                throw new ApplicationException("401 Unauthorized: Access token does not exist");
            }
            if (message.contains("Connection refused")){
                throw new ApplicationException("Connection refused,请检查服务地址");
            }
            if (message.contains("401 Unauthorized")){
                throw new ApplicationException("401 Unauthorized");
            }
            throw new ApplicationException("地址不正确,请检查服务地址");
        }

    }

    @Override
    public void updateRepositoryServer(@NotNull @Valid RepositoryServer RepositoryServer) {
        RepositoryServerEntity RepositoryServerEntity = BeanMapper.map(RepositoryServer, RepositoryServerEntity.class);

        RepositoryServerDao.updateRepositoryServer(RepositoryServerEntity);
    }

    @Override
    public void deleteRepositoryServer(@NotNull String id) {
        RepositoryServerDao.deleteRepositoryServer(id);
    }


    @Override
    public RepositoryServer findOne(String id) {
        RepositoryServerEntity RepositoryServerEntity = RepositoryServerDao.findRepositoryServer(id);

        RepositoryServer RepositoryServer = BeanMapper.map(RepositoryServerEntity, RepositoryServer.class);

        return RepositoryServer;
    }

    @Override
    public RepositoryServer findRepositoryServer(@NotNull String id) {
        RepositoryServer repository = findOne(id);

        joinTemplate.joinQuery(repository);

        return repository;
    }

    @Override
    public List<RepositoryServer> findList(List<String> idList) {
        List<RepositoryServerEntity> RepositoryServerEntityList =  RepositoryServerDao.findRepositoryServerList(idList);

        List<RepositoryServer> RepositoryServerList =  BeanMapper.mapList(RepositoryServerEntityList,RepositoryServer.class);

        return RepositoryServerList;
    }

    @Override
    public List<RepositoryServer> findAllRepositoryServer() {
        List<RepositoryServerEntity> RepositoryServerEntityList =  RepositoryServerDao.findAllRepositoryServer();

        List<RepositoryServer> RepositoryServerList =  BeanMapper.mapList(RepositoryServerEntityList, RepositoryServer.class);

        joinTemplate.joinQuery(RepositoryServerList);


        return RepositoryServerList;
    }


    @Override
    public Pagination<RepositoryServer> findRepositoryServerPage(RepositoryServerQuery RepositoryServerQuery) {
        Pagination<RepositoryServerEntity> RepositoryServerPage = RepositoryServerDao.findRepositoryServerPage(RepositoryServerQuery);

        List<RepositoryServer> openRecordList = BeanMapper.mapList(RepositoryServerPage.getDataList(), RepositoryServer.class);

        joinTemplate.joinQuery(openRecordList,new String[]{"user"});

        return PaginationBuilder.build(RepositoryServerPage,openRecordList);
    }

    @Override
    public List<RepositoryServer> findRepositoryServerList(RepositoryServerQuery RepositoryServerQuery) {
        List<RepositoryServerEntity> RepositoryServerEntityList= RepositoryServerDao.findRepositoryServerList(RepositoryServerQuery);

        List<RepositoryServer> RepositoryServerList = BeanMapper.mapList(RepositoryServerEntityList, RepositoryServer.class);

        joinTemplate.joinQuery(RepositoryServerList);

        return RepositoryServerList;
    }


}