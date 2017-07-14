#!/bin/bash

number=$(( (RANDOM % 100) + 0 ))
count=0
while true;do
	count=$(($count+1))
	echo "Guess?"
	read guess
	if [ $guess -eq $number ];then
		echo "Right!!! Guessed $number in $count tries!"
		break
	elif [ $guess -gt $number ];then
		echo "..smaller!"
	else
		echo "..bigger!"
	fi
done
		
