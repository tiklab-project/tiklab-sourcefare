
ALTER TABLE wair_scan_record_instance add state integer;
ALTER TABLE wair_scan_record_instance add rule_type varchar(32);


-- ---------------------------
-- 扫描记录实例的动态
-- ----------------------------
create table wair_scan_record_instance_condition(
      id                      varchar(12) PRIMARY KEY,
      scan_record_id          varchar(12) NOT NULL,
      scan_play_id            varchar(12) NOT NULL,
      record_instance_id      varchar(12) NOT NULL,
      user_id                 varchar (12),
      data                    varchar(648),
      create_time             timestamp
);