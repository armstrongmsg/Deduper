# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "../file_allocation/file_allocation.h"
# include "../file_similarity/file_similarity.h"
# include "../file_popularity/file_popularity.h"
# include "../model_input_generator/model_input_generator.h"
# include "../deduplicator/deduplicator.h"
# include "../deduplication_model/deduplication_model.h"
# include "model_runner.h"

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
                                double local_access_time, 
				int deduplicate_randomically);

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
                                double local_access_time, 
				int deduplicate_randomically);


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
                                int machine, 
				int deduplicate_randomically);


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
				int deduplicate_randomically);

/*
   MODEL_RUNNER_ARGS functions
*/

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
		int popularity_factor)
{
	MODEL_RUNNER_ARGS *new_args = NULL;

	assert(duplication_level >= -1);
	assert(popularity >= -1);
	assert(number_of_files >= -1);
	assert(number_of_machines >= -1);
	assert(remote_access_time >= -1);
	assert(local_access_time >= -1);
	assert(deduplicate_randomically >= -1);
	assert(machine >= -1);
	assert(popularity_factor >= -1);

	new_args = (MODEL_RUNNER_ARGS *) malloc(sizeof(MODEL_RUNNER_ARGS));

	assert(new_args);

	new_args->mode = mode;
	new_args->duplication_level = duplication_level;
	new_args->popularity = popularity;
	new_args->number_of_files = number_of_files;
	new_args->number_of_machines = number_of_machines;
	new_args->remote_access_time = remote_access_time;
	new_args->local_access_time = local_access_time;
	new_args->deduplicate_randomically = deduplicate_randomically;
	new_args->machine = machine;	
	new_args->popularity_factor = popularity_factor;

	return new_args;
}
			
MODEL_RUNNER_ARGS *construct_empty_model_runner_args(void)
{
	return construct_model_runner_args(0, -1, -1, -1, -1, -1, -1, -1, -1, -1);
}

void destruct_model_runner_args(MODEL_RUNNER_ARGS *model_runner_args)
{
	assert(model_runner_args);
	free(model_runner_args);
}


/*
   MODEL_RUNNER_RESULTS functions
*/

MODEL_RUNNER_RESULTS *construct_model_runner_results(
                double time_access_impact,
                double *time_access_impacts_all_machines)
{
	MODEL_RUNNER_RESULTS *new_results = NULL;

	assert(time_access_impact >= 0);

	new_results = (MODEL_RUNNER_RESULTS *) malloc(sizeof(MODEL_RUNNER_RESULTS));
	
	assert(new_results);

	new_results->time_access_impact = time_access_impact;
	new_results->time_access_impacts_all_machines = time_access_impacts_all_machines;

	return new_results;
}

void destruct_model_runner_results(MODEL_RUNNER_RESULTS *model_runner_results)
{
	assert(model_runner_results);

	if (model_runner_results->time_access_impacts_all_machines)
	{
		free(model_runner_results->time_access_impacts_all_machines);
	}

	free(model_runner_results);
}

MODEL_RUNNER_RESULTS *run_model(MODEL_RUNNER_ARGS *args)
{
	MODEL_RUNNER_RESULTS *results = NULL;
	double time_access_impact = 0.0;
	double *time_access_impacts_all_machines = NULL;	

	assert(args);

	switch(args->mode)
	{
		case SAME_POPULARITY_EQUALIZED_STORAGE:
		{
			time_access_impact = run_with_same_popularity_equalized_storage(
						args->duplication_level,
						args->popularity,
						args->number_of_files,
						args->number_of_machines,
						args->remote_access_time,
						args->local_access_time, 
						args->deduplicate_randomically);	
		} break;
		
		case SAME_POPULARITY_EQUALIZED_STORAGE_MACHINE:
		{
			time_access_impact = run_with_same_popularity_impact_on_machine(
						args->duplication_level,
						args->popularity,
						args->number_of_files,
						args->number_of_machines,
						args->remote_access_time,
						args->local_access_time,
						args->machine, 
						args->deduplicate_randomically);
		} break;	

		case SAME_POPULARITY_EQUALIZED_STORAGE_ALL_MACHINES:
		{
			time_access_impacts_all_machines = 
				run_with_same_popularity_in_all_machines(
						args->duplication_level, 
						args->popularity,
						args->number_of_files,
						args->number_of_machines,
						args->remote_access_time,
						args->local_access_time,
						args->deduplicate_randomically);
		} break;

		case LINEAR_POPULARITY_EQUALIZED_STORAGE:
		{
			time_access_impact = run_with_linear_popularity_equalized_storage(
						args->duplication_level,
						args->popularity_factor,
						args->number_of_files,
						args->number_of_machines,
						args->remote_access_time,
						args->local_access_time, 
						args->deduplicate_randomically);
		} break;
	}

	results = construct_model_runner_results(time_access_impact, 
						time_access_impacts_all_machines);

	return results;
}






