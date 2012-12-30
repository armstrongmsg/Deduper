# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include "file_similarity.h"
# include "../file_allocation/file_allocation.h"

void construct_file_similarity_initializes_space_with_zeros(void)
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(10);
	int i = 0;
	
	for ( ; i < 10*10; i++)
	{
		assert(!file_similarity->similar_files[i]);
	}
	
	destruct_file_similarity(file_similarity);
}

void get_similar_files_test_1()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(10);
	int *similar_files = NULL;	

	/*
	   First file is similar to itself
	   Fifth file is similar to itself
	*/
	file_similarity->similar_files[0] = 1;
	file_similarity->similar_files[4*10 + 4] = 1;

	/*
	    First file and fifth files are similar.
	*/
	file_similarity->similar_files[4] = 1;
	file_similarity->similar_files[4*10] = 1;
	
	similar_files = get_similar_files(0, file_similarity);

	assert(!similar_files[0]);
	assert(similar_files[1] == 4);
	assert(similar_files[2] == -1);
	
	free(similar_files);
	
	similar_files = get_similar_files(4, file_similarity);

	assert(!similar_files[0]);
	assert(similar_files[1] == 4);
	assert(similar_files[2] == -1);

	free(similar_files);
	destruct_file_similarity(file_similarity);
}

void get_similar_files_test_2()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(10);
	int *similar_files = NULL;	

	/*
	   First file is similar to itself
	   Fifth file is similar to itself	
	*/
	file_similarity->similar_files[0] = 1;
	file_similarity->similar_files[4*10 + 4] = 1;

	similar_files = get_similar_files(0, file_similarity);

	assert(!similar_files[0]);
	assert(similar_files[1] == -1);	

	free(similar_files);

	similar_files = get_similar_files(4, file_similarity);

	assert(similar_files[0] == 4);
	assert(similar_files[1] == -1);

	free(similar_files);
	destruct_file_similarity(file_similarity);
}

void get_similar_files_test_3()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(10);
	int *similar_files = NULL;	

	similar_files = get_similar_files(0, file_similarity);

	assert(similar_files[0] == -1);

	free(similar_files);	

	similar_files = get_similar_files(4, file_similarity);

	assert(similar_files[0] == -1);

	free(similar_files);
	destruct_file_similarity(file_similarity);
}

void set_similar_files_test_1(void)
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(3);
	int similar_files[] = {0, 1};
	
	set_similar_files(file_similarity, 
			  similar_files,
			  2);
	
	assert(file_similarity->similar_files[0*3 + 1] == 1);
	assert(file_similarity->similar_files[1*3 + 0] == 1);
	assert(file_similarity->similar_files[0*3 + 0] == 1);
	assert(file_similarity->similar_files[1*3 + 1] == 1);

	destruct_file_similarity(file_similarity);
}

void set_similar_files_test_2(void)
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(5);
	int similar_files[] = {1, 3, 4};
	int i = 0;
		
	set_similar_files(file_similarity, similar_files, 3);
	
	for ( ; i < 3; i++)
	{
		int file = similar_files[i];
		assert(file_similarity->similar_files[file*5 + 1] == 1);
		assert(file_similarity->similar_files[file*5 + 3] == 1);
		assert(file_similarity->similar_files[file*5 + 4] == 1);
	}

	destruct_file_similarity(file_similarity);
}

