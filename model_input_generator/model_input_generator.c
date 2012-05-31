# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include <math.h>
# include "../matrixes/matrixes.h"
# include "../file_allocation/file_allocation.h"
# include "../file_popularity/file_popularity.h"
# include "../file_similarity/file_similarity.h"
# include "model_input_generator.h"


FILE_ALLOCATION *generate_file_allocation(int number_of_files, int number_of_machines)
{
	FILE_ALLOCATION *new_file_allocation = NULL;
	int file_index = 0;
	int machine_index = 0;	
	int files_per_machine = 0;

	assert(number_of_files > 0);
	assert(number_of_machines > 0);

	new_file_allocation = construct_file_allocation(number_of_files);
	assert(new_file_allocation);
	
	files_per_machine = (int) ceil((float) number_of_files/ number_of_machines);		

	for (; file_index < number_of_files; file_index++)
	{
		if (!(file_index % files_per_machine) && file_index)
		{
			machine_index++;	
		}

		new_file_allocation->machines[file_index] = machine_index;
	}

	return new_file_allocation;
}

FILE_POPULARITY *generate_file_popularity_with_equal_value(int number_of_files, int popularity)
{
	FILE_POPULARITY *file_popularity = NULL;
	int i = 0;

	assert(number_of_files > 0);
	assert(file_popularity >= 0);

	file_popularity = construct_file_popularity(number_of_files);

	for ( ; i < number_of_files; i++)
	{
		file_popularity->popularity[i] = popularity;
	}

	return file_popularity;
}

int find_next_non_marked_file(int *marked_files, int start, int end)
{
	int i;

	for (i = start; i <= end; i++)
	{
		if (!marked_files[i])
		{
			return i;
		}
	}

	return -1;
}

/*
	for each machine
		file_in_machine := 1;
		
		while file_in_machine < number_of_files_in_machine do
			file_popularity := file_in_machine*popularity_factor
			file_in_machine := file_in_machine + 1;
		endwhile
	endfor
*/

FILE_POPULARITY *generate_file_popularity_with_linear_values(int popularity_factor, FILE_ALLOCATION *file_allocation)
{
	FILE_POPULARITY *new_file_popularity = NULL;
	int number_of_files = 0;
	int i = 0;
	int file_in_machine = 1;
	int machine = 0;

	assert(popularity_factor >= 0);
	assert(file_allocation);

	number_of_files = file_allocation->number_of_files;
	new_file_popularity = construct_file_popularity(number_of_files);
	
	assert(new_file_popularity);

	for ( ; i < number_of_files ; i++)
	{
		if (file_allocation->machines[i] != machine)
		{
			machine = file_allocation->machines[i];
			file_in_machine = 1;	
		}

		new_file_popularity->popularity[i] = file_in_machine*popularity_factor;		
		file_in_machine++;
	}

	return new_file_popularity;
}

FILE_SIMILARITY *generate_file_similarity(FILE_ALLOCATION *file_allocation, double duplication_level)
{
	int number_of_files = file_allocation->number_of_files;
	int number_of_machines = file_allocation->machines[number_of_files - 1] + 1;
	FILE_SIMILARITY *file_similarity = NULL;
	int *marked_files = NULL;
	int number_of_duplicated_files = ceil(number_of_files*duplication_level);
	int files_duplicated = 0;
	int files_per_machine = number_of_files/number_of_machines;

	assert(file_allocation);

	file_similarity = construct_file_similarity(number_of_files);	
	assert(file_similarity);
	
	marked_files = (int *) malloc(sizeof(int)*number_of_files);
	assert(marked_files);
	memset(marked_files, 0, sizeof(int)*number_of_files);
	
	while (files_duplicated < number_of_duplicated_files)
	{		
		int machine = 0;
		int *duplicated = (int *) malloc(sizeof(int)*number_of_machines);

		for ( ; machine < number_of_machines; machine++)
		{	
			int duplicated_file = find_next_non_marked_file(marked_files, 
						  machine*files_per_machine,
						  (machine + 1)*files_per_machine);	
			marked_files[duplicated_file] = 1;
			duplicated[machine] = duplicated_file;
		}
	
		files_duplicated += number_of_machines;
		set_similar_files(file_similarity, duplicated, 
					number_of_machines);

		free(duplicated);		
	}

	free(marked_files);

	return file_similarity;
}


