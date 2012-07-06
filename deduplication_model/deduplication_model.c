# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include "../file_allocation/file_allocation.h"
# include "../file_popularity/file_popularity.h"
# include "../file_similarity/file_similarity.h"
# include "deduplication_model.h"

double impact_for_similar_file(int file_final_file_system, 
			       int similar_file, 
			       FILE_ALLOCATION *allocation_initial_system,
			       FILE_POPULARITY *file_popularity, 
			       double remote_access_time,
			       double local_access_time)
{
	int co_alloc = co_allocated(allocation_initial_system,
			 file_final_file_system, 
			 similar_file);
	int popularity = file_popularity->popularity[similar_file*file_popularity->number_of_machines + allocation_initial_system->machines[similar_file]];
//	int popularity = file_popularity->popularity[similar_file];
	return ((1 - co_alloc)*remote_access_time +
			(co_alloc - 1)*local_access_time)*popularity; 	
}

double impact_for_similar_files(int file_final_file_system,
				int *similar_files, 
			        FILE_ALLOCATION *allocation_initial_system,
			        FILE_POPULARITY *file_popularity, 
			        double remote_access_time,
			        double local_access_time)
{
	int index_similar_files = 0;
	double impact = 0.0;

	for ( ; similar_files[index_similar_files] != -1; index_similar_files++)
	{
		int similar_file = similar_files[index_similar_files];
		impact += impact_for_similar_file(file_final_file_system,
				similar_file,
				allocation_initial_system,
				file_popularity,
				remote_access_time,
				local_access_time);
	}		

	return impact;
}

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
		
		impact += impact_for_similar_files(file_final_file_system,
					similar_files,
					allocation_initial_system,
					file_popularity,
					remote_access_time,
					local_access_time);		
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

	puts("Calculating impact...");

	for (; file_final_file_system < number_of_files; 
					file_final_file_system++)
	{
		double impact = impact_for_file(file_final_file_system,
                                allocation_initial_system,
                                allocation_final_system,
                                file_similarity,
                                file_popularity, 
				remote_access_time, 
				local_access_time);
		total_impact += impact;
	}		

	return (total_accesses == 0) ? 0 : (total_impact/total_accesses);
}

double get_time_after_deduplication(FILE_ALLOCATION *allocation_initial_system,
				    FILE_ALLOCATION *allocation_final_system,
				    FILE_SIMILARITY *file_similarity,
				    FILE_POPULARITY *file_popularity,
				    int file, 
				    double remote_access_time,
			            double local_access_time)
{
	int file_was_deleted = (allocation_final_system->machines[file] == -1);
	int popularity = file_popularity->popularity[file*file_popularity->number_of_machines + allocation_initial_system->machines[file]];
	int remote_access = file_was_deleted && 
			!there_is_similar_file_on_machine_after_deduplication(file_similarity,
				      allocation_initial_system, 
				      allocation_final_system, 
				      file);

	return (remote_access ? remote_access_time*popularity:
				 local_access_time*popularity);
}

double time_access_impact_per_operation_on_machine(     
                                FILE_ALLOCATION *allocation_initial_system, 
                                FILE_ALLOCATION *allocation_final_system,
                                FILE_SIMILARITY *file_similarity,
                                FILE_POPULARITY *file_popularity, 
                                double remote_access_time, 
                                double local_access_time,
                                int machine)
{
	int file = 0;
	int number_of_files = 0;
	double time_access_impact = 0.0;
	double time_before_deduplication = 0.0;
	double time_after_deduplication = 0.0;
	int total_number_of_operations = 0;

	assert(allocation_initial_system);
	assert(allocation_final_system);
	assert(file_similarity);
	assert(file_popularity);
	assert(remote_access_time >= 0);
	assert(local_access_time >= 0);
	assert(machine >= 0);

	number_of_files = allocation_final_system->number_of_files;

	for ( ; file < number_of_files; file++)
	{
		if (allocation_initial_system->machines[file] == machine)
		{
			total_number_of_operations += file_popularity->popularity[file];	
			time_before_deduplication = local_access_time*file_popularity->popularity[file];
			time_after_deduplication = get_time_after_deduplication(allocation_initial_system,
				    allocation_final_system,
				    file_similarity,
				    file_popularity,
				    file, 
				    remote_access_time,
			            local_access_time);
			
			time_access_impact += (time_after_deduplication - time_before_deduplication);
		}
	}

	return time_access_impact/total_number_of_operations;
}

