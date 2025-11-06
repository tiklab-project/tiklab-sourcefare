UPDATE pcs_prc_function_group SET
      function_ids='project_info,project_scan_config,domain_setting,domain_use,domain_role,domain_message,project_scan_config,scan_door'
WHERE id = 'project_setting';



INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('project_scan', '扫描', 'project_scan', 'scan_report', 1,'2');



-- 扫描报告
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_report', '扫描报告', 'scan_report', NULL, 1, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_exec', '执行扫描', 'scan_exec', 'scan_report', 1, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_report_delete', '删除扫描报告', 'scan_report_delete', 'scan_report', 2, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_issue_update', '更新扫描问题', 'scan_issue_update', 'scan_report', 3, '2');


-- 项目信息
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('project_info', '项目信息', 'project_info', NULL, 1, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('project_update', '编辑项目', 'project_update', 'project_info', 1, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('project_delete', '删除扫描方案', 'project_delete', 'project_info', 2, '2');

--扫描配置
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('project_scan_config', '扫描配置', 'project_scan_config', NULL, 20, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('project_scan_config_update', '编辑扫描配置', 'project_scan_config_update', 'project_scan_config', 1, '2');

--扫描门禁
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_door', '扫描门禁', 'scan_door', NULL, 21, '2');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_door_update', '编辑扫描门禁', 'scan_door_update', 'scan_door', 1, '2');


