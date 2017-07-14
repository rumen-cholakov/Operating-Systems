#!/bin/bash
number_of_files=0
while read -d ':' line;do
	if [[ -d ${line} ]];then 
	number_of_files=$(( $number_of_files + $(find $line -type f -executable|wc -l) ))
	fi
done< <(echo $PATH)

echo $number_of_files
