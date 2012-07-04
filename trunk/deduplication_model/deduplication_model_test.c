# include <stdio.h>
# include <assert.h>
# include <math.h>
# include "../file_allocation/file_allocation.h"
# include "../file_similarity/file_similarity.h"
# include "../file_popularity/file_popularity.h"
# include "deduplication_model.h"

double abs2(double d)
{
	return d < 0 ? -1*d : d;
}

void time_access_impact_per_operation_test_1()
{
	/*
	   There is only one machine, where are stored two similar files.
	   After deduplication, the expected impact is zero.
	*/
	int number_of_files = 2;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 2);
	int local_access_time = 0;
	int remote_access_time = 1;

	/*
	   Two files stored on the same machine.
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;

	/*
	   File 1 was deleted by deduplication.
	*/
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = -1;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;

	/*
	   Similarity file 1
	*/	
	file_similarity->similar_files[0*2 + 0] = 1;
	file_similarity->similar_files[0*2 + 1] = 1;

	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[1*2 + 0] = 1;
	file_similarity->similar_files[1*2 + 1] = 1;	

	assert(!time_access_impact_per_operation(allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time));

	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

void time_access_impact_per_operation_test_2()
{
	/*
	   There is two machines:
	     machine      files 
	 	0	   0,1
		1	    2
	*/
	int number_of_files = 3;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 2);
	int local_access_time = 0;
	int remote_access_time = 1;
	double impact_per_operation = 0.0;

	/*
	   Files 0 and 1 -> machine 0
	   Files 2 -> machine 1
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;
	allocation_initial_system->machines[2] = 1;

	/*
	   Files 1 and 2 were deleted by deduplication.
	*/
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = -1;
	allocation_final_system->machines[2] = -1;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;
	file_popularity->popularity[2] = 10;

	/*
	   Similarity file 1
	*/	
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	file_similarity->similar_files[0*number_of_files + 1] = 1;
	file_similarity->similar_files[0*number_of_files + 2] = 1;

	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[1*number_of_files + 0] = 1;
	file_similarity->similar_files[1*number_of_files + 1] = 1;	
	file_similarity->similar_files[1*number_of_files + 2] = 1;

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[2*number_of_files + 0] = 1;
	file_similarity->similar_files[2*number_of_files + 1] = 1;	
	file_similarity->similar_files[2*number_of_files + 2] = 1;

	impact_per_operation = time_access_impact_per_operation(allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time);

	assert(abs2(impact_per_operation - 1.0/3) < 0.1);

	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

void time_access_impact_per_operation_test_3()
{
	/*
	   There are three machines:
		machine    files
		   0       0,1,2
		   1        3,4
		   2        5,6
	*/
	int number_of_files = 7;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 3);
	int local_access_time = 0;
	int remote_access_time = 1;
	double impact_per_operation = 0.0;

	/*
	   Files 0,1,2 -> machine 0
	   Files 3,4 -> machine 1
	   Files 5,6 -> machine 2
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;
	allocation_initial_system->machines[2] = 0;
	allocation_initial_system->machines[3] = 1;
	allocation_initial_system->machines[4] = 1;
	allocation_initial_system->machines[5] = 2;
	allocation_initial_system->machines[6] = 2;

	/*
	   Files 1, 3, 4 and 5 were deleted by deduplication.
	*/	
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = -1;
	allocation_final_system->machines[2] = 0;
	allocation_final_system->machines[3] = -1;
	allocation_final_system->machines[4] = -1;
	allocation_final_system->machines[5] = -1;
	allocation_final_system->machines[6] = 2;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;
	file_popularity->popularity[2] = 10;
	file_popularity->popularity[3] = 10;
	file_popularity->popularity[4] = 10;
	file_popularity->popularity[5] = 10;
	file_popularity->popularity[6] = 10;

	/*
	   Similarity file 0
	*/	
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	file_similarity->similar_files[0*number_of_files + 1] = 1;
	file_similarity->similar_files[0*number_of_files + 3] = 1;
	file_similarity->similar_files[0*number_of_files + 5] = 1;

	/*
	   Similarity file 1
	*/
	file_similarity->similar_files[1*number_of_files + 0] = 1;
	file_similarity->similar_files[1*number_of_files + 1] = 1;	
	file_similarity->similar_files[1*number_of_files + 3] = 1;
	file_similarity->similar_files[1*number_of_files + 5] = 1;

	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[2*number_of_files + 2] = 1;
	file_similarity->similar_files[2*number_of_files + 4] = 1;	

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[3*number_of_files + 0] = 1;
	file_similarity->similar_files[3*number_of_files + 1] = 1;	
	file_similarity->similar_files[3*number_of_files + 3] = 1;
	file_similarity->similar_files[3*number_of_files + 5] = 1;

	/*
	   Similarity file 4
	*/
	file_similarity->similar_files[4*number_of_files + 2] = 1;
	file_similarity->similar_files[4*number_of_files + 4] = 1;	

	/*
	   Similarity file 5
	*/
	file_similarity->similar_files[5*number_of_files + 0] = 1;
	file_similarity->similar_files[5*number_of_files + 1] = 1;	
	file_similarity->similar_files[5*number_of_files + 3] = 1;
	file_similarity->similar_files[5*number_of_files + 5] = 1;

	/*
	   Similarity file 6
	*/
	file_similarity->similar_files[6*number_of_files + 6] = 1;

	impact_per_operation = time_access_impact_per_operation(allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time);

	assert(abs2(impact_per_operation - 0.43) < 0.1);

	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