void there_is_similar_file_on_machine_after_deduplication_test_1()
{
	FILE_ALLOCATION *file_allocation =
			construct_file_allocation(5);
	FILE_ALLOCATION *file_allocation_after_deduplication = 
			construct_file_allocation(5);
	FILE_SIMILARITY *file_similarity = 
			construct_file_similarity(5);

	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 0;
	file_allocation->machines[3] = 1;
	file_allocation->machines[4] = 1;
		
	/*
     	   Files 1 and 3 were deleted by deduplication
	*/
	file_allocation_after_deduplication->machines[0] = 0;
	file_allocation_after_deduplication->machines[1] = -1;
	file_allocation_after_deduplication->machines[2] = 0;
	file_allocation_after_deduplication->machines[3] = -1;
	file_allocation_after_deduplication->machines[4] = 1;


	file_similarity->similar_files[5*0 + 0] = 1;
	file_similarity->similar_files[5*0 + 1] = 1;
	file_similarity->similar_files[5*0 + 3] = 1;

	file_similarity->similar_files[5*1 + 0] = 1;
	file_similarity->similar_files[5*1 + 1] = 1;
	file_similarity->similar_files[5*1 + 3] = 1;

	file_similarity->similar_files[5*2 + 2] = 1;

	file_similarity->similar_files[5*3 + 0] = 1;
	file_similarity->similar_files[5*3 + 1] = 1;
	file_similarity->similar_files[5*3 + 3] = 1;

	file_similarity->similar_files[5*4 + 4] = 1;

	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 0));
	assert(there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 1) == 1);
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 2));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 3));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 4));

 	destruct_file_allocation(file_allocation);
	destruct_file_allocation(file_allocation_after_deduplication);
	destruct_file_similarity(file_similarity);
}

void there_is_similar_file_on_machine_after_deduplication_test_2()
{
	FILE_ALLOCATION *file_allocation =
			construct_file_allocation(5);
	FILE_ALLOCATION *file_allocation_after_deduplication = 
			construct_file_allocation(5);
	FILE_SIMILARITY *file_similarity = 
			construct_file_similarity(5);

	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 0;
	file_allocation->machines[3] = 1;
	file_allocation->machines[4] = 1;
		
	/*
	   No file was deleted by deduplication
	*/
	file_allocation_after_deduplication->machines[0] = 0;
	file_allocation_after_deduplication->machines[1] = 0;
	file_allocation_after_deduplication->machines[2] = 0;
	file_allocation_after_deduplication->machines[3] = 1;
	file_allocation_after_deduplication->machines[4] = 1;

	file_similarity->similar_files[5*0 + 0] = 1;
	
	file_similarity->similar_files[5*1 + 1] = 1;

	file_similarity->similar_files[5*2 + 2] = 1;

	file_similarity->similar_files[5*3 + 3] = 1;

	file_similarity->similar_files[5*4 + 4] = 1;

	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 0));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 1));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 2));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 3));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 4));

 	destruct_file_allocation(file_allocation);
	destruct_file_allocation(file_allocation_after_deduplication);
	destruct_file_similarity(file_similarity);
}

void there_is_similar_file_on_machine_after_deduplication_test_3(void)
{
	FILE_ALLOCATION *file_allocation =
			construct_file_allocation(5);
	FILE_ALLOCATION *file_allocation_after_deduplication = 
			construct_file_allocation(5);
	FILE_SIMILARITY *file_similarity = 
			construct_file_similarity(5);

	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 0;
	file_allocation->machines[3] = 1;
	file_allocation->machines[4] = 1;

	file_allocation_after_deduplication->machines[0] = 0;
	file_allocation_after_deduplication->machines[1] = -1;
	file_allocation_after_deduplication->machines[2] = -1;
	file_allocation_after_deduplication->machines[3] = -1;
	file_allocation_after_deduplication->machines[4] = -1;
		
	file_similarity->similar_files[5*0 + 0] = 1;
	file_similarity->similar_files[5*0 + 1] = 1;
	file_similarity->similar_files[5*0 + 2] = 1;
	file_similarity->similar_files[5*0 + 3] = 1;
	file_similarity->similar_files[5*0 + 4] = 1;

	file_similarity->similar_files[5*1 + 0] = 1;
	file_similarity->similar_files[5*1 + 1] = 1;
	file_similarity->similar_files[5*1 + 2] = 1;
	file_similarity->similar_files[5*1 + 3] = 1;
	file_similarity->similar_files[5*1 + 4] = 1;

	file_similarity->similar_files[5*2 + 0] = 1;
	file_similarity->similar_files[5*2 + 1] = 1;
	file_similarity->similar_files[5*2 + 2] = 1;
	file_similarity->similar_files[5*2 + 3] = 1;
	file_similarity->similar_files[5*2 + 4] = 1;

	file_similarity->similar_files[5*3 + 0] = 1;
	file_similarity->similar_files[5*3 + 1] = 1;
	file_similarity->similar_files[5*3 + 2] = 1;
	file_similarity->similar_files[5*3 + 3] = 1;
	file_similarity->similar_files[5*3 + 4] = 1;

	file_similarity->similar_files[5*4 + 0] = 1;
	file_similarity->similar_files[5*4 + 1] = 1;
	file_similarity->similar_files[5*4 + 2] = 1;
	file_similarity->similar_files[5*4 + 3] = 1;
	file_similarity->similar_files[5*4 + 4] = 1;

	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 0));
	assert(there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 1) == 1);
	assert(there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 2) == 1);
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 3));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 4));

 	destruct_file_allocation(file_allocation);
	destruct_file_allocation(file_allocation_after_deduplication);
	destruct_file_similarity(file_similarity);
}

