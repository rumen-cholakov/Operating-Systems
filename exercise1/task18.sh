#!/bin/bash
cnt=0
upids=$(ps -elf|tail -n +2|tr -s ' '|cut -f3- -d' '|grep '^r '|cut -f2 -d' '|tr '\n' ' ')
for i in $upids; do
	cnt=$(($cnt+1))
	kill $i
done

echo $cnt
