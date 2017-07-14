#!/bin/bash

echo "Input a name:"

read name

who|grep -c ^$name

