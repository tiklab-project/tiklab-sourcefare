
ALTER TABLE wair_scan_door add error_num INTEGER;
ALTER TABLE wair_scan_door add error_state INTEGER;


DELETE FROM wair_scan_door  where id='default';

INSERT INTO wair_scan_door (id,project_id,severity_num,severity_state,error_num,error_state,notice_num,notice_state,suggest_num,suggest_state,create_time)
       VALUES ('default', 'default', 5, 1, 20, 1, 100, 1,500,0,null);
