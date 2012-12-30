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

FILE_POPULARITY *generate_file_popularity_with_equal_value(int number_of_files, int number_of_machines, int popularity, FILE_ALLOCATION *file_allocation)
{
	FILE_POPULARITY *file_popularity = NULL;
	int i = 0;

	assert(number_of_files > 0);
	assert(number_of_machines > 0);
	assert(file_popularity >= 0);
	assert(file_allocation);

	file_popularity = construct_file_popularity(number_of_files, number_of_machines);

	for ( ; i < number_of_files*number_of_machines; i++)
	{
		int file = i/number_of_machines;
		int machine = i%number_of_machines;

		if (file_allocation->machines[file] == machine)
		{
			file_popularity->popularity[i] = popularity;	
		}
		else
		{
			file_popularity->popularity[i] = 0;
		}	
	}

	return file_popularity;
}

int is_divisible(int value_1, int value_2)
{
	return !value_2 ? 0 : value_1%value_2 == 0;
}

void set_file_popularities(FILE_POPULARITY *new_file_popularity, FILE_ALLOCATION *file_allocation, 
					int file, int local_popularity, int shared_popularity_per_machine)
{
	int machine;
	int number_of_machines = new_file_popularity->number_of_machines;

	for (machine = 0; machine < number_of_machines; machine++)
	{
		new_file_popularity->popularity[file*number_of_machines + machine] = 
						(file_allocation->machines[file] == machine) ? 
						local_popularity : shared_popularity_per_machine;
	}
}

void set_popularity_for_file(int file, FILE_POPULARITY *new_file_popularity, FILE_ALLOCATION *file_allocation, 
				int popularity, double shared_popularity_proportion)
{
	int number_of_machines = new_file_popularity->number_of_machines;
	int shared_popularity_value;
	int shared_popularity_per_machine;
	int local_popularity;
	
	/*
	   Only shares popularity if it is possible to divide the popularity using the 
	   given proportion
	*/
	shared_popularity_value = is_divisible(popularity, shared_popularity_proportion*100) ? 
						  popularity*shared_popularity_proportion : 0;

	shared_popularity_per_machine = shared_popularity_value;
	
	/*
	   This check != 1 avoids division by 0
	*/	
	if (number_of_machines != 1)
	{
		/*
		   Only shares popularity if it is possible to divide the popularity by the 
		   machines
		*/
		shared_popularity_per_machine = is_divisible(shared_popularity_value, number_of_machines - 1) ? 
						shared_popularity_value/(number_of_machines - 1) :
								0;
		shared_popularity_value = !shared_popularity_per_machine ? 0 : shared_popularity_value;	
	}	

	local_popularity = popularity - shared_popularity_value;

	set_file_popularities(new_file_popularity, file_allocation, file, local_popularity, 
					shared_popularity_per_machine);
}

FILE_POPULARITY *generate_file_popularity_using_function(int number_of_files, int number_of_machines, double shared_popularity_proportion,
                                                                FILE_ALLOCATION *file_allocation, POPULARITY_FUNCTION function)
{
	FILE_POPULARITY *new_file_popularity = NULL;
	int file;
	assert(number_of_files > 0);
	assert(number_of_machines > 0);
	assert(shared_popularity_proportion >= 0.0);
	assert(file_allocation);
	assert(function);	

	new_file_popularity = construct_file_popularity(number_of_files, number_of_machines);
	assert(new_file_popularity);

	for (file = 0; file < number_of_files; file++)
	{
		int popularity = function(file);

		set_popularity_for_file(file, new_file_popularity, file_allocation, popularity, 
							shared_popularity_proportion);
	}

	return new_file_popularity;
}





int *new_similar_files(int number_of_machines, int files_per_machine, 
			 int next_not_chosen)
{
	int *duplicated = (int *) malloc(sizeof(int)*number_of_machines);
	int machine = 0;	

	for ( ; machine < number_of_machines; machine++)
	{
		duplicated[machine] = machine*files_per_machine + next_not_chosen;
	}

	return duplicated;
}

void choose_similar_files(FILE_SIMILARITY *file_similarity, 
				int number_of_machines, 
				int files_per_machine, 
				int next_non_marked)
{
	int *duplicated = new_similar_files(number_of_machines, 
					files_per_machine,
					next_non_marked);
	set_similar_files(file_similarity, duplicated, 
				number_of_machines);

	free(duplicated);	
}


/*	
	for each group in groups_of_similar_files do
		for each machine do
			choose the next not-chosen file in machine to the group
		endfor

		set the file in group as similar
	endfor
*/

FILE_SIMILARITY *generate_file_similarity(FILE_ALLOCATION *file_allocation, double duplication_level)
{
	int number_of_files = file_allocation->number_of_files;
	int number_of_machines = file_allocation->machines[number_of_files - 1] + 1;
	FILE_SIMILARITY *file_similarity = NULL;
	int number_of_duplicated_files = ceil(number_of_files*duplication_level);
	int files_per_machine = number_of_files/number_of_machines;
	int similar_group = 0;

	assert(file_allocation);

	file_similarity = construct_file_similarity(number_of_files);	
	assert(file_similarity);
	
	for (; similar_group < number_of_duplicated_files/number_of_machines; similar_group++)
	{
		choose_similar_files(file_similarity, 
			number_of_machines, files_per_machine, 
				similar_group);
	}

	return file_similarity;
}
