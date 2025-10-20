-- ---------------------------
-- 项目扫描问题的统计表
-- ----------------------------
create table wair_issue_statistic(
     id              varchar    (12) PRIMARY KEY,
     project_id      varchar    (12) NOT NULL,
     file_path           varchar(412),
     problem_level      integer,
     problem_line       integer,
     rule_name          varchar(64),
     rule_type          varchar(64),
     problem_state      integer,
     problem_desc       text,
     create_time       timestamp
);


-- ---------------------------
-- Go类型项目覆盖率
-- ----------------------------
create table wair_project_cover_go(
          id          varchar(12) PRIMARY KEY,
          project_id varchar(12) NOT NULL,
          scan_record_id varchar(12) NOT NULL,
          file_path  varchar(328) NOT NULL,
          mode_path  varchar(328) NOT NULL,
          coverage_rate  varchar(12),
          create_time     timestamp
);


COMMENT ON COLUMN "wair_issue_statistic"."project_id" IS '项目id';
COMMENT ON COLUMN "wair_issue_statistic"."file_path" IS '文件路径';
COMMENT ON COLUMN "wair_issue_statistic"."problem_level" IS '问题等级 1、2、3';
COMMENT ON COLUMN "wair_issue_statistic"."problem_line" IS '问题行';
COMMENT ON COLUMN "wair_issue_statistic"."rule_name" IS '问题名称';
COMMENT ON COLUMN "wair_issue_statistic"."rule_type" IS '问题类型';
COMMENT ON COLUMN "wair_issue_statistic"."problem_state" IS '问题状态 0(未解决) 1(已解决) ';
COMMENT ON COLUMN "wair_issue_statistic"."problem_desc" IS '问题描述';


ALTER TABLE wair_scan_record_log add title varchar(128);
ALTER TABLE wair_scan_record_log add time varchar(32);
ALTER TABLE wair_scan_record_log add state INTEGER;

ALTER TABLE wair_scan_record_complexity add code_line_non integer;
ALTER TABLE wair_scan_record_complexity RENAME COLUMN num TO complexity_num;
ALTER TABLE wair_scan_record_complexity ALTER COLUMN path DROP NOT NULL;

ALTER TABLE wair_scan_record_log add sort INTEGER;
ALTER TABLE wair_scan_record_log add type varchar(32);