INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type) VALUES ('project_setting', '项目设置', 'project_setting', 'domain_setting,domain_use,domain_role,domain_message', 4, '2');


INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_setting', '设置', 'domain_setting', null, 2, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_use', '成员', 'domain_use', 'domain_setting', 2, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_role', '角色', 'domain_role', 'domain_setting', 3, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_message', '消息', 'domain_message', 'domain_setting', 3, '2');

-- 成员
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_user_add', '添加成员', 'domain_user_add', 'domain_use', 4, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_user_delete', '删除流水线成员', 'domain_user_delete', 'domain_use', 5, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_user_update', '修改流水线成员角色', 'domain_user_update', 'domain_use', 6, '2');

--角色
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_role_add', '添加角色', 'domain_role_add', 'domain_role', 7, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_role_delete', '删除角色', 'domain_role_delete', 'domain_role', 8, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_role_update', '修改角色信息', 'domain_role_update', 'domain_role',9, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_role_user_add', '添加角色成员', 'domain_role_user_add', 'domain_role', 10, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_role_user_delete', '删除角色成员', 'domain_role_user_delete', 'domain_role', 11, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_role_permission_update', '编辑角色权限', 'domain_role_permission_update', 'domain_role',12, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_role_update_default', '修改默认角色', 'domain_role_update_default', 'domain_role',13, '2');


--消息
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_message_status', '配置消息通知方案开启状态', 'domain_message_status', 'domain_message', 14, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_message_way', '配置消息通知方案通知方式', 'domain_message_way', 'domain_message', 15, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_message_user_add', '配置消息通知方案通知对象', 'domain_message_user_add', 'domain_message', 16, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('domain_message_user_delete', '删除消息通知方案通知对象', 'domain_message_user_delete', 'domain_message', 17, '2');

