# include <stdio.h>
# include <string.h>
# include <assert.h>
# include "file_allocation.h"

void create_file_with_given_name_and_content(char *name, char *content)
{
	FILE *file = fopen(name, "w");
	assert(file);

	rewind(file);
	assert(fwrite(content, 1, strlen(content), file) == strlen(content));
	
	fclose(file);
}

void test_1(void)
{
	FILE_ALLOCATION *file_allocation = NULL;
	FILE *allocation_file = NULL;
	int i = 0;

	create_file_with_given_name_and_content("alloc_test.txt", 
		"0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n");

	allocation_file = fopen("alloc_test.txt", "r");

	file_allocation = load_file_allocation(allocation_file, 10);
	
	for (; i < 10; i++)
	{
		assert(file_allocation->machines[i] == i);	
	}
}

void test_co_allocated_1()
{
	FILE_ALLOCATION *file_allocation = construct_file_allocation(10);

	/*
	   Files 1, 3 and 8 are co-allocated.
	*/
	file_allocation->machines[0] = 1;	
	file_allocation->machines[3] = 1;
	file_allocation->machines[8] = 1;
	
	assert(co_allocated(file_allocation, 0, 3) == 1);
	assert(co_allocated(file_allocation, 3, 0) == 1);

	assert(co_allocated(file_allocation, 0, 8) == 1);
	assert(co_allocated(file_allocation, 8, 0) == 1);
	
	assert(co_allocated(file_allocation, 3, 8) == 1);
	assert(co_allocated(file_allocation, 8, 3) == 1);

	destruct_file_allocation(file_allocation);
}

void test_co_allocated_2()
{
	FILE_ALLOCATION *file_allocation = construct_file_allocation(12);

	/*
	   Files 1 and 3 are co-allocated.
	*/
	file_allocation->machines[0] = 1;	
	file_allocation->machines[3] = 1;
	
	/*
  	   Files 8 and 11 are co-allocated with each other, 
	   but not with 1 and 3.
	*/
	file_allocation->machines[8] = 2;
	file_allocation->machines[11] = 2;
	
	assert(co_allocated(file_allocation, 0, 3) == 1);
	assert(co_allocated(file_allocation, 3, 0) == 1);
	
	assert(co_allocated(file_allocation, 8, 11) == 1);
	assert(co_allocated(file_allocation, 11, 8) == 1);	

	assert(!co_allocated(file_allocation, 0, 8));
	assert(!co_allocated(file_allocation, 8, 0));

	assert(!co_allocated(file_allocation, 0, 11));
	assert(!co_allocated(file_allocation, 11, 0));
	
	assert(!co_allocated(file_allocation, 3, 8));
	assert(!co_allocated(file_allocation, 8, 3));

	assert(!co_allocated(file_allocation, 3, 11));
	assert(!co_allocated(file_allocation, 11, 3));

	assert(!co_allocated(file_allocation, 0, 1));
	assert(!co_allocated(file_allocation, 1, 0));	

	destruct_file_allocation(file_allocation);
}

void test_exist()
{
	FILE_ALLOCATION *file_allocation = construct_file_allocation(10);

	assert(file_allocation);

	file_allocation->machines[0] = 1;
	file_allocation->machines[1] = -1;	

	assert(exist(file_allocation, 0) == 1);
	assert(!exist(file_allocation, 1));

	destruct_file_allocation(file_allocation);
}

int main(void)
{
	test_1();
	puts("passed test_1");
	test_co_allocated_1();
	puts("passed test_co_allocated_1");
	test_co_allocated_2();
	puts("passed test_co_allocated_2");
	test_exist();
	puts("passed test_exist");

	return 0;
}
