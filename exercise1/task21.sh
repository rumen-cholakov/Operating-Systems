#!/bin/bash

if [ $# -ne 1 ];then
 exit 1
fi

ps -e -u $1 -o pid,rss,vsz --sort=-vsz|tail -n +2|tr -s ' '|while read pid rss vsz ;do
 if [ $vsz -ne 0 ];then
  echo "The RSS/VSZ ratio for process $pid is: "
  echo "scale=2; $rss/$vsz"|bc
 fi
done