void time_access_impact_per_operation_on_machine_test_1(void)
{
	/*
	   There are three machines:
		machine    files
		   0       0,1,2
		   1        3,4
		   2        5,6
	*/
	int number_of_files = 7;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 3);
	int local_access_time = 0;
	int remote_access_time = 1;
	double impact_per_operation = 0.0;

	/*
	   Files 0,1,2 -> machine 0
	   Files 3,4 -> machine 1
	   Files 5,6 -> machine 2
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;
	allocation_initial_system->machines[2] = 0;
	allocation_initial_system->machines[3] = 1;
	allocation_initial_system->machines[4] = 1;
	allocation_initial_system->machines[5] = 2;
	allocation_initial_system->machines[6] = 2;

	/*
	   Files 1, 3, 4 and 5 were deleted by deduplication.
	*/	
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = -1;
	allocation_final_system->machines[2] = 0;
	allocation_final_system->machines[3] = -1;
	allocation_final_system->machines[4] = -1;
	allocation_final_system->machines[5] = -1;
	allocation_final_system->machines[6] = 2;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;
	file_popularity->popularity[2] = 10;
	file_popularity->popularity[3] = 10;
	file_popularity->popularity[4] = 10;
	file_popularity->popularity[5] = 10;
	file_popularity->popularity[6] = 10;

	/*
	   Similarity file 0
	*/	
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	file_similarity->similar_files[0*number_of_files + 1] = 1;
	file_similarity->similar_files[0*number_of_files + 3] = 1;
	file_similarity->similar_files[0*number_of_files + 5] = 1;

	/*
	   Similarity file 1
	*/
	file_similarity->similar_files[1*number_of_files + 0] = 1;
	file_similarity->similar_files[1*number_of_files + 1] = 1;	
	file_similarity->similar_files[1*number_of_files + 3] = 1;
	file_similarity->similar_files[1*number_of_files + 5] = 1;

	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[2*number_of_files + 2] = 1;
	file_similarity->similar_files[2*number_of_files + 4] = 1;	

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[3*number_of_files + 0] = 1;
	file_similarity->similar_files[3*number_of_files + 1] = 1;	
	file_similarity->similar_files[3*number_of_files + 3] = 1;
	file_similarity->similar_files[3*number_of_files + 5] = 1;

	/*
	   Similarity file 4
	*/
	file_similarity->similar_files[4*number_of_files + 2] = 1;
	file_similarity->similar_files[4*number_of_files + 4] = 1;	

	/*
	   Similarity file 5
	*/
	file_similarity->similar_files[5*number_of_files + 0] = 1;
	file_similarity->similar_files[5*number_of_files + 1] = 1;	
	file_similarity->similar_files[5*number_of_files + 3] = 1;
	file_similarity->similar_files[5*number_of_files + 5] = 1;

	/*
	   Similarity file 6
	*/
	file_similarity->similar_files[6*number_of_files + 6] = 1;

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					0);

	assert(abs2(impact_per_operation - 0) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					1);

	assert(abs2(impact_per_operation - 1) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					2);

	assert(abs2(impact_per_operation - 0.5) < 0.1);
	
	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

