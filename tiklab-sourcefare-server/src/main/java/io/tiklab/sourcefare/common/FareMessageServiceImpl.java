package io.tiklab.sourcefare.common;

import com.alibaba.fastjson.JSONObject;
import io.tiklab.eam.common.context.LoginContext;
import io.tiklab.message.message.model.SendMessageNotice;
import io.tiklab.message.message.service.SendMessageNoticeService;
import io.tiklab.security.logging.logging.model.Logging;
import io.tiklab.security.logging.logging.model.LoggingType;
import io.tiklab.security.logging.logging.service.LoggingByTempService;
import io.tiklab.sourcefare.project.model.Project;
import io.tiklab.sourcefare.scanner.common.ProjectUtil;
import io.tiklab.sourcefare.scanner.common.SourceFareFinal;
import io.tiklab.user.user.model.User;
import io.tiklab.user.user.service.UserProcessor;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.util.ObjectUtils;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

@Service
public class FareMessageServiceImpl implements FareMessageService  {

    @Value("${base.url:null}")
    String baseUrl;

    @Autowired
    SendMessageNoticeService dispatchNoticeService;

    @Autowired
    LoggingByTempService logService;

    @Autowired
    UserProcessor userProcessor;



    @Override
    public void deployMessage(Map<String, Object> map, String templateId ) {
        SendMessageNotice dispatchNotice = new SendMessageNotice();

        String jsonString = JSONObject.toJSONString(map);

        dispatchNotice.setId(templateId);
        dispatchNotice.setEmailData(jsonString);
        dispatchNotice.setDingdingData(jsonString);
        dispatchNotice.setSiteData(jsonString);
        dispatchNotice.setQywechatData(jsonString);
        dispatchNotice.setSendId(LoginContext.getLoginId());
        dispatchNotice.setLink(map.get("link").toString());
        dispatchNotice.setAction(map.get("action").toString());

        dispatchNotice.setBaseUrl(baseUrl);

        dispatchNoticeService.sendMessageNotice(dispatchNotice);
    }

    @Override
    public void deployLog(Map<String, Object> map,String logType,String model) {
        Logging log = new Logging();
        //消息类型
        LoggingType opLogType = new LoggingType();
        opLogType.setId(logType);
        log.setActionType(opLogType);
        log.setModule(model);


        //用户信息
        String userId = LoginContext.getLoginId();
        User user = userProcessor.findOne(userId);

        log.setUser(user);
        log.setLink(map.get("link").toString());  //跳转地址
        log.setAction(map.get("action").toString());  //操作对象名字
        log.setBaseUrl(baseUrl);
        log.setBgroup("sourcefare");
        log.setData(JSONObject.toJSONString(map));

        logService.createLog(log);

    }

    @Override
    public HashMap<String,Object> initMessageAndLogMap() {

        HashMap<String,Object> map = new HashMap<>();
        String userId = LoginContext.getLoginId();
        User user = userProcessor.findOne(userId);
        String userName;
        if (ObjectUtils.isEmpty(user)){
            userName="admin";
        }else {
            userName = StringUtils.isNotEmpty(user.getNickname()) ? user.getNickname() : user.getName();
        }

        map.put("userName", userName);
        map.put("data",SourceFareUtil.date(1,new Date()));

        return map;
    }
}
