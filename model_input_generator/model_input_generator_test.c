# include <stdio.h>
# include <assert.h>
# include "model_input_generator.h"
# include "../file_allocation/file_allocation.h"
# include "../file_popularity/file_popularity.h"
# include "../file_similarity/file_similarity.h"

void test_1_generate_file_allocation(void)
{
	FILE_ALLOCATION *f_alloc = generate_file_allocation(20, 3);
	int i = 0;
	
	for ( ; i < 7; i++)
	{
		assert(!f_alloc->machines[i]);	
	}

	for ( ; i < 14; i++)
	{
		assert(f_alloc->machines[i] == 1);
	}

	for ( ; i < 20; i++)
	{
		assert(f_alloc->machines[i] == 2);
	}
}

void test_2_generate_file_allocation(void)
{
	FILE_ALLOCATION *f_alloc = generate_file_allocation(21, 3);
	int i = 0;

	for ( ; i < 7; i++)
	{
		assert(!f_alloc->machines[i]);	
	}

	for ( ; i < 14; i++)
	{
		assert(f_alloc->machines[i] == 1);
	}

	for ( ; i < 21; i++)
	{
		assert(f_alloc->machines[i] == 2);
	}
}

void test_3_generate_file_allocation(void)
{
	FILE_ALLOCATION *f_alloc = generate_file_allocation(21, 21);
	int i = 0;

	for ( ; i < 21; i++)
	{
		assert(f_alloc->machines[i] == i);
	}
}

void test_1_generate_file_popularity_with_equal_value(void)
{
	FILE_POPULARITY *file_popularity = generate_file_popularity_with_equal_value(10, 2, 5);
	int i = 0;
		
	assert(file_popularity);

	for ( ; i < 10*2; i++)
	{
		assert(file_popularity->popularity[i] == 5);
	}
		
	destruct_file_popularity(file_popularity);		
}

void test_1_generate_file_similarity(void)
{
	FILE_ALLOCATION *f_alloc_base = generate_file_allocation(10, 5);
	FILE_SIMILARITY *f_similarity = 
			generate_file_similarity(f_alloc_base, 0.4);
	
	int file = 0;

	// checks the similar files
	for ( ; file < 8; file += 2)
	{
		assert(f_similarity->similar_files[file*10] == 1);
		assert(f_similarity->similar_files[file*10 + 2] == 1);
		assert(f_similarity->similar_files[file*10 + 4] == 1);
		assert(f_similarity->similar_files[file*10 + 6] == 1);	

		f_similarity->similar_files[file*10] = 0;
		f_similarity->similar_files[file*10 + 2] = 0;
		f_similarity->similar_files[file*10 + 4] = 0;
		f_similarity->similar_files[file*10 + 6] = 0;	
	}

	// ensure that there's no others similar files
	for (file = 0; file < 10*10; file++)
	{
		assert(!f_similarity->similar_files[file]);
	}	
}

void test_2_generate_file_similarity(void)
{
	FILE_ALLOCATION *f_alloc_base = generate_file_allocation(10, 5);
	FILE_SIMILARITY *f_similarity = 
			generate_file_similarity(f_alloc_base, 0.6);
	
	int file = 0;

	// check the similar files
	// the first group of similar files = {0, 2, 4, 6}
	for ( ; file < 8; file += 2)
	{
		assert(f_similarity->similar_files[file*10] == 1);
		assert(f_similarity->similar_files[file*10 + 2] == 1);
		assert(f_similarity->similar_files[file*10 + 4] == 1);
		assert(f_similarity->similar_files[file*10 + 6] == 1);	

		f_similarity->similar_files[file*10] = 0;
		f_similarity->similar_files[file*10 + 2] = 0;
		f_similarity->similar_files[file*10 + 4] = 0;
		f_similarity->similar_files[file*10 + 6] = 0;	
	}
	

	// the second group of similar files = {1, 8}
	file = 1;
	assert(f_similarity->similar_files[file*10 + 1] == 1);
	assert(f_similarity->similar_files[file*10 + 8] == 1);

	f_similarity->similar_files[file*10 + 1] = 0;
	f_similarity->similar_files[file*10 + 8] = 0;

	file = 8;
	assert(f_similarity->similar_files[file*10 + 1] == 1);
	assert(f_similarity->similar_files[file*10 + 8] == 1);

	f_similarity->similar_files[file*10 + 1] = 1;
	f_similarity->similar_files[file*10 + 8] = 1;
	


	// ensure that there's no others similar files
	for (file = 0; file < 10*10; file++)
	{
		assert(!f_similarity->similar_files[file]);
	}	
}

