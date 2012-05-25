# include <stdio.h>
# include <assert.h>
# include "model_runner.h"
# include "../file_allocation/file_allocation.h"
# include "../file_similarity/file_similarity.h"
# include "../file_popularity/file_popularity.h"
# include "../model_input_generator/model_input_generator.h"
# include "../deduplicator/deduplicator.h"
# include "../deduplication_model/deduplication_model.h"

double run_with_same_popularity_equalized_storage(
                                double duplication_level,
                                int popularity,
                                int number_of_files,
                                int number_of_machines,
                                double remote_access_time,
                                double local_access_time)
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
	final_file_allocation = 						
		deduplicate(initial_file_allocation, 
				file_similarity);

	return time_access_impact_per_operation(
				initial_file_allocation, 
				final_file_allocation, 
				file_similarity, 
				file_popularity, 
				remote_access_time, 
				local_access_time);	
}

