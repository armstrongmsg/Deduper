# include <stdio.h>
# include <assert.h>
# include "model_input_generator.h"
# include "../file_allocation/file_allocation.h"
# include "../file_popularity/file_popularity.h"
# include "../file_similarity/file_similarity.h"

int dummy_popularity = 0;
int popularity_mul_factor = 2;

int dummy_popularity_function_constant(int file)
{
	return dummy_popularity;
}

int dummy_popularity_function_linear(int file)
{
	return file*popularity_mul_factor;
}

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

void test_generate_file_popularity_with_equal_value_1(void)
{
	FILE_ALLOCATION *file_allocation = construct_file_allocation(10);
	FILE_POPULARITY *file_popularity = NULL;

	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 0;
	file_allocation->machines[3] = 0;
	file_allocation->machines[4] = 0;
	file_allocation->machines[5] = 1;
	file_allocation->machines[6] = 1;
	file_allocation->machines[7] = 1;
	file_allocation->machines[8] = 1;
	file_allocation->machines[9] = 1;

	file_popularity = generate_file_popularity_with_equal_value(10, 2, 5, file_allocation);
	int i = 0;
		
	assert(file_popularity);

	/*
	   The first 5 files are stored in the machine 0
	*/
	for ( ; i < 10; i += 2)
	{
		assert(file_popularity->popularity[i] == 5);
		assert(file_popularity->popularity[i + 1] == 0);
	}	

	/*
	   The last 5 files are stored in the machine 1
	*/
	for (i = 10 ; i < 20; i += 2)
	{
		assert(file_popularity->popularity[i] == 0);
		assert(file_popularity->popularity[i + 1] == 5);
	}
		
	destruct_file_popularity(file_popularity);
	destruct_file_allocation(file_allocation);		
}

void test_generate_file_popularity_with_equal_value_2(void)
{
	FILE_ALLOCATION *file_allocation = construct_file_allocation(10);
	FILE_POPULARITY *file_popularity = NULL;

	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 0;
	file_allocation->machines[3] = 0;
	file_allocation->machines[4] = 0;
	file_allocation->machines[5] = 0;
	file_allocation->machines[6] = 0;
	file_allocation->machines[7] = 0;
	file_allocation->machines[8] = 0;
	file_allocation->machines[9] = 0;

	file_popularity = generate_file_popularity_with_equal_value(10, 1, 5, file_allocation);
	int i = 0;
		
	assert(file_popularity);

	/*
	   All the files are stored in machine 0
	*/
	for ( ; i < 10; i++)
	{
		assert(file_popularity->popularity[i] == 5);
	}	
	
	destruct_file_popularity(file_popularity);
	destruct_file_allocation(file_allocation);		
}

void test_generate_file_popularity_with_equal_value_3(void)
{
	FILE_ALLOCATION *file_allocation = construct_file_allocation(10);
	FILE_POPULARITY *file_popularity = NULL;

	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 1;
	file_allocation->machines[2] = 2;
	file_allocation->machines[3] = 3;
	file_allocation->machines[4] = 4;
	file_allocation->machines[5] = 0;
	file_allocation->machines[6] = 1;
	file_allocation->machines[7] = 2;
	file_allocation->machines[8] = 3;
	file_allocation->machines[9] = 4;

	file_popularity = generate_file_popularity_with_equal_value(10, 5, 5, file_allocation);
	int i = 0;
		
	assert(file_popularity);

	for ( ; i < 10; i++)
	{
		int machine = 0;
		for ( ; machine < 5; machine++)
		{
			if (file_allocation->machines[i] == machine)
			{
				assert(file_popularity->popularity[i*5 + machine] == 5);
			}
			else
			{
				assert(file_popularity->popularity[i*5 + machine] == 0);
			}
		}
	}
	
	destruct_file_popularity(file_popularity);
	destruct_file_allocation(file_allocation);		
}