void time_access_impact_per_operation_on_machine_test_2(void)
{
	/*
	   There are three machines:
		machine    files
		   0       0,1,2
		   1        3,4
		   2        5,6
	*/
	int number_of_files = 7;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 3);
	int local_access_time = 0;
	int remote_access_time = 1;
	double impact_per_operation = 0.0;

	/*
	   Files 0,1,2 -> machine 0
	   Files 3,4 -> machine 1
	   Files 5,6 -> machine 2
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;
	allocation_initial_system->machines[2] = 0;
	allocation_initial_system->machines[3] = 1;
	allocation_initial_system->machines[4] = 1;
	allocation_initial_system->machines[5] = 2;
	allocation_initial_system->machines[6] = 2;

	/*
	   Files 1, 3, 4 and 5 were deleted by deduplication.
	*/	
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = -1;
	allocation_final_system->machines[2] = -1;
	allocation_final_system->machines[3] = -1;
	allocation_final_system->machines[4] = 1;
	allocation_final_system->machines[5] = -1;
	allocation_final_system->machines[6] = 2;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;
	file_popularity->popularity[2] = 10;
	file_popularity->popularity[3] = 10;
	file_popularity->popularity[4] = 10;
	file_popularity->popularity[5] = 10;
	file_popularity->popularity[6] = 10;

	/*
	   Similarity file 0
	*/	
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	file_similarity->similar_files[0*number_of_files + 1] = 1;
	file_similarity->similar_files[0*number_of_files + 3] = 1;
	file_similarity->similar_files[0*number_of_files + 5] = 1;

	/*
	   Similarity file 1
	*/
	file_similarity->similar_files[1*number_of_files + 0] = 1;
	file_similarity->similar_files[1*number_of_files + 1] = 1;	
	file_similarity->similar_files[1*number_of_files + 3] = 1;
	file_similarity->similar_files[1*number_of_files + 5] = 1;

	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[2*number_of_files + 2] = 1;
	file_similarity->similar_files[2*number_of_files + 4] = 1;	

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[3*number_of_files + 0] = 1;
	file_similarity->similar_files[3*number_of_files + 1] = 1;	
	file_similarity->similar_files[3*number_of_files + 3] = 1;
	file_similarity->similar_files[3*number_of_files + 5] = 1;

	/*
	   Similarity file 4
	*/
	file_similarity->similar_files[4*number_of_files + 2] = 1;
	file_similarity->similar_files[4*number_of_files + 4] = 1;	

	/*
	   Similarity file 5
	*/
	file_similarity->similar_files[5*number_of_files + 0] = 1;
	file_similarity->similar_files[5*number_of_files + 1] = 1;	
	file_similarity->similar_files[5*number_of_files + 3] = 1;
	file_similarity->similar_files[5*number_of_files + 5] = 1;

	/*
	   Similarity file 6
	*/
	file_similarity->similar_files[6*number_of_files + 6] = 1;

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					0);


	assert(abs2(impact_per_operation - 1/3.0) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					1);

	assert(abs2(impact_per_operation - 0.5) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					2);

	assert(abs2(impact_per_operation - 0.5) < 0.1);
	
	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

void time_access_impact_per_operation_on_machine_test_3(void)
{
	/*
	   There are three machines:
		machine    files
		   0       0,1,2
		   1        3,4
		   2        5,6
	*/
	int number_of_files = 7;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 3);
	int local_access_time = 0;
	int remote_access_time = 1;
	double impact_per_operation = 0.0;

	/*
	   Files 0,1,2 -> machine 0
	   Files 3,4 -> machine 1
	   Files 5,6 -> machine 2
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;
	allocation_initial_system->machines[2] = 0;
	allocation_initial_system->machines[3] = 1;
	allocation_initial_system->machines[4] = 1;
	allocation_initial_system->machines[5] = 2;
	allocation_initial_system->machines[6] = 2;

	/*
	   Files 2, 3, 5 and 6 were deleted by deduplication.
	*/	
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = 0;
	allocation_final_system->machines[2] = -1;
	allocation_final_system->machines[3] = -1;
	allocation_final_system->machines[4] = 1;
	allocation_final_system->machines[5] = -1;
	allocation_final_system->machines[6] = -1;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;
	file_popularity->popularity[2] = 10;
	file_popularity->popularity[3] = 10;
	file_popularity->popularity[4] = 10;
	file_popularity->popularity[5] = 10;
	file_popularity->popularity[6] = 10;

	/*
	   Similarity file 0
	*/	
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	file_similarity->similar_files[0*number_of_files + 3] = 1;
	file_similarity->similar_files[0*number_of_files + 5] = 1;

	/*
	   Similarity file 1
	*/
	file_similarity->similar_files[1*number_of_files + 1] = 1;	

	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[2*number_of_files + 2] = 1;
	file_similarity->similar_files[2*number_of_files + 4] = 1;	
	file_similarity->similar_files[2*number_of_files + 6] = 1;	

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[3*number_of_files + 0] = 1;
	file_similarity->similar_files[3*number_of_files + 3] = 1;
	file_similarity->similar_files[3*number_of_files + 5] = 1;

	/*
	   Similarity file 4
	*/
	file_similarity->similar_files[4*number_of_files + 2] = 1;
	file_similarity->similar_files[4*number_of_files + 4] = 1;	
	file_similarity->similar_files[4*number_of_files + 6] = 1;	

	/*
	   Similarity file 5
	*/
	file_similarity->similar_files[5*number_of_files + 0] = 1;
	file_similarity->similar_files[5*number_of_files + 3] = 1;
	file_similarity->similar_files[5*number_of_files + 5] = 1;

	/*
	   Similarity file 6
	*/
	file_similarity->similar_files[6*number_of_files + 2] = 1;
	file_similarity->similar_files[6*number_of_files + 4] = 1;
	file_similarity->similar_files[6*number_of_files + 6] = 1;

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					0);


	assert(abs2(impact_per_operation - 1/3.0) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					1);

	assert(abs2(impact_per_operation - 0.5) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					2);

	assert(abs2(impact_per_operation - 1) < 0.1);
	
	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

