#!/bin/bash

read string
for file in $@;do
	echo "In file $file: $(cat $file|grep $string|wc -l)"
done
