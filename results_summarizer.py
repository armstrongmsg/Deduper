#!/usr/bin/python

class machine_results:
	
    def __init__(self):
        self.results = [0 for i in xrange(0, 11)]

    def __str__(self):
        representation = ""
        for i in xrange(len(self.results)):
            representation += str(self.results[i]) + ","
        return representation[0:len(representation) - 1]

class file_result:

    def __init__(self):
        self.results = [machine_results() for i in xrange(0, 10)]

    def __str__(self):
        representation = ""
        for i in xrange(len(self.results)):
            representation += "machine " + str(i) + "\n"
            representation += str(self.results[i]) + "\n"
        return representation

results_file_base_name = "results_experiment_4_run_"
files_results = file_result()#[file_result() for i in xrange(0, 10)]

for file_index in xrange(0, 100):
    file_name = results_file_base_name + str(file_index + 1) + ".txt"
    file = open(file_name, "r")

    for duplication_level in xrange(0, 11):
        for machine in xrange(0, 10):
            result = file.readline()
            result = result[0:len(result) - 2]
            impact = float(result.split("  ")[1])
            file_results.results[machine].results[duplication_level] += impact  

        file.readline()     

        for machine in xrange(0, 11):
            file.readline()
      
        file.readline()

for machine in xrange(0, 10):
    for duplication_level in xrange(0, 11):
        files_results.results[machine].results[duplication_level] /= (100.0)

print files_results
