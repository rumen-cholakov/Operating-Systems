#!/bin/bash

read file 
read string

cat $file|grep $string > /dev/null

echo $?