void time_access_impact_per_operation_on_machine_test_4(void)
{
	/*
	   There are three machines:
		machine    files
		   0       0,1,2
		   1        3,4
		   2        5,6
	*/
	int number_of_files = 7;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 3);
	int local_access_time = 100;
	int remote_access_time = 1000;
	double impact_per_operation = 0.0;

	/*
	   Files 0,1,2 -> machine 0
	   Files 3,4 -> machine 1
	   Files 5,6 -> machine 2
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;
	allocation_initial_system->machines[2] = 0;
	allocation_initial_system->machines[3] = 1;
	allocation_initial_system->machines[4] = 1;
	allocation_initial_system->machines[5] = 2;
	allocation_initial_system->machines[6] = 2;

	/*
	   Files 2, 3, 5 and 6 were deleted by deduplication.
	*/	
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = 0;
	allocation_final_system->machines[2] = -1;
	allocation_final_system->machines[3] = -1;
	allocation_final_system->machines[4] = 1;
	allocation_final_system->machines[5] = -1;
	allocation_final_system->machines[6] = -1;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;
	file_popularity->popularity[2] = 10;
	file_popularity->popularity[3] = 10;
	file_popularity->popularity[4] = 10;
	file_popularity->popularity[5] = 10;
	file_popularity->popularity[6] = 10;

	/*
	   Similarity file 0
	*/	
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	file_similarity->similar_files[0*number_of_files + 3] = 1;
	file_similarity->similar_files[0*number_of_files + 5] = 1;

	/*
	   Similarity file 1
	*/
	file_similarity->similar_files[1*number_of_files + 1] = 1;	

	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[2*number_of_files + 2] = 1;
	file_similarity->similar_files[2*number_of_files + 4] = 1;	
	file_similarity->similar_files[2*number_of_files + 6] = 1;	

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[3*number_of_files + 0] = 1;
	file_similarity->similar_files[3*number_of_files + 3] = 1;
	file_similarity->similar_files[3*number_of_files + 5] = 1;

	/*
	   Similarity file 4
	*/
	file_similarity->similar_files[4*number_of_files + 2] = 1;
	file_similarity->similar_files[4*number_of_files + 4] = 1;	
	file_similarity->similar_files[4*number_of_files + 6] = 1;	

	/*
	   Similarity file 5
	*/
	file_similarity->similar_files[5*number_of_files + 0] = 1;
	file_similarity->similar_files[5*number_of_files + 3] = 1;
	file_similarity->similar_files[5*number_of_files + 5] = 1;

	/*
	   Similarity file 6
	*/
	file_similarity->similar_files[6*number_of_files + 2] = 1;
	file_similarity->similar_files[6*number_of_files + 4] = 1;
	file_similarity->similar_files[6*number_of_files + 6] = 1;

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					0);


	assert(abs2(impact_per_operation - 300) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					1);

	assert(abs2(impact_per_operation - 450) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					2);

	assert(abs2(impact_per_operation - 900) < 0.1);
	
	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