void there_is_similar_file_on_machine_after_deduplication_test_4(void)
{
	FILE_ALLOCATION *file_allocation =
			construct_file_allocation(5);
	FILE_ALLOCATION *file_allocation_after_deduplication = 
			construct_file_allocation(5);
	FILE_SIMILARITY *file_similarity = 
			construct_file_similarity(5);

	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 0;
	file_allocation->machines[3] = 1;
	file_allocation->machines[4] = 1;

	file_allocation_after_deduplication->machines[0] = 0;
	file_allocation_after_deduplication->machines[1] = -1;
	file_allocation_after_deduplication->machines[2] = -1;
	file_allocation_after_deduplication->machines[3] = -1;
	file_allocation_after_deduplication->machines[4] = -1;
		
	file_similarity->similar_files[5*0 + 0] = 1;
	file_similarity->similar_files[5*0 + 1] = 1;
	file_similarity->similar_files[5*0 + 2] = 1;
	file_similarity->similar_files[5*0 + 3] = 1;
	file_similarity->similar_files[5*0 + 4] = 1;

	file_similarity->similar_files[5*1 + 0] = 1;
	file_similarity->similar_files[5*1 + 1] = 1;
	file_similarity->similar_files[5*1 + 2] = 1;
	file_similarity->similar_files[5*1 + 3] = 1;
	file_similarity->similar_files[5*1 + 4] = 1;

	file_similarity->similar_files[5*2 + 0] = 1;
	file_similarity->similar_files[5*2 + 1] = 1;
	file_similarity->similar_files[5*2 + 2] = 1;
	file_similarity->similar_files[5*2 + 3] = 1;
	file_similarity->similar_files[5*2 + 4] = 1;

	file_similarity->similar_files[5*3 + 0] = 1;
	file_similarity->similar_files[5*3 + 1] = 1;
	file_similarity->similar_files[5*3 + 2] = 1;
	file_similarity->similar_files[5*3 + 3] = 1;
	file_similarity->similar_files[5*3 + 4] = 1;

	file_similarity->similar_files[5*4 + 0] = 1;
	file_similarity->similar_files[5*4 + 1] = 1;
	file_similarity->similar_files[5*4 + 2] = 1;
	file_similarity->similar_files[5*4 + 3] = 1;
	file_similarity->similar_files[5*4 + 4] = 1;

	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 0));
	assert(there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 1) == 1);
	assert(there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 2) == 1);
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 3));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 4));

 	destruct_file_allocation(file_allocation);
	destruct_file_allocation(file_allocation_after_deduplication);
	destruct_file_similarity(file_similarity);
}

