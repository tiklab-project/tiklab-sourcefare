#!/bin/sh

DIRS=$(dirname "$PWD")

APP_MAIN="io.tiklab.sourcefare.starter.SourceFareApplication"

# find ${DIRS}/ -name '*.sh' | xargs dos2unix;

YAML=${DIRS}/conf/application.yaml

DATA_HOME=""

create_home(){

  data_home=$(awk -F': ' '/DATA_HOME:/ {print $2}' "${YAML}")

  DATA_HOME=${data_home}
  echo "DATA_HOME: ${data_home}"

  # 创建目录及其上级目录(如果不存在)
  mkdir -p "${data_home}"

  # 检查目录是否创建成功
  if [ -d "${data_home}" ]; then
    echo "DATA_HOME ${data_home} initialized successfully！"
  else
    echo "================================================================================================================"
    echo "DATA_HOME ${data_home} initialized Failed!"
    echo "请更改文件${YAML}中的DATA_HOME字段，配置应用可以访问的地址,请不要配置与程序相同的目录！"
    echo "${APP_MAIN} start [failed]"
    echo "================================================================================================================"
    exit 1
  fi

}

JDK_VERSION=jdk-16.0.2
valid_jdk(){
  if [ -d "${DIRS}/embbed/${JDK_VERSION}" ]; then
      echo "user embbed jdk ${JAVA_HOME}"
      JAVA_HOME="${DIRS}/embbed/${JDK_VERSION}"
  else
      echo "Unable to find embbed jdk!"
      exit 1;
  fi
}

# PGSQL_VERSION=pgsql-10.23
# valid_postgresql(){
#   if [ -d "${DIRS}/embbed/${PGSQL_VERSION}/bin" ]; then
#       echo "user embbed postgresql exist"
#       rm -rf ${DIRS}/embbed/${PGSQL_VERSION}/${PGSQL_VERSION}.tar.gz
#   else
#       echo "unzip postgresql file ....."
#       tar -xzf "${DIRS}/embbed/${PGSQL_VERSION}/${PGSQL_VERSION}.tar.gz" -C "${DIRS}/embbed"
#       echo "unzip postgresql success!"
#       rm -rf ${DIRS}/embbed/${PGSQL_VERSION}/${PGSQL_VERSION}.tar.gz
#   fi
# }

APP_HOME=${DIRS}
export APP_HOME


create_home
FILE_PATH=${DATA_HOME}/other/apply_run.txt  

rm -rf FILE_PATH ${FILE_PATH}

# echo ${FILE_PATH}

JAVA_OPTS=""
add_javaOpts(){
  APP_CONFIG=${DIRS}/conf
  APP_LOG=${DIRS}/logs

  JAVA_OPTS="$JAVA_OPTS -server -Xms512m -Xmx512m -Xmn128m -XX:ParallelGCThreads=20 -XX:+UseParallelGC -XX:MaxGCPauseMillis=850 -Xloggc:$APP_LOG/gc.log -Dfile.encoding=UTF-8"
  JAVA_OPTS="$JAVA_OPTS -DlogPath=$APP_LOG -Duser.timezone=GMT+08"
  JAVA_OPTS="$JAVA_OPTS -Dconf.config=file:${APP_CONFIG}"
  JAVA_OPTS="$JAVA_OPTS --add-opens java.base/java.lang=ALL-UNNAMED --add-opens java.sql/java.sql=ALL-UNNAMED  -classpath"
}

