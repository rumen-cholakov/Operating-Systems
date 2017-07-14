#!/bin/bash
dircont=$(find $1 -type f)
sum=0
for file in $dircont;do
curr=$(cat "${file}" 2>/dev/null|wc -c)
if [ $curr -gt $2 ]
then sum=$(($sum+$curr))
fi
done
echo $sum
