package io.tiklab.sourcefare.project.service;

import io.tiklab.core.utils.UuidGenerator;
import io.tiklab.dal.jdbc.JdbcTemplate;
import io.tiklab.dsm.support.DsmProcessTask;
import io.tiklab.privilege.role.model.Role;
import io.tiklab.privilege.role.model.RoleQuery;
import io.tiklab.privilege.role.service.RoleService;
import org.apache.commons.lang.StringUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.Arrays;
import java.util.List;

@Component
public class InitAuthority implements DsmProcessTask {

    @Autowired
    JdbcTemplate jdbcTemplate;

    @Autowired
    RoleService roleService;

    @Override
    public void execute() {
        addSysRoleFunction();
    }

    private void addSysRoleFunction() {
        for (String sysRoleId : sysRoleIds) {
            String[] systemRoleIds = findSystemRoleIds(sysRoleId);
            execBatchInsert(systemRoleIds, sysRoleId);
        }
        RoleQuery roleQuery = new RoleQuery();
        roleQuery.setScope(2);
        roleQuery.setType("2");
        List<Role> roleList = roleService.findRoleList(roleQuery);

        for (Role role : roleList) {
            String[] systemRoleIds = new String[]{};
            String parentId = role.getParentId();
            if (!StringUtils.isEmpty(parentId)) {
                systemRoleIds = findSystemRoleIds(parentId);
            }
            if (systemRoleIds.length == 0) {
                Integer businessType = role.getBusinessType();
                if (businessType.equals(2)) {
                    systemRoleIds = domainAdminFunctionIds;
                } else {
                    systemRoleIds = domainFunctionIds;
                }
            }

            execBatchInsert(systemRoleIds, role.getId());
        }
    }

    private String[] findSystemRoleIds(String id) {
        switch (id) {
            case "111111", "1" -> {
                return allSysFunctionIds;
            }
            case "2" -> {
                return sysFunctionIds;
            }

            // 项目
            case "pro_111111" -> {
                return domainAdminFunctionIds;
            }
            case "4" -> {
                return domainFunctionIds;
            }

            default -> {
                return new String[]{};
            }
        }
    }


    private final String[] sysRoleIds = new String[]{"111111", "1", "2", "pro_111111", "4"};


    private final String[] allSysFunctionIds = new String[]{
            "user", "user_add_user", "user_update_user", "user_delete_user", "user_update_user_password", "user_update_user_recover",
            "orga", "orga_add_orga", "orga_update_orga", "orga_delete_orga", "orga_add_user", "orga_delete_user",
            "user_group", "user_add_group", "user_update_group", "user_delete_group", "user_add_group_user", "user_delete_group_user",
            "user_dir", "user_dir_sync", "user_dir_open", "user_dir_config", "user_dir_forbid",
            "permission", "permission_role_add", "permission_role_delete", "permission_role_update", "permission_role_user_add", "permission_role_user_delete", "permission_role_permission_update", "permission_role_update_default",
            "message", "message_update_send_way", "message_update_plan_status", "message_update_plan_send_way", "message_plan_user_add", "message_plan_delete",
            "openapi", "openapi_add", "openapi_delete", "openapi_find",
            "backups_and_recover", "backups_update_status", "backups_create", "recover_create",
            "log",
            "ip_whitelist", "ip_whitelist_white", "ip_whitelist_black",
            "licence", "licence_import",
            "apply_limits", "apply_limits_add_user", "apply_limits_delete_user", "apply_limits_open_user", "apply_limits_close_user",
            "custom_logo", "custom_logo_update_title", "custom_logo_update_status", "custom_logo_update_pic",

            "scan_scheme","scan_scheme_add","scan_scheme_update","scan_scheme_delete",
            "tool_integration","tool_integration_add","tool_integration_update","tool_integration_delete",
            "service_integration","service_integration_add","service_integration_update","service_integration_delete",
            "project_system","project_add",

    };

    private final String[] sysFunctionIds = new String[]{

            "user",
            "orga",
            "user_group",
            "user_dir",
            "permission",
            "message",
            "openapi",
            "backups_and_recover",
            "log",
            "ip_whitelist",
            "licence",
            "apply_limits",
            "custom_logo",

            "scan_scheme",
            "tool_integration",
            "service_integration",
            "project_system",


            /*         // 流水线权限
                     "pipeline",
                     "pipeline_history",
                     "pipeline_release",
                     "pipeline_statistics",
                     "pipeline_application",
                     "pipeline_environment",
                     "pipeline_variable",
                     "pipeline_agent",
                     "pipeline_host",
                     "pipeline_host_group",
                     "pipeline_kubernetes_cluster",
                     "pipeline_tool_integration",
                     "pipeline_service_integration",
                     "pipeline_resource_monitor",*/
    };


    private final String[] domainAdminFunctionIds = new String[]{
           "project_setting","domain_use","domain_role","domain_permission","domain_message",
            "scan_report","scan_exec","scan_report_delete","scan_issue_update",
            "project_info","project_update","project_delete",
            "project_scan_config","project_scan_config_update","scan_door","scan_door_update",

            // 系统全局设置权限
            "domain_user_add", "domain_user_delete", "domain_user_update",
            "domain_role_add", "domain_role_delete", "domain_role_update", "domain_role_user_add", "domain_role_user_delete", "domain_role_permission_update", "domain_role_update_default",
            "domain_message_status", "domain_message_way", "domain_message_user_add", "domain_message_user_delete"
    };

    private final String[] domainFunctionIds = new String[]{
            "project_setting",
            "project_info",
            "project_scan_config",
            "domain_setting",
            "domain_use",
            "domain_role",
            "domain_message",
            "project_scan_config",
            "scan_door",
            "project_scan"
    };


    public void execBatchInsert(String[] functionIds, String roleId) {

        String sql = "INSERT INTO pcs_prc_role_function (id, role_id, function_id) VALUES (?, ?, ?)";

        jdbcTemplate.batchUpdate(sql, Arrays.stream(functionIds).toList(), functionIds.length,
                (ps, functionId) -> {
                    ps.setString(1, UuidGenerator.getRandomIdByUUID(12));
                    ps.setString(2, roleId);
                    ps.setString(3, functionId);
                }
        );
    }
}