void test_3_generate_file_similarity(void)
{
	FILE_ALLOCATION *f_alloc_base = generate_file_allocation(10, 5);
	FILE_SIMILARITY *f_similarity = 
			generate_file_similarity(f_alloc_base, 0.5);
	
	int file = 0;

	// check the similar files
	// similar files = {0, 2, 4, 6, 8}
	for ( ; file < 10; file += 2)
	{
		assert(f_similarity->similar_files[file*10] == 1);
		assert(f_similarity->similar_files[file*10 + 2] == 1);
		assert(f_similarity->similar_files[file*10 + 4] == 1);
		assert(f_similarity->similar_files[file*10 + 6] == 1);	
		assert(f_similarity->similar_files[file*10 + 8] == 1);

		f_similarity->similar_files[file*10] = 0;
		f_similarity->similar_files[file*10 + 2] = 0;
		f_similarity->similar_files[file*10 + 4] = 0;
		f_similarity->similar_files[file*10 + 6] = 0;	
		f_similarity->similar_files[file*10 + 8] = 0;
	}
	
	// ensure that there's no others similar files
	for (file = 0; file < 10*10; file++)
	{
		assert(!f_similarity->similar_files[file]);
	}	
}

void test_4_generate_file_similarity()
{
	FILE_ALLOCATION *f_alloc_base = generate_file_allocation(15, 5);
	FILE_SIMILARITY *f_similarity = 
			generate_file_similarity(f_alloc_base, 2.0/3);
	
	int file = 0;

	/* check the similar files
	   first group of similar files = {0, 3, 6, 9, 12} */
	for ( ; file <= 12; file += 3)
	{
		assert(f_similarity->similar_files[file*15 + 0] == 1);
		assert(f_similarity->similar_files[file*15 + 3] == 1);
		assert(f_similarity->similar_files[file*15 + 6] == 1);
		assert(f_similarity->similar_files[file*15 + 9] == 1);	
		assert(f_similarity->similar_files[file*15 + 12] == 1);

		f_similarity->similar_files[file*15 + 0] = 0;
		f_similarity->similar_files[file*15 + 3] = 0;
		f_similarity->similar_files[file*15 + 6] = 0;
		f_similarity->similar_files[file*15 + 9] = 0;	
		f_similarity->similar_files[file*15 + 12] = 0;
	}
	
	file = 0;
	/*
	   Second group of similar files={1, 4, 7, 10, 13}
	*/
	for ( ; file <= 12; file += 3)
	{
		file++;
		assert(f_similarity->similar_files[file*15 + 1] == 1);
		assert(f_similarity->similar_files[file*15 + 4] == 1);
		assert(f_similarity->similar_files[file*15 + 7] == 1);
		assert(f_similarity->similar_files[file*15 + 10] == 1);	
		assert(f_similarity->similar_files[file*15 + 13] == 1);

		f_similarity->similar_files[file*15 + 1] = 0;
		f_similarity->similar_files[file*15 + 4] = 0;
		f_similarity->similar_files[file*15 + 7] = 0;
		f_similarity->similar_files[file*15 + 10] = 0;	
		f_similarity->similar_files[file*15 + 13] = 0;
		file--;
	}

	/*
           ensure that there's no other similar files
	*/
	for (file = 0; file < 15*15; file++)
	{
		assert(!f_similarity->similar_files[file]);
	}
}

void test_5_generate_file_similarity()
{
	FILE_ALLOCATION *file_allocation = generate_file_allocation(10, 2);
	FILE_SIMILARITY *file_similarity = generate_file_similarity(
						file_allocation, 0.4);	

	/* 
	   check the similar files
	   First group of similar files = {0, 5} 
	*/
	assert(file_similarity->similar_files[0*10 + 0] == 1);
	assert(file_similarity->similar_files[0*10 + 5] == 1);
	assert(file_similarity->similar_files[5*10 + 0] == 1);
	assert(file_similarity->similar_files[5*10 + 5] == 1);

	file_similarity->similar_files[0*10 + 0] = 0;
	file_similarity->similar_files[0*10 + 5] = 0;
	file_similarity->similar_files[5*10 + 0] = 0;
	file_similarity->similar_files[5*10 + 5] = 0;

	
	/*
	   Second group of similar files = {1, 6}
	*/
	assert(file_similarity->similar_files[1*10 + 1] == 1);
	assert(file_similarity->similar_files[1*10 + 6] == 1);
	assert(file_similarity->similar_files[6*10 + 1] == 1);
	assert(file_similarity->similar_files[6*10 + 6] == 1);

	file_similarity->similar_files[1*10 + 1] = 0;
	file_similarity->similar_files[1*10 + 6] = 0;
	file_similarity->similar_files[6*10 + 1] = 0;
	file_similarity->similar_files[6*10 + 6] = 0;

	int file = 0;

	/*
           ensure that there's no other similar files
	*/
	for (file = 0; file < 10*10; file++)
	{
		assert(!file_similarity->similar_files[file]);
	}
	
	destruct_file_similarity(file_similarity);	
}

int main(void)
{
	test_1_generate_file_allocation();	
	puts("Passed on test 1 generate file allocation");
	test_2_generate_file_allocation();
	puts("Passed on test 2 generate file allocation");
	test_3_generate_file_allocation();	
	puts("Passed on test 3 generate file allocation");
	test_1_generate_file_popularity_with_equal_value();
	puts("Passed on test 1 generate file popularity with equal value");
	test_3_generate_file_similarity();
	puts("Passed on test 3 generate file similarity");
	test_4_generate_file_similarity();
	puts("Passed on test 4 generate file similarity");
	test_5_generate_file_similarity();
	puts("Passed on test 5 generate file similarity");

	return 0;
}
