# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "../model_runner/model_runner.h"
# include "interface.h"

typedef enum {number_of_files, number_of_machines, 
		   duplication_level, remote_access_time, 	
		   local_access_time, popularity, machine, 
		   deduplicate_randomically} ARGUMENT_TYPE;

char *argument_representation[] = {"f", "m", "d", "r", "l", "p", "a"};

void stop(char *message)
{
	puts(message);
	exit(0);
}

void invalid_arguments(void)
{
	puts("Invalid use.");
	puts("Correct use: deduper destination file  mode  args");
	stop("");
}

void some_arguments_are_missing(void)
{
	stop("some arguments are missing");
}

void check_number_of_arguments(int argc)
{
	if (argc < 2)
	{
		invalid_arguments();
	}
}

ARGUMENT_TYPE get_argument_type(char *arg_type_string)
{
	ARGUMENT_TYPE arg_type;

	switch (arg_type_string[1])
	{
		case 'f': arg_type = number_of_files; break;
		case 'm': arg_type = number_of_machines; break;
		case 'd': arg_type = duplication_level; break;
		case 'r': arg_type = remote_access_time; break;
		case 'l': arg_type = local_access_time; break;
		case 'p': arg_type = popularity; break;
		case 'a': arg_type = machine; break;
		case 'x': arg_type = deduplicate_randomically; break; 
		default: invalid_arguments();	
	}

	return arg_type;
}

void get_argument_value(MODEL_RUNNER_ARGS *args, 
		ARGUMENT_TYPE type, char *arg_value_string)
{
	assert(args);
	assert(arg_value_string);

	switch(type)
	{
		case number_of_files:
		{
			int number_of_files = atoi(arg_value_string);
			if (number_of_files <= 0)
			{
				invalid_arguments();
			}
			
			args->number_of_files = number_of_files;	
		} break;
	
		case number_of_machines:
		{
			int number_of_machines = atoi(arg_value_string);
			if (number_of_machines <= 0)
			{
				invalid_arguments();
			}
			
			args->number_of_machines = number_of_machines;
		} break;
	
		case duplication_level:
		{
			double duplication_level = atof(arg_value_string);
		
			if (duplication_level < 0)
			{
				invalid_arguments();
			}

			args->duplication_level = duplication_level;
		} break;
		
		case remote_access_time:
		{
			double remote_access_time = atof(arg_value_string);
		
			if (remote_access_time < 0)
			{
				invalid_arguments();
			}			

			args->remote_access_time = remote_access_time;
		} break;

		case local_access_time:
		{
			double local_access_time = atof(arg_value_string);

			if (local_access_time < 0)
			{
				invalid_arguments();
			}

			args->local_access_time = local_access_time;	
		} break;
		
		case popularity:
		{
			int popularity = atoi(arg_value_string);
			if (popularity < 0)
			{
				invalid_arguments();
			}

			args->popularity = popularity;
			args->popularity_factor = popularity;
		} break;

		case machine:
		{
			int machine = atoi(arg_value_string);
			if (machine < 0)
			{
				invalid_arguments();
			}
			args->machine = machine;
		} break;
		
		case deduplicate_randomically:
		{
			int deduplicate_randomically = atoi(arg_value_string);
			if (deduplicate_randomically < 0)
			{
				invalid_arguments();
			}
			args->deduplicate_randomically = deduplicate_randomically;
		} break;
	}
}

void check_all_arguments_were_given(MODEL_RUNNER_ARGS *args)
{
	if (args->deduplicate_randomically == -1)
	{
		some_arguments_are_missing();
	}

	switch(args->mode)
	{
		case SAME_POPULARITY_EQUALIZED_STORAGE_MACHINE:
		{
			if (args->machine == -1)
			{
				some_arguments_are_missing();
			}
		}

		case SAME_POPULARITY_EQUALIZED_STORAGE:
		
		case SAME_POPULARITY_EQUALIZED_STORAGE_ALL_MACHINES:
		{
			if (args->number_of_files == -1     ||
	    		    args->number_of_machines == -1  ||
	    		    args->duplication_level == -1   ||
	    		    args->remote_access_time == -1  ||
	    		    args->local_access_time == -1   ||
	    		    args->popularity == -1)
			{
				some_arguments_are_missing();
			}
		} break;
		
		case LINEAR_POPULARITY_EQUALIZED_STORAGE:
		{
			if (args->number_of_files == -1     ||
	    		    args->number_of_machines == -1  ||
	    		    args->duplication_level == -1   ||
	    		    args->remote_access_time == -1  ||
	    		    args->local_access_time == -1   ||
	    		    args->popularity_factor == -1)
			{
				some_arguments_are_missing();
			}	
		} break;
	}
}

