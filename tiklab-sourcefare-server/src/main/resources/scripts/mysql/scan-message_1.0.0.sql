-- ---------------------------
-- 日志类型
-- ----------------------------
INSERT INTO pcs_op_log_type (id, name, bgroup) VALUES ('SCAN_CREATE', '创建项目', 'sourcefare');
INSERT INTO pcs_op_log_type (id, name, bgroup) VALUES ('SCAN_UPDATE', '更新项目', 'sourcefare');
INSERT INTO pcs_op_log_type (id, name, bgroup) VALUES ('SCAN_DELETE', '删除项目', 'sourcefare');

-- ---------------------------
-- 消息类型
-- ----------------------------
INSERT INTO pcs_mec_message_type (id, name, description, bgroup) VALUES ('SCAN_CREATE', '创建项目', '创建项目消息', 'sourcefare');
INSERT INTO pcs_mec_message_type (id, name, description, bgroup) VALUES ('SCAN_UPDATE', '更新项目', '更新项目消息', 'sourcefare');
INSERT INTO pcs_mec_message_type (id, name, description, bgroup) VALUES ('SCAN_DELETE', '删除项目', '删除项目消息', 'sourcefare');

-- ---------------------------
--消息发送人
-- ----------------------------
INSERT INTO pcs_mec_message_notice_connect_user ("id", "message_notice_id", "user_id") VALUES ('fbf8c6bb1d3c', 'SCAN_CREATE', '111111');
INSERT INTO pcs_mec_message_notice_connect_user ("id", "message_notice_id", "user_id") VALUES ('defe335b21ef', 'SCAN_UPDATE', '111111');
INSERT INTO pcs_mec_message_notice_connect_user ("id", "message_notice_id", "user_id") VALUES ('f11c3d87764b', 'SCAN_DELETE', '111111');



-- ---------------------------
-- 发送消息途径
-- ----------------------------
INSERT INTO pcs_mec_message_notice (id, message_type_id, type, bgroup, message_send_type_id) VALUES ('SCAN_CREATE', 'SCAN_CREATE', 1, 'sourcefare', 'site');
INSERT INTO pcs_mec_message_notice (id, message_type_id, type, bgroup, message_send_type_id) VALUES ('SCAN_UPDATE', 'SCAN_UPDATE', 1, 'sourcefare', 'site');
INSERT INTO pcs_mec_message_notice (id, message_type_id, type, bgroup, message_send_type_id) VALUES ('SCAN_DELETE', 'SCAN_DELETE', 1, 'sourcefare', 'site');


-- ---------------------------
-- 发送消息模版
-- ----------------------------
INSERT INTO pcs_mec_message_template (id, msg_type_id, msg_send_type_id, title, content,link,bgroup,link_params) VALUES ('SCAN_CREATE', 'SCAN_CREATE', 'site', '创建项目', '创建项目',null,'sourcefare',null);
INSERT INTO pcs_mec_message_template (id, msg_type_id, msg_send_type_id, title, content,link,bgroup,link_params) VALUES ('SCAN_UPDATE', 'SCAN_UPDATE', 'site', '更新项目', '更新项目',null,'sourcefare',null);
INSERT INTO pcs_mec_message_template (id, msg_type_id, msg_send_type_id, title, content,link,bgroup,link_params) VALUES ('SCAN_DELETE', 'SCAN_DELETE', 'site', '删除项目', '删除项目',null,'sourcefare',null);

INSERT INTO pcs_mec_message_template(id, msg_type_id, msg_send_type_id, title, content,link,bgroup,link_params) VALUES
    ('bb09db8fa4d1', 'SCAN_CREATE', 'qywechat', NULL, '## 创建项目\n
> 创建人：<font color=comment>${userName}</font>\n
> 仓库名称：<font color=warning>[${projectName}](${qywxurl})</font>','/#/project/${projectId}/setting/info','sourcefare',NULL);

INSERT INTO pcs_mec_message_template(id, msg_type_id, msg_send_type_id, title, content,link,bgroup,link_params) VALUES
    ('bb09db8fa512', 'SCAN_DELETE', 'qywechat', NULL, '## 删除项目\n
> 执行人：<font color=comment>${userName}</font>\n
> 仓库名称：<font color=warning>[${projectName}](${qywxurl})</font>','/#/project','sourcefare',NULL);
INSERT INTO pcs_mec_message_template(id, msg_type_id, msg_send_type_id, title, content,link,bgroup,link_params) VALUES
    ('bb09db8fa612', 'SCAN_UPDATE', 'qywechat', NULL, '## 更新项目\n
> 执行人：<font color=comment>${userName}</font>\n
> 更新前名称：<font color=comment>${updateName}</font>\n
> 更新后名称：<font color=warning>[${projectName}](${qywxurl})</font>','/#/project/${projectId}/setting/info','sourcefare',NULL);
