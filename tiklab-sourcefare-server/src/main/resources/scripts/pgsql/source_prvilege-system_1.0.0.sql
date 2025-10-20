INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('scan_config', '扫描配置', 'scan_config', 'scan_scheme', 20, 1);

INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('integration', '集成开放', 'integration', 'tool_integration,service_integration,openapi', 21, 1);

INSERT INTO pcs_prc_function_group (id, name, code, function_ids, sort, type)
VALUES ('project_sys', '项目', 'project_sys', 'project_system', 10, 1);

-- 扫描方案
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_scheme', '扫描方案', 'scan_scheme', NULL, 20, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_scheme_add', '添加扫描方案', 'scan_scheme_add', 'scan_scheme', 1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_scheme_update', '编辑扫描方案', 'scan_scheme_update', 'user', 2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('scan_scheme_delete', '删除扫描方案', 'scan_scheme_delete', 'user', 3, '1');

--工具集成
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('tool_integration', '工具集成', 'tool_integration', NULL, 21, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('tool_integration_add', '添加工具集成', 'tool_integration_add', 'tool_integration', 1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('tool_integration_update', '编辑工具集成', 'tool_integration_update', 'tool_integration', 2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('tool_integration_delete', '删除工具集成', 'tool_integration_delete', 'tool_integration', 3, '1');

-- 服务集成
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('service_integration', '服务集成', 'service_integration', NULL, 22, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('service_integration_add', '添加服务集成', 'service_integration_add', 'service_integration',1, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('service_integration_update', '修改服务集成', 'service_integration_update', 'service_integration',2, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('service_integration_delete', '删除服务集成', 'service_integration_delete', 'service_integration',3, '1');

--项目
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('project_system', '项目', 'project_system', NULL, 23, '1');
INSERT INTO pcs_prc_function (id, name, code, parent_function_id, sort, type) VALUES ('project_add', '添加项目', 'project_add', 'project_system',1, '1');