MODEL_RUNNER_MODE get_model_runner_mode_from_string(char *string)
{
	MODEL_RUNNER_MODE mode;

	switch(string[0])
	{
		case '0': mode = SAME_POPULARITY_EQUALIZED_STORAGE; break;
		case '1': mode = SAME_POPULARITY_EQUALIZED_STORAGE_MACHINE; break;
		case '2': mode = SAME_POPULARITY_EQUALIZED_STORAGE_ALL_MACHINES; break;
		case '3': mode = LINEAR_POPULARITY_EQUALIZED_STORAGE; break;
		default : invalid_arguments();
	}
	
	return mode;	
}

void print_results(MODEL_RUNNER_ARGS *model_runner_args, MODEL_RUNNER_RESULTS *model_runner_results, FILE *output_file)
{
	switch(model_runner_args->mode)
	{
		case SAME_POPULARITY_EQUALIZED_STORAGE:
		{

		}

		case LINEAR_POPULARITY_EQUALIZED_STORAGE:
		{
			
		}

		case SAME_POPULARITY_EQUALIZED_STORAGE_MACHINE:
		{
			fprintf(output_file, "%f    %f\n", model_runner_args->duplication_level, 
							   model_runner_results->time_access_impact);				
		} break;

		case SAME_POPULARITY_EQUALIZED_STORAGE_ALL_MACHINES:
		{
			int machine = 0;
			int number_of_machines = model_runner_args->number_of_machines;
			double *impacts = model_runner_results->time_access_impacts_all_machines;
		
			printf("impact duplication level=%f\n", model_runner_args->duplication_level);
			for (; machine < number_of_machines; machine++)
			{
				fprintf(output_file, "%d  %f\n", 
					machine, *(impacts + machine));
			}

			fprintf(output_file, "\n");
		} break;
	}
}

void run(int argc, char *argv[])
{
	int i = 0;
	ARGUMENT_TYPE arg_type;
	char *arg_value = NULL;
	MODEL_RUNNER_ARGS *model_runner_args = NULL; 
	MODEL_RUNNER_RESULTS *model_runner_results = NULL;	
	char *output_file_name = NULL;
	FILE *output_file = NULL;
	char *model_runner_mode_name = NULL;
	MODEL_RUNNER_MODE mode = 0;
	int *number_of_duplicatas_on_machines = NULL;

	model_runner_args = construct_model_runner_args(SAME_POPULARITY_EQUALIZED_STORAGE_ALL_MACHINES,
				    -1, -1, -1, -1, -1, -1, -1, -1, -1, NULL);

	check_number_of_arguments(argc);	

	output_file_name = argv[1];
	output_file = fopen(output_file_name, "a+");
	assert(output_file);

	model_runner_mode_name = argv[2];
	mode = get_model_runner_mode_from_string(model_runner_mode_name);

	model_runner_args->mode = mode;

	for (i = 3; i < argc; i+= 2)
	{
		arg_type = get_argument_type(argv[i]);
		arg_value = argv[i + 1];
		get_argument_value(model_runner_args, arg_type,
					arg_value);
	}

	check_all_arguments_were_given(model_runner_args);

	model_runner_args->number_of_duplicated_files = number_of_duplicatas_on_machines;
	
	model_runner_results = run_model(model_runner_args);	

	print_results(model_runner_args, model_runner_results, output_file);
	
	destruct_model_runner_args(model_runner_args);
	destruct_model_runner_results(model_runner_results);
	fclose(output_file);
}
