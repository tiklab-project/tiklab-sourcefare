-- ---------------------------
-- 服务端扫描 的仓库信息
-- ----------------------------
create table wair_project_rep(
     id          varchar(12) PRIMARY KEY,
     project_id varchar(12) NOT NULL,
     repository_server_id varchar (12) NOT NULL,
     branch  varchar(32),
     repository_code varchar(60),
     repository_name varchar(248),
     repository_address varchar(428)
);


-- ---------------------------
-- 添加扫描项目的字段
-- ----------------------------
ALTER TABLE wair_project add scan_way varchar(12) NOT NULL;
ALTER TABLE wair_project add scan_scheme_id varchar(12);
ALTER TABLE wair_project add scan_time timestamp;
ALTER TABLE wair_project RENAME COLUMN project_name TO name;

ALTER TABLE wair_scan_record_instance_condition RENAME COLUMN scan_play_id TO project_id;

ALTER TABLE wair_scan_record DROP COLUMN scan_play_id;


ALTER TABLE wair_scan_record_instance DROP COLUMN scan_play_id;
ALTER TABLE wair_scan_record_instance add project_id varchar(12);

-- ---------------------------
-- 删除计划表
-- ----------------------------
DROP TABLE wair_scan_play