void time_access_impact_per_operation_on_machine_test_5(void)
{
	/*
	   There are three machines:
		machine    files
		   0       0,1,2
		   1        3,4
		   2        5,6
	*/
	int number_of_files = 7;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 3);
	int local_access_time = 100;
	int remote_access_time = 1000;
	double impact_per_operation = 0.0;

	/*
	   Files 0,1,2 -> machine 0
	   Files 3,4 -> machine 1
	   Files 5,6 -> machine 2
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;
	allocation_initial_system->machines[2] = 0;
	allocation_initial_system->machines[3] = 1;
	allocation_initial_system->machines[4] = 1;
	allocation_initial_system->machines[5] = 2;
	allocation_initial_system->machines[6] = 2;

	/*
	   No file was deleted by deduplication
	*/	
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = 0;
	allocation_final_system->machines[2] = 0;
	allocation_final_system->machines[3] = 1;
	allocation_final_system->machines[4] = 1;
	allocation_final_system->machines[5] = 2;
	allocation_final_system->machines[6] = 2;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;
	file_popularity->popularity[2] = 10;
	file_popularity->popularity[3] = 10;
	file_popularity->popularity[4] = 10;
	file_popularity->popularity[5] = 10;
	file_popularity->popularity[6] = 10;

	/*
	   Similarity file 0
	*/	
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	
	/*
	   Similarity file 1
	*/
	file_similarity->similar_files[1*number_of_files + 1] = 1;
	
	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[2*number_of_files + 2] = 1;

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[3*number_of_files + 3] = 1;

	/*
	   Similarity file 4
	*/
	file_similarity->similar_files[4*number_of_files + 4] = 1;

	/*
	   Similarity file 5
	*/
	file_similarity->similar_files[5*number_of_files + 5] = 1;

	/*
	   Similarity file 6
	*/
	file_similarity->similar_files[6*number_of_files + 6] = 1;

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					0);

	assert(abs2(impact_per_operation - 0) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					1);

	assert(abs2(impact_per_operation - 0) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					2);

	assert(abs2(impact_per_operation - 0) < 0.1);
	
	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