double run_with_same_popularity_equalized_storage(
                                double duplication_level,
                                int popularity,
                                int number_of_files,
                                int number_of_machines,
                                double remote_access_time,
                                double local_access_time, 
				int randomically)
{
	FILE_ALLOCATION *initial_file_allocation = NULL;
	FILE_SIMILARITY *file_similarity = NULL;
	FILE_POPULARITY *file_popularity = NULL;	
	FILE_ALLOCATION *final_file_allocation = NULL; 
	
	assert(duplication_level >= 0);
	assert(popularity >= 0);
	assert(number_of_files > 0);
	assert(number_of_machines > 0);
	assert(remote_access_time >= 0);
	assert(local_access_time >= 0);	

	puts("generating initial file allocation...");
	initial_file_allocation = 
		generate_file_allocation(number_of_files, 
						number_of_machines);	

	puts("generating file similarity...");
	file_similarity = 
		generate_file_similarity(initial_file_allocation, 
						duplication_level);

	puts("generating file popularity...");
	file_popularity = 
		generate_file_popularity_with_equal_value(number_of_files, 
						popularity);

	puts("generating final file allocation...");
	final_file_allocation = ( randomically ?						
		deduplicate_randomically(initial_file_allocation, file_similarity) :
		deduplicate(initial_file_allocation, file_similarity) );

	double impact = time_access_impact_per_operation(
				initial_file_allocation, 
				final_file_allocation, 
				file_similarity, 
				file_popularity, 
				remote_access_time, 
				local_access_time);	

	destruct_file_allocation(initial_file_allocation);
	destruct_file_allocation(final_file_allocation);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);	

	return impact;
}

double run_with_linear_popularity_equalized_storage(
                                double duplication_level,
                                int popularity_factor,
                                int number_of_files,
                                int number_of_machines,
                                double remote_access_time,
                                double local_access_time,
				int randomically)
{
	FILE_ALLOCATION *initial_file_allocation = NULL;
	FILE_SIMILARITY *file_similarity = NULL;
	FILE_POPULARITY *file_popularity = NULL;	
	FILE_ALLOCATION *final_file_allocation = NULL; 
	
	assert(duplication_level >= 0);
	assert(popularity_factor >= 0);
	assert(number_of_files > 0);
	assert(number_of_machines > 0);
	assert(remote_access_time >= 0);
	assert(local_access_time >= 0);	

	puts("generating initial file allocation...");
	initial_file_allocation = 
		generate_file_allocation(number_of_files, 
						number_of_machines);	

	puts("generating file similarity...");
	file_similarity = 
		generate_file_similarity(initial_file_allocation, 
						duplication_level);

	puts("generating file popularity...");
	file_popularity = 
		generate_file_popularity_with_linear_values(popularity_factor,
						initial_file_allocation);

	puts("generating final file allocation...");
	final_file_allocation = ( randomically ?						
		deduplicate_randomically(initial_file_allocation, file_similarity) :
		deduplicate(initial_file_allocation, file_similarity) );

	double impact =  time_access_impact_per_operation(
				initial_file_allocation, 
				final_file_allocation, 
				file_similarity, 
				file_popularity, 
				remote_access_time, 
				local_access_time);	
	
	destruct_file_allocation(initial_file_allocation);
	destruct_file_allocation(final_file_allocation);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);	
	
	return impact;
}

