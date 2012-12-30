#!/bin/bash

# Federal University of Campina Grande
# Distributed Systems Laboratory
# Author: Armstrong Mardilson da Silva Goes
# Contact: armstrongmsg@lsd.ufcg.edu.br

#
# This script integrates the tests running
#

files="deduplication_model deduplicator file_allocation file_popularity file_similarity matrixes model_input_generator model_runner timer" 

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
	cd $i
	echo
	echo "-----------------"
	echo "testing   $i"
	echo "-----------------"
	echo
	make "clean" "all" "run"
	cd ..
done 

space