void there_is_similar_file_on_machine_after_deduplication_test_5(void)
{
	FILE_ALLOCATION *file_allocation =
			construct_file_allocation(7);
	FILE_ALLOCATION *file_allocation_after_deduplication = 
			construct_file_allocation(7);
	FILE_SIMILARITY *file_similarity = 
			construct_file_similarity(7);

	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 0;
	file_allocation->machines[3] = 1;
	file_allocation->machines[4] = 1;
	file_allocation->machines[5] = 2;
	file_allocation->machines[6] = 2;

	/*
          The files 2, 3, 5 and 6 were deleted by deduplication
	*/
	file_allocation_after_deduplication->machines[0] = 0;
	file_allocation_after_deduplication->machines[1] = 0;
	file_allocation_after_deduplication->machines[2] = -1;
	file_allocation_after_deduplication->machines[3] = -1;
	file_allocation_after_deduplication->machines[4] = 1;
	file_allocation_after_deduplication->machines[5] = -1;
	file_allocation_after_deduplication->machines[6] = -1;
	
	file_similarity->similar_files[5*0 + 0] = 1;
	file_similarity->similar_files[5*0 + 3] = 1;
	file_similarity->similar_files[5*0 + 5] = 1;

	file_similarity->similar_files[5*1 + 1] = 1;

	file_similarity->similar_files[5*2 + 2] = 1;
	file_similarity->similar_files[5*2 + 4] = 1;
	file_similarity->similar_files[5*2 + 6] = 1;

	file_similarity->similar_files[5*3 + 0] = 1;
	file_similarity->similar_files[5*3 + 3] = 1;
	file_similarity->similar_files[5*3 + 5] = 1;

	file_similarity->similar_files[5*4 + 2] = 1;
	file_similarity->similar_files[5*4 + 4] = 1;
	file_similarity->similar_files[5*4 + 6] = 1;

	file_similarity->similar_files[5*5 + 0] = 1;
	file_similarity->similar_files[5*5 + 3] = 1;
	file_similarity->similar_files[5*5 + 5] = 1;

	file_similarity->similar_files[5*6 + 2] = 1;
	file_similarity->similar_files[5*6 + 4] = 1;
	file_similarity->similar_files[5*6 + 6] = 1;

	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 0));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 1));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 2));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 3));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 4));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 5));
	assert(!there_is_similar_file_on_machine_after_deduplication(file_similarity, file_allocation, file_allocation_after_deduplication, 6));

 	destruct_file_allocation(file_allocation);
	destruct_file_allocation(file_allocation_after_deduplication);
	destruct_file_similarity(file_similarity);	
}

void number_of_duplicatas_test_1()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(5);

	assert(file_similarity);

	/*
	   equal files: 0, 1, 3
	*/
	file_similarity->similar_files[5*0 + 0] = 1;
	file_similarity->similar_files[5*0 + 1] = 1;
	file_similarity->similar_files[5*0 + 3] = 1;

	file_similarity->similar_files[5*1 + 0] = 1;
	file_similarity->similar_files[5*1 + 1] = 1;
	file_similarity->similar_files[5*1 + 3] = 1;

	file_similarity->similar_files[5*3 + 0] = 1;
	file_similarity->similar_files[5*3 + 1] = 1;
	file_similarity->similar_files[5*3 + 3] = 1;

	assert(number_of_duplicatas(file_similarity, 
					0) == 2);
	assert(number_of_duplicatas(file_similarity, 
					1) == 2);
	assert(number_of_duplicatas(file_similarity, 
					2) == 0);
	assert(number_of_duplicatas(file_similarity, 
					3) == 2);
	assert(number_of_duplicatas(file_similarity, 
					4) == 0);
	
	destruct_file_similarity(file_similarity);	
}

