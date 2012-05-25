/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains the implementations for the functions declared on
   "file_allocation.h". These functions deal with the FILE_ALLOCATION struct.
*/
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include "file_allocation.h"

FILE_ALLOCATION *construct_file_allocation(int number_of_files)
{
	FILE_ALLOCATION *new_file_allocation = NULL;	
	int *machines = NULL;

	assert(number_of_files > 0);
	
	new_file_allocation = 
			 (FILE_ALLOCATION *) malloc(sizeof(FILE_ALLOCATION));

	assert(new_file_allocation);
	
	machines = (int *) malloc(sizeof(int)*number_of_files);
	memset(machines, '\0', sizeof(int)*number_of_files);
	
	assert(machines);

	new_file_allocation->machines = machines;
	new_file_allocation->number_of_files = number_of_files;

	return new_file_allocation;
}

void destruct_file_allocation(FILE_ALLOCATION *file_allocation)
{
	assert(file_allocation);
	
	if (file_allocation->machines)
	{
		free(file_allocation->machines);
	}

	free(file_allocation);	
}

FILE_ALLOCATION *load_file_allocation(FILE *file, int number_of_files)
{
	int read_allocation = 0;
	int machine = 0;
	int reading_result = 0;
	FILE_ALLOCATION *file_allocation = NULL;

	assert(file);
	
	file_allocation = construct_file_allocation(number_of_files);
	assert(file_allocation);
	
	for (; read_allocation < number_of_files; read_allocation++)
	{
		reading_result = fscanf(file, "%d", &machine);
		assert(reading_result == 1);
		file_allocation->machines[read_allocation] = machine;
	}
	
	return file_allocation;	
}

int co_allocated(FILE_ALLOCATION *file_allocation, int file_index_1,
                                        int file_index_2)
{
	assert(file_allocation);
	assert(file_index_1 >= 0);
	assert(file_index_2 >= 0);
	
	return file_allocation->machines[file_index_1] == 
			file_allocation->machines[file_index_2];
}

int exist(FILE_ALLOCATION *file_allocation, int file_index)
{
	assert(file_allocation);
	assert(file_index >= 0);

	return file_allocation->machines[file_index] != -1;
}

