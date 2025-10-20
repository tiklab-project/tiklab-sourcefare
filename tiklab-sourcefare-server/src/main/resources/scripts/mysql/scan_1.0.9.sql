
ALTER TABLE wair_deploy_env add install_way INTEGER;

ALTER TABLE wair_project add complexity INTEGER;


ALTER TABLE wair_scan_record_instance MODIFY rule_name VARCHAR(248);
ALTER TABLE wair_issue_statistic MODIFY rule_name  VARCHAR(248)