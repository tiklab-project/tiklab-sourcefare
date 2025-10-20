-- ---------------------------
-- 项目上传的信息
-- ----------------------------
create table wair_project_rep_upload(
     id              varchar(12) PRIMARY KEY,
     project_id      varchar  (12) NOT NULL,
     code_name       varchar  (248) NOT NULL,
     create_time     timestamp
);


-- ---------------------------
-- 扫描门禁
-- ----------------------------
create table wair_scan_door(
        id              varchar(12) PRIMARY KEY,
        project_id      varchar  (12) NOT NULL,
        severity_num    INTEGER,
        severity_state  INTEGER,
        notice_num      INTEGER,
        notice_state    INTEGER,
        suggest_num     INTEGER,
        suggest_state   INTEGER,
        create_time     timestamp
);


INSERT INTO wair_scan_door VALUES ('default', 'default', 5, 1, 10, 1, 50, 1,null);