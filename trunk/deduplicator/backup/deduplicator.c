# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "../file_allocation/file_allocation.h"
# include "../file_similarity/file_similarity.h"
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

void deduplicate_file(int file_on_allocation, 
			FILE_ALLOCATION *file_allocation, 
			FILE_ALLOCATION *new_allocation, 
			FILE_SIMILARITY *file_similarity)
{
	if (exist(new_allocation, file_on_allocation))
	{
		int *similar_files = 
			get_similar_files(file_on_allocation, 
					file_similarity);	
		int *iter_similar_files = similar_files;		
	
		for ( ; *iter_similar_files != -1; iter_similar_files++)
		{
			if (*iter_similar_files != file_on_allocation)
			{
				new_allocation->machines[*iter_similar_files] = -1;	
			}
		}
	
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
	int number_of_machines = 0;

	assert(file_allocation);
	assert(file_similarity);

	number_of_files = file_allocation->number_of_files;	
	number_of_machines = 
		file_allocation->machines[number_of_files - 1] + 1;

	new_allocation = construct_file_allocation(
				file_allocation->number_of_files);
	
	for ( ; file_on_allocation < number_of_files; file_on_allocation++)
	{
		deduplicate_file(file_on_allocation,
				file_allocation, 
				new_allocation, 
				file_similarity);
		
		/*
		if (exist(new_allocation, file_on_allocation))
		{
			int *similar_files = 
				get_similar_files(file_on_allocation, 
						file_similarity);	
			int *iter_similar_files = similar_files;			

			for ( ; *iter_similar_files != -1; iter_similar_files++)
			{
				if (*iter_similar_files != file_on_allocation)
				{
					new_allocation->machines[*iter_similar_files] = -1;	
				}
			}
		
			new_allocation->machines[file_on_allocation] = 
						file_allocation->machines[file_on_allocation];
			free(similar_files);
		*/
	//	}			
	}	

	return new_allocation;
}