void time_access_impact_per_operation_on_machine_test_6(void)
{
	/*
	   There are three machines:
		machine    files
		   0       0,1,2
		   1        3,4
		   2        5,6
	*/
	int number_of_files = 7;
	FILE_ALLOCATION *allocation_initial_system = construct_file_allocation(number_of_files);
	FILE_ALLOCATION *allocation_final_system = construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = construct_file_similarity(number_of_files);
	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files, 3);
	int local_access_time = 100;
	int remote_access_time = 1000;
	double impact_per_operation = 0.0;

	/*
	   Files 0,1,2 -> machine 0
	   Files 3,4 -> machine 1
	   Files 5,6 -> machine 2
	*/
	allocation_initial_system->machines[0] = 0;
	allocation_initial_system->machines[1] = 0;
	allocation_initial_system->machines[2] = 0;
	allocation_initial_system->machines[3] = 1;
	allocation_initial_system->machines[4] = 1;
	allocation_initial_system->machines[5] = 2;
	allocation_initial_system->machines[6] = 2;

	/*
	   All the files except file 0 were deleted by deduplication
	*/	
	allocation_final_system->machines[0] = 0;
	allocation_final_system->machines[1] = -1;
	allocation_final_system->machines[2] = -1;
	allocation_final_system->machines[3] = -1;
	allocation_final_system->machines[4] = -1;
	allocation_final_system->machines[5] = -1;
	allocation_final_system->machines[6] = -1;

	/*
	   Files have the same popularity.
	*/
	file_popularity->popularity[0] = 10;
	file_popularity->popularity[1] = 10;
	file_popularity->popularity[2] = 10;
	file_popularity->popularity[3] = 10;
	file_popularity->popularity[4] = 10;
	file_popularity->popularity[5] = 10;
	file_popularity->popularity[6] = 10;

	/*
	   Similarity file 0
	*/	
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	file_similarity->similar_files[0*number_of_files + 1] = 1;
	file_similarity->similar_files[0*number_of_files + 2] = 1;
	file_similarity->similar_files[0*number_of_files + 3] = 1;
	file_similarity->similar_files[0*number_of_files + 4] = 1;
	file_similarity->similar_files[0*number_of_files + 5] = 1;
	file_similarity->similar_files[0*number_of_files + 6] = 1;
	
	/*
	   Similarity file 1
	*/
	file_similarity->similar_files[1*number_of_files + 0] = 1;
	file_similarity->similar_files[1*number_of_files + 1] = 1;
	file_similarity->similar_files[1*number_of_files + 2] = 1;
	file_similarity->similar_files[1*number_of_files + 3] = 1;
	file_similarity->similar_files[1*number_of_files + 4] = 1;
	file_similarity->similar_files[1*number_of_files + 5] = 1;
	file_similarity->similar_files[1*number_of_files + 6] = 1;
	
	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[2*number_of_files + 0] = 1;
	file_similarity->similar_files[2*number_of_files + 1] = 1;
	file_similarity->similar_files[2*number_of_files + 2] = 1;
	file_similarity->similar_files[2*number_of_files + 3] = 1;
	file_similarity->similar_files[2*number_of_files + 4] = 1;
	file_similarity->similar_files[2*number_of_files + 5] = 1;
	file_similarity->similar_files[2*number_of_files + 6] = 1;

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[3*number_of_files + 0] = 1;
	file_similarity->similar_files[3*number_of_files + 1] = 1;
	file_similarity->similar_files[3*number_of_files + 2] = 1;
	file_similarity->similar_files[3*number_of_files + 3] = 1;
	file_similarity->similar_files[3*number_of_files + 4] = 1;
	file_similarity->similar_files[3*number_of_files + 5] = 1;
	file_similarity->similar_files[3*number_of_files + 6] = 1;

	/*
	   Similarity file 4
	*/
	file_similarity->similar_files[4*number_of_files + 0] = 1;
	file_similarity->similar_files[4*number_of_files + 1] = 1;
	file_similarity->similar_files[4*number_of_files + 2] = 1;
	file_similarity->similar_files[4*number_of_files + 3] = 1;
	file_similarity->similar_files[4*number_of_files + 4] = 1;
	file_similarity->similar_files[4*number_of_files + 5] = 1;
	file_similarity->similar_files[4*number_of_files + 6] = 1;

	/*
	   Similarity file 5
	*/
	file_similarity->similar_files[5*number_of_files + 0] = 1;
	file_similarity->similar_files[5*number_of_files + 1] = 1;
	file_similarity->similar_files[5*number_of_files + 2] = 1;
	file_similarity->similar_files[5*number_of_files + 3] = 1;
	file_similarity->similar_files[5*number_of_files + 4] = 1;
	file_similarity->similar_files[5*number_of_files + 5] = 1;
	file_similarity->similar_files[5*number_of_files + 6] = 1;

	/*
	   Similarity file 6
	*/
	file_similarity->similar_files[6*number_of_files + 0] = 1;
	file_similarity->similar_files[6*number_of_files + 1] = 1;
	file_similarity->similar_files[6*number_of_files + 2] = 1;
	file_similarity->similar_files[6*number_of_files + 3] = 1;
	file_similarity->similar_files[6*number_of_files + 4] = 1;
	file_similarity->similar_files[6*number_of_files + 5] = 1;
	file_similarity->similar_files[6*number_of_files + 6] = 1;

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					0);

	assert(abs2(impact_per_operation - 0) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					1);

	assert(abs2(impact_per_operation - 900) < 0.1);

	impact_per_operation = time_access_impact_per_operation_on_machine(
					allocation_initial_system, 
					allocation_final_system,
					file_similarity,
					file_popularity,
					remote_access_time,
					local_access_time,
					2);

	assert(abs2(impact_per_operation - 900) < 0.1);
	
	destruct_file_allocation(allocation_initial_system);
	destruct_file_allocation(allocation_final_system);
	destruct_file_popularity(file_popularity);
	destruct_file_similarity(file_similarity);
}

int main(void)
{

	time_access_impact_per_operation_test_1();
	puts("passed time_access_impact_per_operation_test_1");
	time_access_impact_per_operation_test_2();
	puts("passed time_access_impact_per_operation_test_2");	
	time_access_impact_per_operation_test_3();
	puts("passed time_access_impact_per_operation_test_3");	
	time_access_impact_per_operation_on_machine_test_1();
	puts("passed time_access_impact_per_operation_on_machine_test_1");
	time_access_impact_per_operation_on_machine_test_2();
	puts("passed time_access_impact_per_operation_on_machine_test_2");
	time_access_impact_per_operation_on_machine_test_3();
	puts("passed time_access_impact_per_operation_on_machine_test_3");
	time_access_impact_per_operation_on_machine_test_4();
	puts("passed time_access_impact_per_operation_on_machine_test_4");
	time_access_impact_per_operation_on_machine_test_5();
	puts("passed time_access_impact_per_operation_on_machine_test_5");
	time_access_impact_per_operation_on_machine_test_6();
	puts("passed time_access_impact_per_operation_on_machine_test_6");

	return 0;
}
