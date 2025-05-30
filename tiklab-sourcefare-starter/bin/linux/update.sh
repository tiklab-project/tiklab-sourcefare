#!/bin/sh

DIR=$(dirname "$PWD")

JAR_DIR=`find ${DIR}/lib -name "tiklab-install-starter*.jar" -print`

JAVA_HOME=${DIR}/embbed/jdk-16.0.2

if [ ! -d ${JAVA_HOME} ] ; then
  echo "The jdk program does not exist。"
  exit 1
fi

if [ -d ${JAR_DIR} ] ; then
  echo "The upgrade program does not exist。"
  exit 1
fi

cd ${JAVA_HOME}/bin && ./java -jar -Dfiledir="${DIR}" "${JAR_DIR}"

