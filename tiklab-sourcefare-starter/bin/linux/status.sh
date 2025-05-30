#!/bin/sh

DIRS=$(dirname "$PWD")
APP_MAIN="io.tiklab.sourcefare.starter.SourceFareApplication"

YAML=${DIRS}/conf/application.yaml

data_home=$(awk -F': ' '/DATA_HOME:/ {print $2}' "${YAML}")

JDK_VERSION=jdk-16.0.2
valid_jdk(){
  if [ -d "${DIRS}/embbed/${JDK_VERSION}" ]; then
      #echo "user embbed jdk ${JAVA_HOME}"
      JAVA_HOME="${DIRS}/embbed/${JDK_VERSION}"
  else
      echo "Unable to find embbed jdk!"
      exit 1;
  fi
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

   #echo "PostgreSQL start Port: ${db_port}"
}

db_enable="false"
pg_enable(){

    db_enable=$(awk -F": *" '/^postgresql:/ {
        inf=1
        next
    }
    inf && /^  embbed:/ {
        embbed=1
        next
    }
    embbed && /^    enable:/ {
        print $2
        exit
    }' "${YAML}")

   #echo "PostgreSQL embbed enable: ${db_enable}"
}

pgsql(){
  pg_enable
  pg_port
  if [ "${db_enable}" = "true" ]; then
    if [ "${db_port}" = "0" ]; then
        echo "find pgsql port error "
        exit 1
    fi

    pid_address=${data_home}/postgresql/postmaster.pid

    # 检查文件是否存在
    if [ -f "${pid_address}" ]; then
        pid=$(cat ${pid_address} | head -n 1)
         # shellcheck disable=SC2039
        if ps -p ${pid} > /dev/null 2>&1; then
            echo "pgsql is running(PID=${pid})"
        else
            echo "starting pgsql [failed]"
        fi
    else
        echo "unable to read pgsql status"
    fi
  fi
}

status(){
  valid_jdk
  getPID
  echo "================================================================================================================"
  if [ $PID -ne 0 ]; then
      echo "$APP_MAIN is running(PID=$PID)"
      pgsql
  else
      echo "$APP_MAIN is not running"
  fi
  echo "================================================================================================================"
}


status