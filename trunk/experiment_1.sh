#!/bin/bash

duplication_levels="0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1"
number_of_files=10000
number_of_machines=10
remote_access_time=1000
local_access_time=100
popularity=10

results_file="results.txt"

touch $results_file

echo
echo "running experiment"
echo

for duplication_level in $duplication_levels ; do
	./interface/deduper $results_file -f $number_of_files -m $number_of_machines -d $duplication_level -r $remote_access_time -l $local_access_time -p $popularity 
done
