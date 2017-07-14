#!/bin/bash

dircont=$(find $1 -type f)
for file in $dircont;do
	if [ $(cat "${file}"|wc -c 2>/dev/null) -gt $2 ]
	then echo "$file"
	fi
done
