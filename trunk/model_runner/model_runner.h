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
		int popularity_factor);

void destruct_model_runner_args(MODEL_RUNNER_ARGS *model_runner_args);

MODEL_RUNNER_RESULTS *construct_model_runner_results(
		double time_access_impact,
		double *time_access_impacts_all_machines);	
void destruct_model_runner_results(MODEL_RUNNER_RESULTS *model_runner_results);

/*
    Run the model with the given set of arguments
*/
MODEL_RUNNER_RESULTS *run_model(MODEL_RUNNER_ARGS *args);

# endif
