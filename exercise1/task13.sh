#!/bin/bash

while true 
do
	sleep 1;
	if [[ $(who|cut -f1 -d' ')=~$1 ]]
	then
		echo "I'm killing myself!"
		kill $(pidof -x $0)
	fi
done
