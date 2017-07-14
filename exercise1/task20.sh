#!/bin/bash
ps -e -o ppid --sort ppid|tail -n +2|tr -s ' '|uniq -c|sort -t ' ' -k1 -n|while read numchildren parent;do
if [ $numchildren -gt 1 ]; then
echo "$numchildren $parent";
fi;
done|while read cildren proc;do
tochek=$(ps -e pid=$proc -o ppid|tail -n +2);
if [ $children -gt $(ps -e ppid=$tochek -o ppid|tail -n +2|tr -s ' '|uniq -c|tr -s ' '|cut -f2 -d') ];then
echo $proc;
fi;
done
