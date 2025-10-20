-- ---------------------------
-- 项目
-- ----------------------------
create table wair_project(
      id            varchar(12) PRIMARY KEY,
      project_name  varchar (128) NOT NULL,
      project_desc  varchar(248),
      user_id       varchar(12),
      rules         VARCHAR(12),
      category      varchar(12),
      color  integer,
      create_time   timestamp,
      update_time   timestamp
);

-- ---------------------------
-- 仓库服务
-- ----------------------------
create table wair_repository_server(
         id            varchar(12) PRIMARY KEY,
         name  varchar (128) NOT NULL,
         address  varchar(248) NOT NULL,
         server_type varchar(32),
         auth_type varchar(12),
         secret_key varchar(248),
         account   VARCHAR(32),
         pass_word  varchar(32),
         user_id  varchar(12) NOT NULL,
         create_time   timestamp

);

-- ---------------------------
-- 环境配置
-- ----------------------------
create table wair_deploy_env(
           id             varchar(12) PRIMARY KEY ,
           env_type       varchar (32) NOT NULL,
           env_name       varchar(128) NOT NULL,
           env_address    varchar (255) NOT NULL,
           category              int,
           create_time    timestamp
);

-- ---------------------------
-- 扫描计划
-- ----------------------------
create table wair_scan_play(
      id          varchar(12) PRIMARY KEY,
      play_name  varchar (128) NOT NULL,
      project_id varchar(12) NOT NULL,
      scan_way varchar(12) NOT NULL,
      branch  varchar(32),
      scan_scheme_id varchar(12) NOT NULL,
      repository_server_id varchar(428),
      repository_name varchar(248),
      repository_address varchar(248),
      user_id varchar(12),
      scan_time timestamp,
      create_time  timestamp
);

-- ---------------------------
-- 扫描记录
-- ----------------------------
create table wair_scan_record(
        id                    varchar(12) PRIMARY KEY,
        scan_play_id          varchar(12) NOT NULL,
        scan_object           varchar (64),
        project_id            varchar  (12) NOT NULL,
        scan_user_id          varchar (12),
        scan_result           varchar (12),
        scan_way              varchar (32),
        all_trouble           integer,
        severity_trouble      integer,
        error_trouble         integer,
        notice_trouble        integer,
        suggest_trouble       integer,
        log                   text,
        scan_time             varchar(12),
        create_time           timestamp
);

-- ---------------------------
-- 扫描记录的明细
-- ----------------------------
create table wair_scan_record_instance(
         id                 varchar(12) PRIMARY KEY,
         scan_record_id     varchar(12) NOT NULL,
         scan_play_id       varchar(12),
         file_name          varchar(248),
         file_path           varchar(248),
         problem_level      integer,
         problem_line       integer,
         rule_name          varchar(64),
         repair_overview    text,
         repair_desc        text,
         problem_overview   text,
         problem_desc       text,
         problem_state      varchar(12),
         import_user        varchar(32),
         import_time        timestamp,
         create_time        timestamp
);

-- ---------------------------
-- 扫描问题列表
-- ----------------------------
create table wair_scan_issues(
        id                 varchar(12) PRIMARY KEY,
        scan_record_id     varchar(12) NOT NULL,
        issues_severity    varchar(12),
        scan_issues_key    varchar(32),
        file_name          varchar(248),
        rule_name          varchar(248),
        lead_in_time       timestamp,
        issues_line        integer,
        issues_message     text,
        create_time        timestamp
);

-- ---------------------------
-- 扫描方案
-- ----------------------------
create table wair_scan_scheme(
        id          varchar(12) PRIMARY KEY,
        scheme_name  varchar (128) NOT NULL,
        language     varchar(12),
        scan_way    varchar(12),
        category    int,
        deploy_env_id varchar(12),
        describe         varchar (246),
        create_time  timestamp
);

-- ---------------------------
-- 扫描方案规则集的关联表
-- ----------------------------
create table wair_scan_scheme_ruleset(
        id          varchar(12) PRIMARY KEY,
        scan_scheme_id  varchar (12) NOT NULL,
        rule_set_id     varchar(12),
        language        varchar(12),
        create_time  timestamp
);
-- ---------------------------
-- 扫描方案的规则的关联表
-- ----------------------------
create table wair_scan_scheme_rule(
         id          varchar(12) PRIMARY KEY,
         scan_scheme_id varchar(12) NOT NULL,
         scheme_ruleset_id  varchar(12) NOT NULL,
         rule_Id  varchar (12) NOT NULL,
         problem_level    integer,
         is_disable       integer,
         create_time  timestamp
);

-- ---------------------------
-- 扫描规则集
-- ----------------------------
create table wair_scan_rule_set(
          id          varchar(12) PRIMARY KEY,
          rule_set_name  varchar (128) NOT NULL,
          describe       text,
          language     varchar(12),
          create_time  timestamp
);

-- ---------------------------
-- 扫描规则
-- ----------------------------
create table wair_scan_rule(
      id          varchar(12) PRIMARY KEY,
      rule_set_id  varchar(12) NOT NULL,
      rule_name  varchar (128) NOT NULL,
      rule_type  varchar(12),
      scan_tool varchar(32),
      rule_overview text,
      problem_level    integer,
      create_time  timestamp,
      description       text
);

-- ---------------------------
-- 打开项目记录表
-- ----------------------------
create table wair_record_open(
         id               varchar(12),
         project_id       varchar(12),
         user_id          varchar(12),
         new_open_time    timestamp,
         create_time      timestamp
);

