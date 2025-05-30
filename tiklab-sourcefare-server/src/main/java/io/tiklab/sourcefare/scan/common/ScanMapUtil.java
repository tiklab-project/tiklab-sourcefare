package io.tiklab.sourcefare.scan.common;

import io.tiklab.sourcefare.scan.model.ScanRecord;

import java.sql.Date;
import java.util.HashMap;
import java.util.Map;

public class ScanMapUtil {

    //执行扫描的日志
    public static Map<String , String> scanExecLog = new HashMap<>();


    //执行扫描执行开始时间
    public static Map<String , Date> scanExecStarTime = new HashMap<>();

    //代码扫描的记录
    public static Map<String , ScanRecord> scanExecRecord = new HashMap<>();



    // 添加扫描日志
    public static void putScanLog(String key, String value) {
        scanExecLog.put(key, value);
    }

    // 获取扫描日志
    public static String getScanLog(String key) {
        return scanExecLog.get(key);
    }

    // 移除扫描日志
    public static String removeScanLog(String key) {
        return scanExecLog.remove(key);
    }

    // 添加扫描记录
    public static void putExecRecord (String key, ScanRecord value) {
        scanExecRecord.put(key, value);
    }

    // 获取扫描记录
    public static ScanRecord getExecRecord (String key) {
        return scanExecRecord.get(key);
    }

    // 移除扫描记录
    public static ScanRecord removeExecRecord (String key) {
        return scanExecRecord.remove(key);
    }

    // 添加扫描的开始时间
    public static void putExecStarTime (String key, Date value) {
        scanExecStarTime.put(key, value);
    }

    // 获取扫描开始时间
    public static Date getExecStarTime (String key) {
        return scanExecStarTime.get(key);
    }
}
