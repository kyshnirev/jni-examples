#!/bin/sh

#
# build this project & run
#
# options:
#  no args - build this project
#  -run    - build and run main java class after
#  -clean  - remove all builds produced files
#

# logging to stdout
p() {
  [ "$1" = '' ] && echo '' || echo ">> $@"
}

# check last program exit status
e() {
  local EXIT_STATUS="$?"
  [ "$EXIT_STATUS" != "$1" ] && { p "ERROR: exit status $EXIT_STATUS != $@"; exit 1; }
}


#
# parse arguments
#
while [ "$1" != "" ]; do
  A="$1";
  shift;

  case "$A" in
    -clean) DO_CLEAN=true ;;
    -run)   DO_RUN=true ;;
    *)      p "unknown argument: $A" ;;
  esac
done;


if [ "$DO_CLEAN" = true ]; then
  rm -r $JAVA_BIN/*
  rm -r $C_BIN/*
  rm sources.list
  exit 0
fi


JAVA_SOURCE=src/main/java
JAVA_BIN=bin
C_BIN=bin
C_SOURCE=src/main/c


p "JAVA_HOME=$JAVA_HOME"
java -version 2>&1 | grep version
javac -version
javah -version
p '------------------------'

find $JAVA_SOURCE -name '*.java' | grep 'gk/tutorial/jni/call' > sources.list
p "compile java sources (`wc -l sources.list`)"
javac -verbose -d $JAVA_BIN @sources.list
e 0 'failed to compile java sources'

p "generate c-header into $C_SOURCE"
javah -verbose -classpath $JAVA_BIN -d $C_SOURCE gk.tutorial.jni.call.UnoNativeCall
e 0 'failed to generate c-header'

p "compile native code to $C_BIN/unolibo.so"
gcc -shared -fPIC -o unolibo.so -I/opt/jdk1.7.0_71/include -I/opt/jdk1.7.0_71/include/linux src/main/c/gk_tutorial_jni_call_UnoNativeCall.c
e 0 'failed to compile native shared library'

if [ "$DO_RUN" = true ]; then
  p "run java app"
  p
  java -cp $JAVA_BIN gk.tutorial.jni.call.RunJNINative
  e 0 'failed to run java app'
fi
