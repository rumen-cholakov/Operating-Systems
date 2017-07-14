#!/bin/bash

echo "Input a full path to a directory"

read dir

echo "files: "
find /home/r/OS -maxdepth 1 -type f|wc -l
echo "diectory: "
find /home/r/OS -maxdepth 1  -type d|wc -l
