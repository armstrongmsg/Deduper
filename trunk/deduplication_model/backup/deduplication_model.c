# include <stdlib.h>
# include "../file_allocation/file_allocation.h"
# include "../file_popularity/file_popularity.h"
# include "../file_similarity/file_similarity.h"
# include "deduplication_model.h"

# define REMOTE_ACCESS_TIME 1
# define LOCAL_ACCESS_TIME 0

double impact_for_file(int file_final_file_system, 
		       FILE_ALLOCATION *allocation_initial_system,
		       FILE_ALLOCATION *allocation_final_system,
		       FILE_SIMILARITY *file_similarity,
		       FILE_POPULARITY *file_popularity, 
		       double remote_access_time,
		       double local_access_time)
{
	double impact = 0.0;

	if (exist(allocation_final_system, file_final_file_system))
	{
		int *similar_files = 
			get_similar_files(file_final_file_system, 
					file_similarity);
		int index_similar_files = 0;
		while (similar_files[index_similar_files] != -1)
		{
			int similar_file = similar_files[index_similar_files];
			int co_alloc = co_allocated(allocation_initial_system,
					 file_final_file_system, 
					 similar_file);
			int popularity = file_popularity->popularity[similar_file];
			impact += ((1 - co_alloc)*remote_access_time +
					(co_alloc - 1)*local_access_time)*popularity; 	
			
			index_similar_files++;
		} 	
	}

	return impact;
}

double time_access_impact_per_operation(
                                FILE_ALLOCATION *allocation_initial_system,
                                FILE_ALLOCATION *allocation_final_system,
                                FILE_SIMILARITY *file_similarity,
                                FILE_POPULARITY *file_popularity, 
				double remote_access_time, 
				double local_access_time)
{
	int number_of_files = allocation_initial_system->number_of_files;
	int file_final_file_system = 0;
	double total_impact = 0.0;
	long total_accesses = system_popularity(file_popularity);

	for (; file_final_file_system < number_of_files; 
					file_final_file_system++)
	{
		total_impact += impact_for_file(file_final_file_system,
                                allocation_initial_system,
                                allocation_final_system,
                                file_similarity,
                                file_popularity, 
				remote_access_time, 
				local_access_time);
		/*
		if (exist(allocation_final_system, file_final_file_system))
		{
			int *similar_files = 
				get_similar_files(file_final_file_system, 
						file_similarity);
			int index_similar_files = 0;

			while (similar_files[index_similar_files] != -1)
			{
				int similar_file = similar_files[index_similar_files];
				int co_alloc = co_allocated(allocation_initial_system,
						 file_final_file_system, 
						 similar_file);
				int popularity = file_popularity->popularity[similar_file];
				total_impact += ((1 - co_alloc)*remote_access_time +
						(co_alloc - 1)*local_access_time)*popularity; 	
				
				index_similar_files++;
			} 	
		}*/		
	}		

	return total_accesses == 0 ? 0 : total_impact/total_accesses;
}
