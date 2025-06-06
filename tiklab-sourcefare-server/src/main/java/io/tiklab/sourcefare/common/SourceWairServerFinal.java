package io.tiklab.sourcefare.common;

public class SourceWairServerFinal {


    // 查询gitPuk的仓库地址
    public static final String FIND_REPOSITORY_GIT_PUK = "/api/rpy/findRepositoryByUser";


    // 查询gitPuk的仓库分支
    public static final String FIND_REPOSITORY_BRANCH_GIT_PUK = "/api/branch/findAllBranch";

    // 代码扫描应用类型
    public static final String SCAN_SONAR = "sonar";
    public static final String SCAN_SPOTBUGS = "spotbugs";

    /**
     * DEFAULT
     */
    public static final String DEFAULT = "default";

    //eslint可执行程序路径
    public static final String ESLINT_PATH ="node_modules/eslint/bin/eslint.js";

    //默认异常
    public static final Integer SYSTEM_EXCEPTION = 56100;

    //文件异常
    public static final Integer FILE_EXCEPTION = 56101;

    //时间异常
    public static final Integer TIME_EXCEPTION = 56102;

    //重复
    public static final Integer REPEAT01_EXCEPTION = 56111;


    //重复
    public static final Integer REPEAT02_EXCEPTION = 56112;


    //没有查询到
    public static final Integer NOT_FOUNT_EXCEPTION = 56404;


    // 日志、消息类型
    public static final String LOG_TYPE_CREATE = "SCAN_CREATE";

    public static final String LOG_TYPE_UPDATE = "SCAN_UPDATE";

    public static final String LOG_TYPE_DELETE = "SCAN_DELETE";


    /*
     * 消息、日志跳转路径
     * */
    //仓库创建
    public static final String LOG_RPY_CREATE = "/project/${projectId}/setting/info";
    //仓库删除
    public static final String LOG_RPY_DELETE = "/project";
    //仓库修改
    public static final String LOG_RPY_UPDATE = "/project/${projectId}/setting/info";



}
