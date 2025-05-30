package io.tiklab.sourcefare.server.service;

import io.tiklab.core.page.Pagination;
import io.tiklab.core.page.PaginationBuilder;
import io.tiklab.sourcefare.server.dao.RepositoryServerDao;
import io.tiklab.sourcefare.server.entity.RepositoryServerEntity;
import io.tiklab.sourcefare.server.model.RepositoryServer;
import io.tiklab.sourcefare.server.model.RepositoryServerQuery;
import io.tiklab.toolkit.beans.BeanMapper;
import io.tiklab.toolkit.join.JoinTemplate;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.validation.Valid;
import javax.validation.constraints.NotNull;
import java.sql.Timestamp;
import java.util.List;

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
    public String createRepositoryServer(@NotNull @Valid RepositoryServer RepositoryServer) {

        RepositoryServerEntity RepositoryServerEntity = BeanMapper.map(RepositoryServer, RepositoryServerEntity.class);
        RepositoryServerEntity.setCreateTime(new Timestamp(System.currentTimeMillis()));

        String RepositoryServerId= RepositoryServerDao.createRepositoryServer(RepositoryServerEntity);
        return RepositoryServerId;
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

        joinTemplate.joinQuery(openRecordList);

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