void number_of_duplicatas_test_2()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(5);

	assert(file_similarity);

	assert(number_of_duplicatas(file_similarity, 
					0) == 0);
	assert(number_of_duplicatas(file_similarity, 
					1) == 0);
	assert(number_of_duplicatas(file_similarity, 
					2) == 0);
	assert(number_of_duplicatas(file_similarity, 
					3) == 0);
	assert(number_of_duplicatas(file_similarity, 
					4) == 0);

	destruct_file_similarity(file_similarity);	
}

void number_of_duplicatas_test_3()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(5);

	assert(file_similarity);

	/*
	   all files are similar
	*/
	file_similarity->similar_files[5*0 + 0] = 1;
	file_similarity->similar_files[5*0 + 1] = 1;
	file_similarity->similar_files[5*0 + 2] = 1;
	file_similarity->similar_files[5*0 + 3] = 1;
	file_similarity->similar_files[5*0 + 4] = 1;

	file_similarity->similar_files[5*1 + 0] = 1;
	file_similarity->similar_files[5*1 + 1] = 1;
	file_similarity->similar_files[5*1 + 2] = 1;
	file_similarity->similar_files[5*1 + 3] = 1;
	file_similarity->similar_files[5*1 + 4] = 1;
	
	file_similarity->similar_files[5*2 + 0] = 1;
	file_similarity->similar_files[5*2 + 1] = 1;
	file_similarity->similar_files[5*2 + 2] = 1;
	file_similarity->similar_files[5*2 + 3] = 1;
	file_similarity->similar_files[5*2 + 4] = 1;
	
	file_similarity->similar_files[5*3 + 0] = 1;
	file_similarity->similar_files[5*3 + 1] = 1;
	file_similarity->similar_files[5*3 + 2] = 1;
	file_similarity->similar_files[5*3 + 3] = 1;
	file_similarity->similar_files[5*3 + 4] = 1;
	
	file_similarity->similar_files[5*4 + 0] = 1;
	file_similarity->similar_files[5*4 + 1] = 1;
	file_similarity->similar_files[5*4 + 2] = 1;
	file_similarity->similar_files[5*4 + 3] = 1;
	file_similarity->similar_files[5*4 + 4] = 1;
	
	assert(number_of_duplicatas(file_similarity, 
					0) == 4);
	assert(number_of_duplicatas(file_similarity, 
					1) == 4);
	assert(number_of_duplicatas(file_similarity, 
					2) == 4);
	assert(number_of_duplicatas(file_similarity, 
					3) == 4);
	assert(number_of_duplicatas(file_similarity, 
					4) == 4);

	destruct_file_similarity(file_similarity);	
}

void has_duplicatas_test_1()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(5);

	assert(file_similarity);

	/*
	   equal files: 0, 1, 3
	*/
	file_similarity->similar_files[5*0 + 0] = 1;
	file_similarity->similar_files[5*0 + 1] = 1;
	file_similarity->similar_files[5*0 + 3] = 1;

	file_similarity->similar_files[5*1 + 0] = 1;
	file_similarity->similar_files[5*1 + 1] = 1;
	file_similarity->similar_files[5*1 + 3] = 1;

	file_similarity->similar_files[5*3 + 0] = 1;
	file_similarity->similar_files[5*3 + 1] = 1;
	file_similarity->similar_files[5*3 + 3] = 1;

	assert(has_duplicatas(file_similarity, 
					0));
	assert(has_duplicatas(file_similarity, 
					1));
	assert(!has_duplicatas(file_similarity, 
					2));
	assert(has_duplicatas(file_similarity, 
					3));
	assert(!has_duplicatas(file_similarity, 
					4));
	
	destruct_file_similarity(file_similarity);	
}

void has_duplicatas_test_2()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(5);

	assert(file_similarity);

	assert(!has_duplicatas(file_similarity, 
					0));
	assert(!has_duplicatas(file_similarity, 
					1));
	assert(!has_duplicatas(file_similarity, 
					2));
	assert(!has_duplicatas(file_similarity, 
					3));
	assert(!has_duplicatas(file_similarity, 
					4));

	destruct_file_similarity(file_similarity);	
}

