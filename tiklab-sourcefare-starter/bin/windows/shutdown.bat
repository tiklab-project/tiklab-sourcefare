
@echo off
chcp 65001 > nul
setlocal enabledelayedexpansion

REM 启动类文件
set APP_MAIN=io.tiklab.sourcefare.starter.SourceFareApplication

REM 获取系统文件地址
set "current_path=%~dp0"
echo BAT_DATA_PATH:%current_path%

rem 进入目录
cd "%current_path%"

rem 上级目录
cd.. 

REM 输出基本文件地址
set DIRS=%cd%\

REM 内嵌应用地址
set EMBEDDED_DIR=%DIRS%embbed
echo EMBEDDED_DIR:%EMBEDDED_DIR%

REM JDK路径
set JAVA_HOME=%EMBEDDED_DIR%\jdk-16.0.2
echo JAVA_HOME:%JAVA_HOME%
if not exist "%JAVA_HOME%" (
    echo Unable to obtain the JAVA_HOME path!
    goto :start_error
)

set YAML_FILE=%DIRS%conf\application.yaml
set PGSQL_PORT=
set DATE_HOME=
set PGSQL_ENABLE=
set values=

rem 获取DateHome
for /f "tokens=1,* delims=:" %%a in ('type "%YAML_FILE%"') do (
    rem 输出当前行内容，以便调试
    if "%%a" == "DATA_HOME" (
         set DATE_HOME=%%b
    )
)

:found
set "DATE_HOME=!DATE_HOME: =!"
echo APPLY_DATA_HOME:%DATE_HOME%


rem 获取PgsqlPort
for /f "tokens=1,* delims=:" %%a in ('type "%YAML_FILE%"') do (
    rem 输出当前行内容，以便调试
    if "%%a" == "postgresql" (
        set values=1
    )
    if "!values!" == "1" (
        if "%%a" == "  db" (
            set values=2
        )
    )
    if "!values!" == "2" (
        if "%%a" == "    port" (
            set PGSQL_PORT=%%b
            set values=0
            goto found
        )
    )
)

:found
set "PGSQL_PORT=!PGSQL_PORT: =!"


rem 获取PgsqlPort
for /f "tokens=1,* delims=:" %%a in ('type "%YAML_FILE%"') do (
    rem 输出当前行内容，以便调试
    if "%%a" == "postgresql" (
        set values=1
    )
    if "!values!" == "1" (
        if "%%a" == "  embbed" (
            set values=2
        )
    )
    if "!values!" == "2" (
        if "%%a" == "    enable" (
            set PGSQL_ENABLE=%%b
            set values=0
            goto found
        )
    )
)

:found
set "PGSQL_ENABLE=!PGSQL_ENABLE: =!"


rem 获取ServerPort
set SERVER_PORT=
for /f "tokens=1,* delims=:" %%a in ('type "%YAML_FILE%"') do (
    rem 输出当前行内容，以便调试
    if "%%a" == "server" (
        set values=1
    )
    if "!values!" == "1" (
        if "%%a" == "  port" (
            set SERVER_PORT=%%b
            set values=0
            goto found
        )
    )
)

:found
set "SERVER_PORT=!SERVER_PORT: =!"
echo APPLY_SERVER_PORT:%SERVER_PORT%


echo ================================================================================================================

if "%SERVER_PORT%"=="" (
    echo "Callback hook not triggered , Forced stop ......"
) else (
    echo Callback hook triggered ......
    curl -u admin:admin123 -X POST http://localhost:%SERVER_PORT%/actuator/shutdown
    echo .
    timeout /t 2 >nul
)

if exist "%DATE_HOME%\postgresql\postmaster.pid" (
    rem 文件存在，执行下面的代码
    for /f "usebackq delims=" %%a in ("%DATE_HOME%\postgresql\postmaster.pid") do (
        set "PGSQL_PID=%%a"
        rem 这里可以添加其他操作，比如使用 %PGSQL_PID%
    )

    rem 判断pgsql端口是否被占用
    if "%PGSQL_ENABLE%" == "true" (
        if not "%PGSQL_PID%" == "" (
            taskkill /PID %PGSQL_PID% /F > NUL 2>&1
        )
    )
)

rem for /f "usebackq delims=" %%a in ("%DATE_HOME%\postgresql\postmaster.pid") do (
rem     set "PGSQL_PID=%%a"
rem     goto :break
rem )
rem :break

rem rem 判断pgsql端口是否被占用
rem if "%PGSQL_ENABLE%" == "true" (
rem     if not "%PGSQL_PID%" == "" (
rem         taskkill /PID %PGSQL_PID% /F > NUL 2>&1
rem     )
rem )

set PID=0
for /f "usebackq tokens=1-2" %%a in (`"%JAVA_HOME%\bin\jps.exe" -l ^| findstr %APP_MAIN%`) do (
set PID=%%a
)

if %PID% == 0 (
     exit
) else (
    taskkill /PID %PID% /F > NUL 2>&1
    rem if errorlevel 1 (
    rem     echo STOPPING APPLY SERVER %APP_MAIN% FAILED
    rem ) else (
    rem     echo STOPPING APPLY SERVER %APP_MAIN% SUCCESS(PID=%PID%^)
    rem )
)


echo ================================================================================================================