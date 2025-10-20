package io.tiklab.sourcefare.project.service;

import io.tiklab.licence.appauth.service.ApplyAuthService;
import io.tiklab.licence.licence.model.Version;
import io.tiklab.licence.licence.service.VersionService;
import io.tiklab.message.message.service.MessageNoticeService;
import io.tiklab.message.setting.service.MessageSendTypeService;
import io.tiklab.privilege.role.service.RoleService;
import io.tiklab.security.backups.service.BackupsDbService;
import io.tiklab.sourcefare.project.model.SystemCount;
import io.tiklab.user.directory.service.UserDirService;
import io.tiklab.user.orga.service.OrgaService;
import io.tiklab.user.user.service.UserProcessor;
import io.tiklab.user.usergroup.service.UserGroupService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class SystemCountServiceImpl implements SystemCountService{

    @Autowired
    UserProcessor userProcessor;

    @Autowired
    OrgaService orgaService;

    @Autowired
    UserGroupService userGroupService;

    @Autowired
    RoleService roleService;

    @Autowired
    UserDirService userDirService;

    @Autowired
    MessageNoticeService messageNoticeService;

    @Autowired
    MessageSendTypeService messageSendTypeService;

    @Autowired
    VersionService versionService;

    @Autowired
    ApplyAuthService applyAuthService;

    @Autowired
    BackupsDbService backupsDbService;
    @Override
    public SystemCount collectCount() {
        SystemCount systemCount = new SystemCount();

        Integer userNumber = userProcessor.findUserNumber();
        Integer orgaNumber = orgaService.findOrgaNumber();
        Integer userGroupNumber = userGroupService.findUserGroupNumber();
        Integer roleNumber = roleService.findRoleNumber();
        Integer userDirNumber = userDirService.findUserDirNumber();
        Integer noticeNumber = messageNoticeService.findNoticeNumber("gitpuk");
        Integer sendTypeNumber = messageSendTypeService.findSendTypeNumber();

        String lastBackupsTime = backupsDbService.findLastBackupsTime();



        systemCount.setUserNum(userNumber);
        systemCount.setOrgaNum(orgaNumber);
        systemCount.setUserGroupNum(userGroupNumber);
        systemCount.setRoleNum(roleNumber);
        systemCount.setUserDirNum(userDirNumber);
        systemCount.setMessageNoticeNum(noticeNumber);
        systemCount.setMessageSendTypeNum(sendTypeNumber);


        systemCount.setBackupsTime(lastBackupsTime);

        findProductInfo(systemCount);
        return systemCount;
    }

    public void findProductInfo(SystemCount systemCount){
        Version version = versionService.getVersion();
        Integer applyAuthNumber = applyAuthService.findApplyAuthNumber();
        systemCount.setAuthUserNum(applyAuthNumber);
        systemCount.setVersion(version);
    }
}
