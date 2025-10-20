TRUNCATE TABLE pcs_prc_function;
TRUNCATE TABLE pcs_prc_role_function;
TRUNCATE TABLE pcs_prc_function_group;

INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('user', '用户', 'user', 'user,orga,user_group,user_dir', 1, 1);

INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('permission', '权限', 'permission', 'permission', 2, 1);

INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('message', '消息', 'message', 'message', 3, 1);

INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('security', '安全', 'security', 'log,backups_and_recover,ip_whitelist', 8, 1);

INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('system', '系统', 'system', 'licence,apply_limits,custom_logo', 9, 1);


-- 用户
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user', '用户管理', 'user', NULL, 1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_add_user', '添加用户', 'user_add_user', 'user', 1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_update_user', '编辑用户', 'user_update_user', 'user', 2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_delete_user', '删除用户', 'user_delete_user', 'user', 3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_update_user_password', '修改用户密码', 'user_update_user_password', 'user', 4, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_update_user_recover', '找回用户密码', 'user_update_user_recover', 'user', 4, '1');

--部门
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('orga', '部门管理', 'orga', NULL, 2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('orga_add_orga', '添加组织', 'orga_add_orga', 'orga', 1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('orga_update_orga', '编辑组织信息', 'orga_update_orga', 'orga', 2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('orga_delete_orga', '删除组织', 'orga_delete_orga', 'orga', 3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('orga_add_user', '添加组织成员', 'orga_add_user', 'orga', 4, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('orga_delete_user', '删除组织成员', 'orga_delete_user', 'orga', 5, '1');

--用户组
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_group', '用户组管理', 'user_group', NULL, 3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_add_group', '添加用户组', 'user_add_group', 'user_group', 1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_update_group', '更新用户组信息', 'user_update_group', 'user_group', 2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_delete_group', '删除用户组', 'user_delete_group', 'user_group', 3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_add_group_user', '添加用户组成员', 'user_add_group_user', 'user_group', 4, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_delete_group_user', '删除用户组成员', 'user_delete_group_user', 'user_group', 5, '1');

-- 用户目录
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_dir', '用户目录管理', 'user_dir', NULL, 4, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_dir_sync', '同步数据', 'user_dir_sync', 'user_dir', 1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_dir_open', '开启', 'user_dir_open', 'user_dir', 2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_dir_config', '配置', 'user_dir_config', 'user_dir', 3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('user_dir_forbid', '禁止', 'user_dir_forbid', 'user_dir',4, '1');

--权限

INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('permission', '权限管理', 'permission', NULL, 5, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('permission_role_add', '添加角色', 'permission_role_add', 'permission',1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('permission_role_delete', '删除角色', 'permission_role_delete', 'permission',2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('permission_role_update', '修改角色信息', 'permission_role_update', 'permission',3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('permission_role_user_add', '添加角色成员', 'permission_role_user_add', 'permission',3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('permission_role_user_delete', '删除角色信息', 'permission_role_user_delete', 'permission',3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('permission_role_permission_update', '编辑角色权限', 'permission_role_permission_update', 'permission',3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('permission_role_update_default', '修改默认角色', 'permission_role_update_default', 'permission',4, '1');

-- 消息

INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('message', '消息管理', 'message', NULL, 6, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('message_update_send_way', '配置消息发送方式', 'message_update_send_way', 'message',1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('message_update_plan_status', '修改通知方案状态', 'message_update_plan_status', 'message',2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('message_update_plan_send_way', '修改通知方案发送方式', 'message_update_plan_send_way', 'message',3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('message_plan_user_add', '添加通知方案通知成员', 'message_plan_user_add', 'message',4, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('message_plan_delete', '删除通知方案通知成员', 'message_plan_delete', 'message',4, '1');



-- openapi
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('openapi', 'openapi管理', 'openapi', NULL, 100, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('openapi_add', '添加授权秘钥', 'openapi_add', 'openapi',1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('openapi_delete', '删除授权秘钥', 'openapi_delete', 'openapi',2, '1');


-- 备份与恢复
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('backups_and_recover', '备份与恢复管理', 'backups_and_recover', NULL, 101, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('backups_update_status', '修改定时备份状态', 'backups_update_status', 'backups_and_recover',1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('backups_create', '手动备份', 'backups_create', 'backups_and_recover',2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('recover_create', '恢复', 'recover_create', 'backups_and_recover',3, '1');

-- 日志
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('log', '操作日志管理', 'log', NULL, 102, '1');

-- ip黑白名单
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('ip_whitelist', 'IP黑白名单管理', 'ip_whitelist', NULL,103, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('ip_whitelist_white', '配置白名单', 'ip_whitelist_white', 'ip_whitelist',1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('ip_whitelist_black', '配置黑名单', 'ip_whitelist_black', 'ip_whitelist',2, '1');

-- 版本与许可证
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('licence', '版本与许可证管理', 'licence', NULL,104, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('licence_import', '导入Licence', 'licence_import', 'licence',1, '1');

--系统访问权限
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('apply_limits', '系统访问权限管理', 'apply_limits', NULL, 105, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('apply_limits_add_user', '添加授权用户', 'apply_limits_add_user', 'apply_limits', 1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('apply_limits_delete_user', '删除授权用户', 'apply_limits_delete_user', 'apply_limits', 2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('apply_limits_open_user', '激活授权', 'apply_limits_open_user', 'apply_limits', 3, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('apply_limits_close_user', '取消授权', 'apply_limits_close_user', 'apply_limits', 4, '1');


-- 自定义Logo
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('custom_logo', '自定义Logo管理', 'custom_logo', NULL, 106, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('custom_logo_update_title', '修改标题', 'custom_logo_update_title', 'custom_logo',1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('custom_logo_update_status', '修改开启状态', 'custom_logo_update_status', 'custom_logo',2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('custom_logo_update_pic', '修改Logo图片', 'custom_logo_update_pic', 'custom_logo',3, '1');
