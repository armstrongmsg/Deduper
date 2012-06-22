# !/bin/bash

# Federal University of Campina Grande
# Distributed Systems Laboratory
# Author: Armstrong Mardilson da Silva Goes
# Contact: armstrongmsg@lsd.ufcg.edu.br

#
# This script sets up the experiments environment
#

experiment_environment_directory="experiments_environment"

rm -f $experiment_environment_directory/binaries/*
rm -f $experiment_environment_directory/results_files/*

cp interface/deduper experiment.sh $experiment_environment_directory/binaries
cp results_summarizer.py $experiment_environment_directory/results_files