void test_generate_file_popularity_with_equal_value_4(void)
{
	FILE_ALLOCATION *file_allocation = construct_file_allocation(10);
	FILE_POPULARITY *file_popularity = NULL;

	file_allocation->machines[0] = 1;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 2;
	file_allocation->machines[3] = 4;
	file_allocation->machines[4] = 0;
	file_allocation->machines[5] = 2;
	file_allocation->machines[6] = 1;
	file_allocation->machines[7] = 3;
	file_allocation->machines[8] = 3;
	file_allocation->machines[9] = 0;

	file_popularity = generate_file_popularity_with_equal_value(10, 5, 5, file_allocation);
	int i = 0;
		
	assert(file_popularity);

	for ( ; i < 10; i++)
	{
		int machine = 0;
		for ( ; machine < 5; machine++)
		{
			if (file_allocation->machines[i] == machine)
			{
				assert(file_popularity->popularity[i*5 + machine] == 5);
			}
			else
			{
				assert(file_popularity->popularity[i*5 + machine] == 0);
			}
		}
	}
	
	destruct_file_popularity(file_popularity);
	destruct_file_allocation(file_allocation);		
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

void test_1_generate_file_popularity_using_function(void)
{
	int number_of_files = 2;
	int number_of_machines = 1;
	FILE_ALLOCATION *file_allocation = construct_file_allocation(number_of_files);
	FILE_POPULARITY *file_popularity = NULL;
	double shared = 0;
	int constant_popularity = 10;
	int popularity_factor = 2;
	
	assert(file_allocation);
	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;

	dummy_popularity = constant_popularity;
				
	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_constant);	
	

	assert(file_popularity);
	assert(file_popularity->number_of_files == 2);
	assert(file_popularity->number_of_machines == 1);
	assert(file_popularity->popularity[0] == 10);
	assert(file_popularity->popularity[1] == 10);

	destruct_file_popularity(file_popularity);

	popularity_mul_factor = popularity_factor;		

	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_linear);	
	
	assert(file_popularity);
	assert(file_popularity->number_of_files == number_of_files);
	assert(file_popularity->number_of_machines == number_of_machines);
	assert(file_popularity->popularity[0] == 0);
	assert(file_popularity->popularity[1] == 2);

	destruct_file_allocation(file_allocation);
	destruct_file_popularity(file_popularity);
}

