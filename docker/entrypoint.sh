#!/bin/bash

UNAME=`whoami`
EXEC_CMD=""
if [ $UNAME != root ];then
  sudo chown $UNAME:$UNAME /home/$UNAME
else
  UNAME=dockeruser
  USER_ID=60001
  GROUP_ID=60001
  echo "Start as \"$UNAME\"(UID: $USER_ID, GID: $GROUP_ID)"
  useradd -u $USER_ID -o -m $UNAME
  groupmod -g $GROUP_ID $UNAME
  export HOME=/home/$UNAME
  EXEC_CMD="`which gosu` $UNAME"
fi

if [ $# = 0 ]; then
  while : ; do sleep 3; done
else
  exec $EXEC_CMD "$@"  
fi