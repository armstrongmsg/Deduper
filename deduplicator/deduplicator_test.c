# include <stdio.h>
# include <assert.h>
# include "../file_allocation/file_allocation.h"
# include "../file_similarity/file_similarity.h"
# include "deduplicator.h"

void test_deduplicate_1()
{
	int number_of_files = 7;
	FILE_ALLOCATION *initial_allocation = 
				construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = 
				construct_file_similarity(number_of_files);	
	FILE_ALLOCATION *allocation_final_system = NULL;
	
	initial_allocation->machines[0] = 0;
	initial_allocation->machines[1] = 0;
	initial_allocation->machines[2] = 0;
	initial_allocation->machines[3] = 1;
	initial_allocation->machines[4] = 1;
	initial_allocation->machines[5] = 2;
	initial_allocation->machines[6] = 2;

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

	allocation_final_system = deduplicate(initial_allocation, 
				       file_similarity);

	/*
	   Files 1, 3, 4 and 5 were deleted by deduplication.
	*/	
	assert(allocation_final_system->machines[0] == 0);
	assert(allocation_final_system->machines[1] == -1);
	assert(allocation_final_system->machines[2] == 0);
	assert(allocation_final_system->machines[3] == -1);
	assert(allocation_final_system->machines[4] == -1);
	assert(allocation_final_system->machines[5] == -1);
	assert(allocation_final_system->machines[6] == 2);
	
	destruct_file_allocation(initial_allocation);
	destruct_file_allocation(allocation_final_system);
	destruct_file_similarity(file_similarity);
}

void test_deduplicate_2()
{
	int number_of_files = 4;
	FILE_ALLOCATION *initial_allocation = 
				construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = 
				construct_file_similarity(number_of_files);	
	FILE_ALLOCATION *allocation_final_system = NULL;

	initial_allocation->machines[0] = 0;
	initial_allocation->machines[1] = 1;
	initial_allocation->machines[2] = 2;
	initial_allocation->machines[3] = 3;

	/*
	   There is no similar files.
	*/

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

	allocation_final_system = deduplicate(initial_allocation, 
					file_similarity);

	/*
	   The system remains unchanged.
	*/	
	assert(allocation_final_system->machines[0] == 0);
	assert(allocation_final_system->machines[1] == 1);
	assert(allocation_final_system->machines[2] == 2);
	assert(allocation_final_system->machines[3] == 3);

	destruct_file_allocation(initial_allocation);
	destruct_file_allocation(allocation_final_system);
	destruct_file_similarity(file_similarity);
}

void test_deduplicate_3()
{
	int number_of_files = 6;
	FILE_ALLOCATION *initial_allocation = 
				construct_file_allocation(number_of_files);
	FILE_SIMILARITY *file_similarity = 
				construct_file_similarity(number_of_files);	
	FILE_ALLOCATION *allocation_final_system = NULL;
	
	initial_allocation->machines[0] = 0;
	initial_allocation->machines[1] = 1;
	initial_allocation->machines[2] = 1;
	initial_allocation->machines[3] = 1;
	initial_allocation->machines[4] = 1;
	initial_allocation->machines[5] = 1;

	/*
	   Similarity file 0
	*/
	file_similarity->similar_files[0*number_of_files + 0] = 1;
	file_similarity->similar_files[0*number_of_files + 1] = 1;	
	file_similarity->similar_files[0*number_of_files + 2] = 1;
	file_similarity->similar_files[0*number_of_files + 3] = 1;
	file_similarity->similar_files[0*number_of_files + 4] = 1;

	/*
	   Similarity file 1
	*/
	file_similarity->similar_files[1*number_of_files + 0] = 1;
	file_similarity->similar_files[1*number_of_files + 1] = 1;	
	file_similarity->similar_files[1*number_of_files + 2] = 1;
	file_similarity->similar_files[1*number_of_files + 3] = 1;
	file_similarity->similar_files[1*number_of_files + 4] = 1;

	/*
	   Similarity file 2
	*/
	file_similarity->similar_files[2*number_of_files + 0] = 1;
	file_similarity->similar_files[2*number_of_files + 1] = 1;	
	file_similarity->similar_files[2*number_of_files + 2] = 1;
	file_similarity->similar_files[2*number_of_files + 3] = 1;
	file_similarity->similar_files[2*number_of_files + 4] = 1;

	/*
	   Similarity file 3
	*/
	file_similarity->similar_files[3*number_of_files + 0] = 1;
	file_similarity->similar_files[3*number_of_files + 1] = 1;	
	file_similarity->similar_files[3*number_of_files + 2] = 1;
	file_similarity->similar_files[3*number_of_files + 3] = 1;
	file_similarity->similar_files[3*number_of_files + 4] = 1;


	/*
	   Similarity file 4
	*/
	file_similarity->similar_files[4*number_of_files + 0] = 1;
	file_similarity->similar_files[4*number_of_files + 1] = 1;	
	file_similarity->similar_files[4*number_of_files + 2] = 1;
	file_similarity->similar_files[4*number_of_files + 3] = 1;
	file_similarity->similar_files[4*number_of_files + 4] = 1;

	/*
	   Similarity file 5
	*/
	file_similarity->similar_files[5*number_of_files + 5] = 1;

	allocation_final_system = deduplicate(initial_allocation, 
				       file_similarity);

	/*
	   Files 1, 2, 3 and 4 were deleted by deduplication.
	*/	
	assert(allocation_final_system->machines[0] == 0);
	assert(allocation_final_system->machines[1] == -1);
	assert(allocation_final_system->machines[2] == -1);
	assert(allocation_final_system->machines[3] == -1);
	assert(allocation_final_system->machines[4] == -1);
	assert(allocation_final_system->machines[5] == 1);
	
	destruct_file_allocation(initial_allocation);
	destruct_file_allocation(allocation_final_system);
	destruct_file_similarity(file_similarity);
}

int main(void)
{
	test_deduplicate_1();
	puts("passed test_deduplicate_1");
	test_deduplicate_2();
	puts("passed test_deduplicate_2");
	test_deduplicate_3();
	puts("passed test_deduplicate_3");

	return 0;
}
