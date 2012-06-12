/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains prototypes of functions that run the
   model with determined configurations.
*/

# ifndef MODEL_RUNNER_H
# define MODEL_RUNNER_H

enum mode {SAME_POPULARITY_EQUALIZED_STORAGE, 
	   SAME_POPULARITY_EQUALIZED_STORAGE_MACHINE,
	   SAME_POPULARITY_EQUALIZED_STORAGE_ALL_MACHINES,
	   LINEAR_POPULARITY_EQUALIZED_STORAGE};
typedef enum mode MODEL_RUNNER_MODE;

typedef struct
{
	MODEL_RUNNER_MODE mode;
	double duplication_level;
	int popularity;
	int number_of_files;
	int number_of_machines;
	double remote_access_time;
	double local_access_time;
	int deduplicate_randomically;
	int machine;
	int popularity_factor;
	int *number_of_duplicated_files;
} MODEL_RUNNER_ARGS;

typedef struct
{
	double time_access_impact;
	double *time_access_impacts_all_machines;
} MODEL_RUNNER_RESULTS;

MODEL_RUNNER_ARGS *construct_model_runner_args(
		MODEL_RUNNER_MODE mode,
		double duplication_level,
		int popularity,
		int number_of_files,
		int number_of_machines,
		double remote_access_time,
		double local_access_time,
		int deduplicate_randomically,
		int machine,
		int popularity_factor, 
		int *number_of_duplicated_files);

void destruct_model_runner_args(MODEL_RUNNER_ARGS *model_runner_args);

MODEL_RUNNER_RESULTS *construct_model_runner_results(
		double time_access_impact,
		double *time_access_impacts_all_machines);	
void destruct_model_runner_results(MODEL_RUNNER_RESULTS *model_runner_results);

/*
    Run the model with the given set of arguments
*/
MODEL_RUNNER_RESULTS *run_model(MODEL_RUNNER_ARGS *args);

/*
   This function will run the model using a generated input:
   1- the storage will be equalized. So all the machines will
      store approximately the same number of files.
   2- all the files will have the same popularity.
*/
double run_with_same_popularity_equalized_storage(
				double duplication_level,
				int popularity,
				int number_of_files,
				int number_of_machines,
				double remote_access_time,
				double local_access_time);

/*
   This function will run the model using a generated input:
   1- the storage will be equalized. So all the machines will
      store approximately the same number of files. 
   2- the files will have linear popularity. So the i-th file stored
      in a machine will have popularity equal to i*popularity_factor
*/
double run_with_linear_popularity_equalized_storage(
				double duplication_level,
				int popularity_factor,
				int number_of_files,
				int number_of_machines,
				double remote_access_time,
				double local_access_time);

/*
   This function will run the model using a generated input:
   1- the storage will be equalized. So all the machines will
      store approximately the same number of files.
   2- all the files will have the same popularity.

   The output will be the impact in the access of the files
   stored in the given machine.
*/
double run_with_same_popularity_impact_on_machine(
				double duplication_level,
				int popularity_factor,
				int number_of_files,
				int number_of_machines,
				double remote_access_time,
				double local_access_time, 
				int machine);

/*
   This function will run the model using a generated input
   1- the storage will be equalized. So all the machines will
      store approximately the same number of files.
   2- all the files will have the same popularity.

   The output will be a pointer to an array that stores the 
   impact in the access of the files stored in each machine.
*/
double *run_with_same_popularity_in_all_machines(
				double duplication_level,
				int popularity,
				int number_of_files,
				int number_of_machines,
				double remote_access_time,
				double local_access_time, 
				int *number_of_duplicated_files_in_machines);

# endif
