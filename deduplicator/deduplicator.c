# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "../file_allocation/file_allocation.h"
# include "../file_similarity/file_similarity.h"
# include "../random/random.h"
# include "deduplicator.h"

/*
	Algorithm used to deduplicate
	
	for each file on file_allocation do
		if file exists on new_allocation then
			get the files similar to file
			
			for each similar file do
				if similar file != file then
					exclude it from new_allocation
				endif
			endfor
		endif
	endfor
*/	

int number_of_elements(int *array)
{	
	int number = 0;

	while ((*array) != -1)
	{
		number++;
		array++;
	}

	return number;
}

void exclude_similar_files(int file, 
			int *similar_files, 
			FILE_ALLOCATION *new_allocation,
                        int randomically)
{
	int number_of_similar_files = 0;
	int file_to_keep_on_system = file;

	if (randomically)
	{
		number_of_similar_files = number_of_elements(similar_files);
		file_to_keep_on_system = choose_number(similar_files, 
					number_of_similar_files);
	}				 

	for ( ; *similar_files != -1; similar_files++)
	{
		if (*similar_files != file_to_keep_on_system)
		{
			new_allocation->machines[*similar_files] = -1;	
		}
	}
}

void deduplicate_file(int file_on_allocation, 
			FILE_ALLOCATION *file_allocation, 
			FILE_ALLOCATION *new_allocation, 
			FILE_SIMILARITY *file_similarity, 
			int randomically)
{
	if (exist(new_allocation, file_on_allocation))
	{
		int *similar_files = 
			get_similar_files(file_on_allocation, 
					file_similarity);	

		exclude_similar_files(file_on_allocation, similar_files, 
					new_allocation, randomically);	

		new_allocation->machines[file_on_allocation] = 
					file_allocation->machines[file_on_allocation];
		free(similar_files);
	}
}

FILE_ALLOCATION *deduplicate(FILE_ALLOCATION *file_allocation, 
                             FILE_SIMILARITY *file_similarity)
{
	FILE_ALLOCATION *new_allocation = NULL;
	int file_on_allocation = 0;
	int number_of_files = 0;	

	assert(file_allocation);
	assert(file_similarity);

	puts("deduplicating...");

	number_of_files = file_allocation->number_of_files;	
		
	new_allocation = construct_file_allocation(
				file_allocation->number_of_files);

	for ( ; file_on_allocation < number_of_files; file_on_allocation++)
	{
		deduplicate_file(file_on_allocation,
				file_allocation, 
				new_allocation, 
				file_similarity, 
				0);	
	}	

	return new_allocation;
}

FILE_ALLOCATION *deduplicate_randomically(FILE_ALLOCATION *file_allocation, 
					FILE_SIMILARITY *file_similarity)
{
	FILE_ALLOCATION *new_allocation = NULL;
	int file_on_allocation = 0;
	int number_of_files = 0;	

	assert(file_allocation);
	assert(file_similarity);

	puts("deduplicating...");

	number_of_files = file_allocation->number_of_files;	
	new_allocation = construct_file_allocation(
				file_allocation->number_of_files);
	
	for ( ; file_on_allocation < number_of_files; file_on_allocation++)
	{
		deduplicate_file(file_on_allocation,
				file_allocation, 
				new_allocation, 
				file_similarity, 
				1);	
	}	

	return new_allocation;
}

