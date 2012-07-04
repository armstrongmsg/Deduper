/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains prototypes for functions used to simulate
   inputs for the model.
   As to collect real data may be difficult and sometimes we want
   to verify some specific situations, is good to generate inputs.
*/

# ifndef MODEL_INPUT_GENERATOR_H
# define MODEL_INPUT_GENERATOR_H

# include "../file_allocation/file_allocation.h"
# include "../file_popularity/file_popularity.h"
# include "../file_similarity/file_similarity.h"

/*
   Construct a new FILE_ALLOCATION with the given number of files and 
   the given number of machines.   
   The adopted policy tries to equalize the allocation of files on the 
   machines. So, the returned FILE_ALLOCATION, if possible, will store the 
   same number of files on all the machines. 
   For example:
	For 10 files and 5 machines
        The returned allocation:
	       file  machine	
	      	0	0	
              	1	0 
		2	1
		3	1
		4	2
		5	2
		6	3
		7	3
		8	4
		9	4

	For 9 files and 5 machines
	 The returned allocation:
	       file  machine	
	      	0	0	
              	1	0 
		2	1
		3	1
		4	2
		5	2
		6	3
		7	3
		8	4

    The struct is created with malloc, so this must be destructed
    with destruct_file_allocation.
*/
FILE_ALLOCATION *generate_file_allocation(int number_of_files, int number_of_machines);

/*
    Constructs a FILE_POPULARITY with the given number of files and the given number of machines. 
    The popularities are constructed to simulate a situation which all file is only accessed locally, that is,
    the popularity of the file in the other machines is 0.
    The returned struct must be destructed with destruct_file_popularity.
*/
FILE_POPULARITY *generate_file_popularity_with_equal_value(int number_of_files, int number_of_machines, int popularity, 
								FILE_ALLOCATION *file_allocation);

/*
    Constructs a FILE_SIMILARITY, based on the given FILE_ALLOCATION 
    and the given duplication level.
    This function will try to generate the struct in a way that there 
    are not two files stored on the same machines and similars.
    There is no guarantee that it will get it.

    Example 1:
	
	Given the FILE_ALLOCATION generated in the call 
	generate_file_allocation(10, 5) and a popularity of 0.4, 
        the similar files are 0, 2, 4 and 6.

    Example 2:
   
	Given the FILE_ALLOCATION genereted in the call
	generate_file_allocation(10, 5) and a popularity of 0.6,
	there will be two groups of similar files:
		- group 1: 0, 2, 4, 6
		- group 2: 1, 8
	It will try to store a duplicate on each machine. As it won't get
 	it (more files that machines), it will create a new group of 
	duplicated files.	

    Example 3:
	
	Given the FILE_ALLOCATION genereted in the call
	generate_file_allocation(10, 5) and a popularity of 0.5,
	the similar files are 0, 2, 4, 6, 8.
			
*/
FILE_SIMILARITY *generate_file_similarity(FILE_ALLOCATION *file_allocation, double duplication_level);

# endif
