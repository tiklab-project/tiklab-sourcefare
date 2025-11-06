TRUNCATE TABLE wair_scan_rule;
TRUNCATE TABLE wair_scan_rule_set;
TRUNCATE TABLE wair_scan_scheme;
TRUNCATE TABLE wair_scan_scheme_rule;
TRUNCATE TABLE wair_scan_scheme_ruleset;

ALTER TABLE wair_scan_rule add property INTEGER NOT NULL;
ALTER TABLE wair_scan_rule_set add property INTEGER NOT NULL;
ALTER TABLE wair_scan_scheme_ruleset add property INTEGER NOT NULL;

ALTER TABLE wair_scan_record RENAME COLUMN scan_result TO issue_result;
ALTER TABLE wair_scan_record add com_result varchar(12);
ALTER TABLE wair_scan_record add dup_result varchar(12);
ALTER TABLE wair_scan_record add cover_result varchar(12);