void has_duplicatas_test_3()
{
	FILE_SIMILARITY *file_similarity = construct_file_similarity(5);

	assert(file_similarity);

	/*
	   all files are similar
	*/
	file_similarity->similar_files[5*0 + 0] = 1;
	file_similarity->similar_files[5*0 + 1] = 1;
	file_similarity->similar_files[5*0 + 2] = 1;
	file_similarity->similar_files[5*0 + 3] = 1;
	file_similarity->similar_files[5*0 + 4] = 1;

	file_similarity->similar_files[5*1 + 0] = 1;
	file_similarity->similar_files[5*1 + 1] = 1;
	file_similarity->similar_files[5*1 + 2] = 1;
	file_similarity->similar_files[5*1 + 3] = 1;
	file_similarity->similar_files[5*1 + 4] = 1;
	
	file_similarity->similar_files[5*2 + 0] = 1;
	file_similarity->similar_files[5*2 + 1] = 1;
	file_similarity->similar_files[5*2 + 2] = 1;
	file_similarity->similar_files[5*2 + 3] = 1;
	file_similarity->similar_files[5*2 + 4] = 1;
	
	file_similarity->similar_files[5*3 + 0] = 1;
	file_similarity->similar_files[5*3 + 1] = 1;
	file_similarity->similar_files[5*3 + 2] = 1;
	file_similarity->similar_files[5*3 + 3] = 1;
	file_similarity->similar_files[5*3 + 4] = 1;
	
	file_similarity->similar_files[5*4 + 0] = 1;
	file_similarity->similar_files[5*4 + 1] = 1;
	file_similarity->similar_files[5*4 + 2] = 1;
	file_similarity->similar_files[5*4 + 3] = 1;
	file_similarity->similar_files[5*4 + 4] = 1;
	
	assert(has_duplicatas(file_similarity, 
					0));
	assert(has_duplicatas(file_similarity, 
					1));
	assert(has_duplicatas(file_similarity, 
					2));
	assert(has_duplicatas(file_similarity, 
					3));
	assert(has_duplicatas(file_similarity, 
					4));

	destruct_file_similarity(file_similarity);	
}

int main(void)
{
	construct_file_similarity_initializes_space_with_zeros();
	puts("passed on construct_file_similarity_initializes_space_with_zeros");
	get_similar_files_test_1();
	puts("passed on get_similar_files_test_1");
	get_similar_files_test_2();
	puts("passed on get_similar_files_test_2");
	get_similar_files_test_3();
	puts("passed on get_similar_files_test_3");
	set_similar_files_test_1();
	puts("passed on set_similar_files_test_1");
	set_similar_files_test_2();
	puts("passed on set_similar_files_test_2");
	there_is_similar_file_on_machine_after_deduplication_test_1();
	puts("passed on there_is_similar_file_on_machine_after_deduplication_test_1");
	there_is_similar_file_on_machine_after_deduplication_test_2();
	puts("passed on there_is_similar_file_on_machine_after_deduplication_test_2");
	there_is_similar_file_on_machine_after_deduplication_test_3();
	puts("passed on there_is_similar_file_on_machine_after_deduplication_test_3");	
	there_is_similar_file_on_machine_after_deduplication_test_4();
	puts("passed on there_is_similar_file_on_machine_after_deduplication_test_4");
	number_of_duplicatas_test_1();
	puts("passed on number_of_duplicatas_test_1");
	number_of_duplicatas_test_2();
	puts("passed on number_of_duplicatas_test_2");
	number_of_duplicatas_test_3();
	puts("passed on number_of_duplicatas_test_3");
	has_duplicatas_test_1();
	puts("passed on has_duplicatas_test_1");
	has_duplicatas_test_2();
	puts("passed on has_duplicatas_test_2");
	has_duplicatas_test_3();
	puts("passed on has_duplicatas_test_3");

	return 0;
}
