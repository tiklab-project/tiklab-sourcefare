

-- ---------------------------
-- 项目覆盖率
-- ----------------------------
create table wair_project_cover(
         id          varchar(12) PRIMARY KEY,
         project_id varchar(12) NOT NULL,
         scan_record_id varchar(12) NOT NULL,
         name  varchar(128) NOT NULL,
         path  varchar(128),
         type  varchar(12) NOT NULL ,
         parent_path varchar (128),
         instructions  integer,
         instructions_missed integer,
         instructions_percent varchar,
         branch  integer,
         branch_missed  integer,
         branch_percent varchar,
         complexity integer,
         complexity_missed integer,
         line  integer,
         line_missed integer,
         methods integer,
         methods_missed integer,
         classes integer,
         classes_missed integer,
         create_time     timestamp
);

-- ---------------------------
-- 项目环境关联表
-- ----------------------------
create table wair_project_env(
     id                    varchar(12) PRIMARY KEY,
     project_id            varchar  (12) NOT NULL,
     type                  varchar  (12),
     env_id                varchar  (12) NOT NULL
);

-- ---------------------------
-- 扫描记录日志
-- ----------------------------
create table wair_scan_record_log(
     id                    varchar(12) PRIMARY KEY,
     project_id            varchar  (12) NOT NULL,
     scan_record_id        varchar  (12) NOT NULL,
     log                   text
);



-- ---------------------------
-- 项目收藏表
-- ----------------------------
create table wair_project_collect(
     id              varchar(12) PRIMARY KEY,
     project_id      varchar  (12) NOT NULL,
     user_id         varchar(12) NOT NULL,
     create_time     timestamp
);


ALTER TABLE wair_scan_record DROP COLUMN log;
ALTER TABLE wair_scan_record DROP COLUMN scan_object;


-- ---------------------------
-- 添加扫描项目的字段
-- ----------------------------
ALTER TABLE wair_project add cover INTEGER;
ALTER TABLE wair_project add scan_result  varchar (12);


ALTER TABLE wair_scan_scheme DROP COLUMN deploy_env_id;
