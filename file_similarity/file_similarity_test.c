# include <stdio.h>
# include <assert.h>
# include <stdlib.h>
# include "file_similarity.h"

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
	
	return 0;
}
