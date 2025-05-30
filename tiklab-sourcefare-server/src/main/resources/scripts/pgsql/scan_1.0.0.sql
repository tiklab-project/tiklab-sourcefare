-- ---------------------------
-- 项目
-- ----------------------------
create table scan_project(
      id            varchar(12) PRIMARY KEY,
      project_name  varchar (128) NOT NULL,
      project_desc  varchar(248),
      user_id       varchar(12),
      rules         VARCHAR(12),
      color  integer,
      create_time   timestamp,
      update_time   timestamp
);

-- ---------------------------
-- 仓库服务
-- ----------------------------
create table scan_repository_server(
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
create table scan_deploy_env(
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
create table scan_play(
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
create table scan_record(
        id          varchar(12) PRIMARY KEY,
        scan_play_id         varchar(12) NOT NULL,
        scan_object           varchar (64),
        project_id         varchar  (12) NOT NULL,
        scan_user_id           varchar (12),
        scan_result           varchar (12),
        scan_way                varchar (32),
        all_trouble         integer,
        severity_trouble      integer,
        error_trouble         integer,
        notice_trouble           integer,
        suggest_trouble         integer,
        log                     text,
        scan_time               varchar(12),
        create_time  timestamp
);

-- ---------------------------
-- 扫描记录的明细
-- ----------------------------
create table scan_record_instance(
         id                 varchar(12) PRIMARY KEY,
         scan_record_id     varchar(12) NOT NULL,
         scan_play_id       varchar(12),
         file_name          varchar(248),
         file_path           varchar(248),
         problem_level      integer,
         problem_line       integer,
         rule_name          varchar(64),
         repair_overview    varchar(524),
         repair_desc        text,
         problem_overview   varchar(524),
         problem_desc       text,
         problem_state      varchar(12),
         import_user        varchar(32),
         import_time        timestamp,
         create_time        timestamp
);

-- ---------------------------
-- 扫描问题列表
-- ----------------------------
create table scan_issues(
        id                 varchar(12) PRIMARY KEY,
        scan_record_id     varchar(12) NOT NULL,
        issues_severity    varchar(12),
        scan_issues_key    varchar(32),
        file_name          varchar(248),
        rule_name          varchar(12),
        lead_in_time       timestamp,
        issues_line        integer,
        issues_message     text,
        create_time        timestamp
);

-- ---------------------------
-- 扫描方案
-- ----------------------------
create table scan_scheme(
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
create table scan_scheme_ruleset(
        id          varchar(12) PRIMARY KEY,
        scan_scheme_id  varchar (12) NOT NULL,
        rule_set_id     varchar(12),
        language        varchar(12),
        create_time  timestamp
);
-- ---------------------------
-- 扫描方案的规则的关联表
-- ----------------------------
create table scan_scheme_rule(
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
create table scan_rule_set(
          id          varchar(12) PRIMARY KEY,
          rule_set_name  varchar (128) NOT NULL,
          describe       text,
          language     varchar(12),
          create_time  timestamp
);

-- ---------------------------
-- 扫描规则
-- ----------------------------
create table scan_rule(
      id          varchar(12) PRIMARY KEY,
      rule_set_id  varchar(12) NOT NULL,
      rule_name  varchar (128) NOT NULL,
      rule_type  varchar(12),
      scan_tool varchar(32),
      rule_overview varchar(528),
      problem_level    integer,
      create_time  timestamp,
      describe       text
);



INSERT INTO scan_scheme (id, scheme_name, language, scan_way,category, describe, create_time) VALUES
    ('default', 'Java推荐检测方案', 'Java', 'rule', 1,'默认Java检测方案', '2022-12-12 11:30:00');

INSERT INTO scan_scheme_ruleset (id, scan_scheme_id, rule_set_id, language, create_time) VALUES
    ('default', 'default', '123456789', NULL, '2024-02-29 11:35:10.062');

INSERT INTO scan_scheme_rule (id, scan_scheme_id, scheme_ruleset_id, rule_id, problem_level, is_disable, create_time) VALUES
                                                                                                                              ('51f3f01c280b', 'default', 'default', '123456789000', 1, 0, '2024-02-29 13:37:10.012'),
                                                                                                                              ('08460e059cf6', 'default', 'default', '123456789001', 2, 0, '2024-02-29 13:37:10.055');


INSERT INTO scan_rule_set (id, rule_set_name, describe, language, create_time) VALUES
    ('123456789', 'Java安全检测', '基于spotbugs提供的规则和模式检测代码中的常见问题，帮助开发人员提高代码质量、减少潜在的安全漏洞', 'Java', '2023-12-15 09:52:54.599');

INSERT INTO scan_rule (id, rule_set_id, rule_name, scan_tool, rule_overview, problem_level, create_time, describe) VALUES
('123456789000', '123456789', 'DM_DEFAULT_ENCODING', 'SpotBugs', 'Reliance on default encoding', 1, '2023-12-15 09:53:31.198', 'Found a call to a method which will perform a byte to String (or String to byte) conversion, and will assume that the default platform encoding is suitable. This will cause the application behavior to vary between platforms. Use an alternative API and specify a charset name or Charset object explicitly.'),
('123456789001', '123456789', 'EI_EXPOSE_REP2', 'SpotBugs', 'May expose internal representation by incorporating reference to mutable object', 2, '2023-12-15 09:54:01.023', 'This code stores a reference to an externally mutable object into the internal representation of the object. If instances are accessed by untrusted code, and unchecked changes to the mutable object would compromise security or other important properties, you will need to do something different. Storing a copy of the object is better approach in many situations.');