CLASSPATH=${DIRS}/conf
add_classpath(){
  #加载私有依赖
  for appJar in "${DIRS}"/lib/*.jar;
  do
     CLASSPATH="$CLASSPATH":"$appJar"
  done
}

db_port=0
pg_port(){
    db_port=$(awk -F": *" '/^postgresql:/ {
        inf=1
        next
    }
    inf && /^  db:/ {
        db=1
        next
    }
    db && /^    port:/ {
        print $2
        exit
    }' "${YAML}")

   # echo "PostgreSQL start Port: ${db_port}"
}

PID=0
getPID(){
    javaps=`$JAVA_HOME/bin/jps -l | grep $APP_MAIN`
    if [ -n "$javaps" ]; then
        PID=`echo $javaps | awk '{print $1}'`
    else
        PID=0
    fi
}

startup(){
    getPID
    echo "================================================================================================================"
    if [ $PID -ne 0 ]; then
        echo "$APP_MAIN already started(PID=$PID)"
        echo "================================================================================================================"
    else
        echo "starting $APP_MAIN"
        if [ ! -d "$APP_LOG" ]; then
            mkdir "$APP_LOG"
        fi

        nohup $JAVA_HOME/bin/java $JAVA_OPTS $CLASSPATH $APP_MAIN > /dev/null 2>&1 &

        for i in $(seq 5); do
            printf "."
            sleep 0.8
        done

        getPID

        if [ $PID -ne 0 ]; then
            echo "(PID=$PID)...[success]"
            output
        else
            echo "[failed]"
            echo "================================================================================================================"
        fi
    fi
}


find_apply_state(){

    MAX_RETRIES=30                    
    RETRY_COUNT=0                     

    # 循环检查文件内容
    while true; do
        # 检查文件是否存在
        if [ ! -f "$FILE_PATH" ]; then
            echo "."
            # echo "文件不存在: ${FILE_PATH}，等待文件创建... (重试次数: $RETRY_COUNT)"
        else
            # 读取文件的第一行内容
            FIRST_LINE=$(head -n 1 "$FILE_PATH")

            # 判断第一行内容是否为 1
            if [ "$FIRST_LINE" == "1" ]; then
                # echo "文件第一行内容为 1，继续执行..."
                echo "."
                break
            else
                echo "."
                # echo "文件第一行内容不是 1，等待 2 秒后重试... (重试次数: $RETRY_COUNT)"
            fi
        fi

        # 增加重试计数
        RETRY_COUNT=$((RETRY_COUNT + 1))

        # 判断是否超出最大重试次数
        if [ $RETRY_COUNT -ge $MAX_RETRIES ]; then
            echo "超过重试次数限制，退出脚本。"
            exit 1
        fi

        # 等待 2 秒
        sleep 2
    done
}


output(){

  dcs_port=$(awk -F": *" '/^dcs:/ {
      inf=1
      next
  }
  inf && /^  server:/ {
      server=1
      next
  }
  server && /^    port:/ {
      print $2
      exit
  }' "${YAML}")
  # echo "DCS Server Port: ${dcs_port}"

  server_port=$(awk -F": *" '/^server:/ {
      inf=1
      next
  }
  inf && /^  port:/ {
      print $2
      exit
  }' "${YAML}")
  echo "Apply Server Port: ${server_port}"

  # echo "PostgreSQL start Port: ${db_port}"

  if command -v ifconfig > /dev/null 2>&1; then
        ip_address=$(ifconfig | grep -Eo 'inet (addr:)?([0-9]*\.){3}[0-9]*' | grep -Eo '([0-9]*\.){3}[0-9]*' | grep -v '127.0.0.1' | head -n 1)
    else
        ip_address="127.0.0.1"
    fi

  echo "The application is starting. Please wait ......"
#  find_apply_state

  sleep 1

  echo "====================== Enter the following link in the browser to access ======================================="
  echo "http://${ip_address}:${server_port}"
  echo "================================================================================================================"



      # 打开默认浏览器访问 URL
    if command -v xdg-open > /dev/null; then
        # Linux 系统
        xdg-open "http://${ip_address}:${server_port}"
    elif command -v gnome-open > /dev/null; then
        # GNOME 桌面环境
        gnome-open "http://${ip_address}:${server_port}"
    elif command -v open > /dev/null; then
        # macOS 系统
        open "http://${ip_address}:${server_port}"
    else
        echo "无法检测到可用的浏览器打开命令，请手动访问: http://${ip_address}:${server_port}"
        exit 1
    fi


}




start(){
  # pg_port
  # create_home
  valid_jdk
  # valid_postgresql
  add_javaOpts
  add_classpath
  startup
}

start