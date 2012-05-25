#!/bin/bash

directory="41ed"
files=`ls`

function space()
{
	i=0
	while [ $i -lt 20 ] ;do
		echo
		i=`expr $i + 1`	
	done
}

space

for i in $files ; do
	if [ "`stat --format %f $i`" = $directory ]; then
		if [ $i != "interface" ]; then
			cd $i

			echo
			echo "-----------------"
			echo "testing   $i"
			echo "-----------------"
			echo

			make "clean" "all" "run"
			cd ..
		fi
	fi
done 

space
