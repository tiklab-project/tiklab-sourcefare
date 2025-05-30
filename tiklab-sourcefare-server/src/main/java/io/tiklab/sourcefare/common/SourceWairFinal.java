package io.tiklab.sourcefare.common;

public class SourceWairFinal {


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

}