void test_2_generate_file_popularity_using_function(void)
{
	int number_of_files = 4;
	int number_of_machines = 2;
	FILE_ALLOCATION *file_allocation = construct_file_allocation(number_of_files);
	FILE_POPULARITY *file_popularity = NULL;
	double shared = 0;
	int constant_popularity = 10;
	int popularity_factor = 2;
	
	assert(file_allocation);
	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 0;
	file_allocation->machines[2] = 1;
	file_allocation->machines[3] = 1;

	dummy_popularity = constant_popularity;
				
	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_constant);	
	

	assert(file_popularity);
	assert(file_popularity->number_of_files == number_of_files);
	assert(file_popularity->number_of_machines == number_of_machines);
	
	assert(file_popularity->popularity[0*number_of_machines + 0] == 10);
	assert(file_popularity->popularity[0*number_of_machines + 1] == 0);
	assert(file_popularity->popularity[1*number_of_machines + 0] == 10);
	assert(file_popularity->popularity[1*number_of_machines + 1] == 0);
	assert(file_popularity->popularity[2*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[2*number_of_machines + 1] == 10);
	assert(file_popularity->popularity[3*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[3*number_of_machines + 1] == 10);

	destruct_file_popularity(file_popularity);

	popularity_mul_factor = popularity_factor;		

	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_linear);	
	
	assert(file_popularity);
	assert(file_popularity->number_of_files == number_of_files);
	assert(file_popularity->number_of_machines == number_of_machines);
	
	assert(file_popularity->popularity[0*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[0*number_of_machines + 1] == 0);
	assert(file_popularity->popularity[1*number_of_machines + 0] == 2);
	assert(file_popularity->popularity[1*number_of_machines + 1] == 0);
	assert(file_popularity->popularity[2*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[2*number_of_machines + 1] == 4);
	assert(file_popularity->popularity[3*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[3*number_of_machines + 1] == 6);

	destruct_file_allocation(file_allocation);
	destruct_file_popularity(file_popularity);
}

void test_3_generate_file_popularity_using_function(void)
{
	int number_of_files = 2;
	int number_of_machines = 2;
	FILE_ALLOCATION *file_allocation = construct_file_allocation(number_of_files);
	FILE_POPULARITY *file_popularity = NULL;
	double shared = 0.1;
	int constant_popularity = 10;
	int popularity_factor = 2;
	
	assert(file_allocation);
	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 1;

	dummy_popularity = constant_popularity;
				
	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_constant);	
	

	assert(file_popularity);
	assert(file_popularity->number_of_files == number_of_files);
	assert(file_popularity->number_of_machines == number_of_machines);
	
	assert(file_popularity->popularity[0*number_of_machines + 0] == 9);
	assert(file_popularity->popularity[0*number_of_machines + 1] == 1);
	assert(file_popularity->popularity[1*number_of_machines + 0] == 1);
	assert(file_popularity->popularity[1*number_of_machines + 1] == 9);

	destruct_file_popularity(file_popularity);

	popularity_mul_factor = popularity_factor;		

	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_linear);	
	
	assert(file_popularity);
	assert(file_popularity->number_of_files == number_of_files);
	assert(file_popularity->number_of_machines == number_of_machines);
	
	assert(file_popularity->popularity[0*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[0*number_of_machines + 1] == 0);

	/*
	  As it was not possible to share the popularity (2/10.0 is not an integer), 
	  all the popularity is local
	*/
	assert(file_popularity->popularity[1*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[1*number_of_machines + 1] == 2);

	destruct_file_popularity(file_popularity);
	
	popularity_mul_factor = 15;		

	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_linear);	
	
	assert(file_popularity);
	assert(file_popularity->number_of_files == number_of_files);
	assert(file_popularity->number_of_machines == number_of_machines);
	
	assert(file_popularity->popularity[0*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[0*number_of_machines + 1] == 0);

	/*
	  As it was not possible to share the popularity (2/10.0 is not an integer), 
	  all the popularity is local
	*/
	assert(file_popularity->popularity[1*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[1*number_of_machines + 1] == 15);

	destruct_file_allocation(file_allocation);
	destruct_file_popularity(file_popularity);
}

void test_4_generate_file_popularity_using_function(void)
{
	int number_of_files = 3;
	int number_of_machines = 3;
	FILE_ALLOCATION *file_allocation = construct_file_allocation(number_of_files);
	FILE_POPULARITY *file_popularity = NULL;
	double shared = 0.1;
	int constant_popularity = 20;
	int popularity_factor = 30;
	
	assert(file_allocation);
	file_allocation->machines[0] = 0;
	file_allocation->machines[1] = 1;
	file_allocation->machines[2] = 2;


	dummy_popularity = constant_popularity;
				
	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_constant);	
	

	assert(file_popularity);
	assert(file_popularity->number_of_files == number_of_files);
	assert(file_popularity->number_of_machines == number_of_machines);
	assert(file_popularity->popularity[0*number_of_machines + 0] == 18);
	assert(file_popularity->popularity[0*number_of_machines + 1] == 1);
	assert(file_popularity->popularity[0*number_of_machines + 2] == 1);
	assert(file_popularity->popularity[1*number_of_machines + 0] == 1);
	assert(file_popularity->popularity[1*number_of_machines + 1] == 18);
	assert(file_popularity->popularity[1*number_of_machines + 2] == 1);
	assert(file_popularity->popularity[2*number_of_machines + 0] == 1);
	assert(file_popularity->popularity[2*number_of_machines + 1] == 1);
	assert(file_popularity->popularity[2*number_of_machines + 2] == 18);

	destruct_file_popularity(file_popularity);

	popularity_mul_factor = popularity_factor;		

	file_popularity = generate_file_popularity_using_function(number_of_files, 
								number_of_machines,
								shared,
								file_allocation,	
								dummy_popularity_function_linear);	
	
	assert(file_popularity);
	assert(file_popularity->number_of_files == number_of_files);
	assert(file_popularity->number_of_machines == number_of_machines);
	
	assert(file_popularity->popularity[0*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[0*number_of_machines + 1] == 0);
	assert(file_popularity->popularity[0*number_of_machines + 2] == 0);
	assert(file_popularity->popularity[1*number_of_machines + 0] == 0);
	assert(file_popularity->popularity[1*number_of_machines + 1] == 30);
	assert(file_popularity->popularity[1*number_of_machines + 2] == 0);
	assert(file_popularity->popularity[2*number_of_machines + 0] == 3);
	assert(file_popularity->popularity[2*number_of_machines + 1] == 3);
	assert(file_popularity->popularity[2*number_of_machines + 2] == 54);

	destruct_file_allocation(file_allocation);
	destruct_file_popularity(file_popularity);
}


int main(void)
{
	test_1_generate_file_allocation();	
	puts("Passed on test 1 generate file allocation");
	test_2_generate_file_allocation();
	puts("Passed on test 2 generate file allocation");
	test_3_generate_file_allocation();	
	puts("Passed on test 3 generate file allocation");
	test_generate_file_popularity_with_equal_value_1();
	puts("Passed on test generate file popularity with equal value 1");
	test_generate_file_popularity_with_equal_value_2();
	puts("Passed on test generate file popularity with equal value 2");
	test_generate_file_popularity_with_equal_value_3();
	puts("Passed on test generate file popularity with equal value 3");
	test_generate_file_popularity_with_equal_value_4();
	puts("Passed on test generate file popularity with equal value 4");
	test_3_generate_file_similarity();
	puts("Passed on test 3 generate file similarity");
	test_4_generate_file_similarity();
	puts("Passed on test 4 generate file similarity");
	test_5_generate_file_similarity();
	puts("Passed on test 5 generate file similarity");
	test_1_generate_file_popularity_using_function();
	puts("Passed on test_1_generate_file_popularity_using_function");
	test_2_generate_file_popularity_using_function();
	puts("Passed on test_2_generate_file_popularity_using_function");
	test_3_generate_file_popularity_using_function();
	puts("Passed on test_3_generate_file_popularity_using_function");
	test_4_generate_file_popularity_using_function();
	puts("Passed on test_4_generate_file_popularity_using_function");

	return 0;
}