double *run_with_same_popularity_in_all_machines(
                                double duplication_level,
                                int popularity,
                                int number_of_files,
                                int number_of_machines,
                                double remote_access_time,
                                double local_access_time, 
				int randomically)
{
	FILE_ALLOCATION *initial_file_allocation = NULL;
	FILE_SIMILARITY *file_similarity = NULL;
	FILE_POPULARITY *file_popularity = NULL;	
	FILE_ALLOCATION *final_file_allocation = NULL; 
	double *impacts = NULL;	
	int machine = 0;

	assert(duplication_level >= 0);
	assert(popularity >= 0);
	assert(number_of_files > 0);
	assert(number_of_machines > 0);
	assert(remote_access_time >= 0);
	assert(local_access_time >= 0);	
	assert(machine >= 0);

	impacts = (double *) malloc(sizeof(double)*number_of_machines);

	assert(impacts);

	puts("generating initial file allocation...");
	initial_file_allocation = 
		generate_file_allocation(number_of_files, 
						number_of_machines);	

	puts("generating file similarity...");
	file_similarity = 
		generate_file_similarity(initial_file_allocation, 
						duplication_level);

	puts("generating file popularity...");
	file_popularity = 
		generate_file_popularity_with_equal_value(number_of_files, 
						popularity);

	puts("generating final file allocation...");
	final_file_allocation = ( randomically ?						
		deduplicate_randomically(initial_file_allocation, file_similarity) :
		deduplicate(initial_file_allocation, file_similarity) );

	for (machine = 0 ; machine < number_of_machines; machine++)
	{
		double impact = time_access_impact_per_operation_on_machine(
			 initial_file_allocation,
			 final_file_allocation, 
			 file_similarity,
			 file_popularity,
			 remote_access_time,
			 local_access_time,
			 machine);
		impacts[machine] = impact; 
	}

	destruct_file_allocation(initial_file_allocation);
	destruct_file_allocation(final_file_allocation);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);	

	return impacts;
}

double run_with_same_popularity_impact_on_machine(
                                double duplication_level,
                                int popularity,
                                int number_of_files,
                                int number_of_machines,
                                double remote_access_time,
                                double local_access_time,
                                int machine, 
				int randomically)
{
	FILE_ALLOCATION *initial_file_allocation = NULL;
	FILE_SIMILARITY *file_similarity = NULL;
	FILE_POPULARITY *file_popularity = NULL;	
	FILE_ALLOCATION *final_file_allocation = NULL; 
	
	assert(duplication_level >= 0);
	assert(popularity >= 0);
	assert(number_of_files > 0);
	assert(number_of_machines > 0);
	assert(remote_access_time >= 0);
	assert(local_access_time >= 0);	
	assert(machine >= 0);

	puts("generating initial file allocation...");
	initial_file_allocation = 
		generate_file_allocation(number_of_files, 
						number_of_machines);	
	
	puts("generating file similarity...");
	file_similarity = 
		generate_file_similarity(initial_file_allocation, 
						duplication_level);

	puts("generating file popularity...");
	file_popularity = 
		generate_file_popularity_with_equal_value(number_of_files, 
						popularity);

	puts("generating final file allocation...");
	final_file_allocation = ( randomically ?						
		deduplicate_randomically(initial_file_allocation, file_similarity) :
		deduplicate(initial_file_allocation, file_similarity) );

	double impact =  time_access_impact_per_operation_on_machine(
			 initial_file_allocation,
			 final_file_allocation, 
			 file_similarity,
			 file_popularity,
			 remote_access_time,
			 local_access_time,
			 machine);

	destruct_file_allocation(initial_file_allocation);
	destruct_file_allocation(final_file_allocation);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);	

	return impact;
}
