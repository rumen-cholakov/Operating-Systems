#!/bin/bash
if [ $# -ne 1 ]
then exit 1
fi

color=( "\033[0;31m" "\033[0;32m" "\033[0;34m" );
case $1 in
-r) i=0;;
-g) i=1;;
-b) i=2;;
esac


while IFS= read -r line;do
if [ $1 = -x ];then
echo "${line}"
else
echo -e ${color[$i]}"${line}\033[0m"
i=$(( ($i+1)%3 ))
fi
done

