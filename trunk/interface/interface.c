# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <assert.h>
# include "../model_runner/model_runner.h"
# include "interface.h"

typedef enum {number_of_files, number_of_machines, 
		   duplication_level, remote_access_time, 	
		   local_access_time, popularity} ARGUMENT_TYPE;

char *argument_representation[] = {"f", "m", "d", "r", "l", "p"};

MODEL_RUNNER_ARGS *construct_model_runner_args()
{
	MODEL_RUNNER_ARGS *new_model_runner_args = 
			malloc(sizeof(MODEL_RUNNER_ARGS));

	assert(new_model_runner_args);	

	new_model_runner_args->number_of_files = -1;
	new_model_runner_args->number_of_machines = -1;
	new_model_runner_args->duplication_level = -1;
	new_model_runner_args->remote_access_time = -1;
	new_model_runner_args->local_access_time = -1;
	new_model_runner_args->popularity = -1;
	
	return new_model_runner_args;
}

void destruct_model_runner_args(MODEL_RUNNER_ARGS *args)
{
	assert(args);
	free(args);
}

void stop(char *message)
{
	puts(message);
	exit(0);
}

void invalid_arguments(void)
{
	puts("Invalid use.");
	puts("Correct use: deduper args");
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
				// stop execution
				// invalid value
			}
			
			args->number_of_files = number_of_files;	
		} break;
	
		case number_of_machines:
		{
			int number_of_machines = atoi(arg_value_string);
			if (number_of_machines <= 0)
			{
				// stop execution
				// invalid value
			}
			
			args->number_of_machines = number_of_machines;
		} break;
	
		case duplication_level:
		{
			double duplication_level = atof(arg_value_string);
		
			if (duplication_level < 0)
			{
				// stop execution
				// invalid value
			}

			args->duplication_level = duplication_level;
		} break;
		
		case remote_access_time:
		{
			double remote_access_time = atof(arg_value_string);
		
			if (remote_access_time < 0)
			{
				// stop execution
				// invalid value
			}			

			args->remote_access_time = remote_access_time;
		} break;

		case local_access_time:
		{
			double local_access_time = atof(arg_value_string);

			if (local_access_time < 0)
			{
				// stop execution
				// invalid value
			}

			args->local_access_time = local_access_time;	
		} break;
		
		case popularity:
		{
			int popularity = atoi(arg_value_string);
			if (popularity < 0)
			{
				// stop execution
				// invalid value
			}

			args->popularity = popularity;
		}
	}
}

void check_all_arguments_were_given(MODEL_RUNNER_ARGS *args)
{
	if (args->number_of_files == -1     ||
	    args->number_of_machines == -1  ||
	    args->duplication_level == -1 ||
	    args->remote_access_time == -1  ||
	    args->local_access_time == -1   ||
	    args->popularity == -1)
	{
		some_arguments_are_missing();	
	}
}

void run(int argc, char *argv[])
{
	int i = 0;
	ARGUMENT_TYPE arg_type;
	char *arg_value = NULL;
	MODEL_RUNNER_ARGS *model_runner_args = 
			construct_model_runner_args();	
	double impact = 0.0;
	char *output_file_name = NULL;
	FILE *output_file = NULL;

	check_number_of_arguments(argc);	

	output_file_name = argv[1];
	output_file = fopen(output_file_name, "a+");
	assert(output_file);

	for (i = 2; i < argc; i+= 2)
	{
		arg_type = get_argument_type(argv[i]);
		arg_value = argv[i + 1];
		get_argument_value(model_runner_args, arg_type,
					arg_value);
	}

	check_all_arguments_were_given(model_runner_args);
	
	impact = run_with_linear_popularity_equalized_storage(
				model_runner_args->duplication_level,
				model_runner_args->popularity,
				model_runner_args->number_of_files,
	    			model_runner_args->number_of_machines,
	    			model_runner_args->remote_access_time,
				model_runner_args->local_access_time);

	printf("impact per operation: %f\n", impact);
	fprintf(output_file, "%f  %f\n", 
			model_runner_args->duplication_level, 
			impact);

	destruct_model_runner_args(model_runner_args);
	fclose(output_file);
}
