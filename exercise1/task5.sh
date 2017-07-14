#!/bin/bash

name=$(whoami)
if [[ $name =~ ^s[:digit:]+ ]]
	 then echo "hi"
else 
	echo "Danger it's a teacher"
fi
