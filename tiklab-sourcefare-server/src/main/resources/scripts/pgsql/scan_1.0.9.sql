
ALTER TABLE wair_deploy_env add install_way INTEGER;

ALTER TABLE wair_project add complexity INTEGER;


ALTER TABLE wair_scan_record_instance ALTER COLUMN rule_name TYPE VARCHAR(248);
ALTER TABLE wair_issue_statistic ALTER COLUMN rule_name TYPE VARCHAR(248);