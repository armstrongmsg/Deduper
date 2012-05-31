#!/bin/bash

duplication_levels="0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1"
popularity_indexes="1 2 3 4 5 6 7 8 9 10"
number_of_files=10000
number_of_machines=10
remote_access_time=1000
local_access_time=100

echo
echo "running experiment"
echo

for popularity_index in $popularity_indexes ; do
	echo
	echo "popularity index=$popularity_index"
	echo
	results_file="results_popularity_factor_$popularity_index.txt"
	touch $results_file
	for duplication_level in $duplication_levels ; do
		./interface/deduper $results_file -f $number_of_files -m $number_of_machines -d $duplication_level -r $remote_access_time -l $local_access_time -p $popularity_index 
		echo
		echo
	done
done
