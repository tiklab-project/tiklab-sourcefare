-- ---------------------------
-- 项目扫描记录的重复数据
-- ----------------------------
create table wair_scan_record_duplicated(
     id              varchar    (12) PRIMARY KEY,
     project_id      varchar    (12) NOT NULL,
     record_id       varchar    (12) NOT NULL,
     path            varchar    (496) NOT NULL,
     start_line      INTEGER,
     end_line        INTEGER,
     lines           INTEGER,
     grouping         varchar(32),
     create_time     timestamp
);

-- ---------------------------
-- 项目扫描记录的复杂度
-- ----------------------------
create table wair_scan_record_complexity(
    id              varchar    (12) PRIMARY KEY,
    project_id      varchar    (12) NOT NULL,
    record_id       varchar    (12) NOT NULL,
    path            varchar    (496),
    method          varchar    (248),
    type            varchar    (32) NOT NULL,
    num             INTEGER,
    create_time     timestamp
);