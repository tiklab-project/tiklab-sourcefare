package io.tiklab.sourcefare.common;

public class SourceFareServerFinal {



    public static final String ACCESS_TOKEN = "dGlrbGFi";

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


    /**
     * 系统任务类型
     */
    public static final String TASK_TOOL_TYPE_JDK = "jdk";
    public static final String TASK_TOOL_TYPE_MAVEN = "maven";
    public static final String TASK_TOOL_TYPE_GIT = "git";
    public static final String TASK_TOOL_TYPE_SVN = "svn";
    public static final String TASK_TOOL_TYPE_NODE = "node";
    public static final String TASK_TOOL_TYPE_NPM = "npm";
    public static final String TASK_TOOL_TYPE_GO = "go";

    public static final String TASK_TOOL_TYPE_PYTHON="python";


    public static final String PROJECT_DELETE = "project_delete";
    public static final String PROJECT_UPDATE = "project_update";


    //代码扫描方式 静态、编译、组合
    public static final String STATIC = "static";

    public static final String COMPILE = "compile";

    public static final String COLLECT = "collect";



    public static final String PRI_GITLAB = "priGitlab";
    public static final String GIT_PUK = "gitPuk";
    public static final String GITEE = "gitee";
    public static final String GITEE_PARH = "https://gitee.com";


    //gitee 查询仓库用户信息API
    public static final String GITEE_USER_URL = "https://gitee.com/api/v5/user";

    //gitee 查询仓库API地址
    public static final String GITEE_API_URL = "https://gitee.com/api/v5/user/repos";

    //gitee 查询仓库分支API地址
    public static final String GITEE_BRANCH_API_URL = "https://gitee.com/api/v5/repos/";



    // 查询gitPuk的仓库地址
    public static final String FIND_REPOSITORY_GIT_PUK = "/api/rpy/findUserRepositoryList";

    // 查询gitPuk的仓库分支
    public static final String FIND_REPOSITORY_BRANCH_GIT_PUK = "/api/branch/findAllBranch";

    //gitlab 查询仓库API地址
    public static final String GITLAB_API_URL = "https://gitlab.com/api/v4/projects";


    //扫描类型
    public static final String SERVER = "server";
    public static final String SERVER_UPLOAD = "serverUpload";

    public static final String CLIENT = "client";
}
