/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains structs used to store file allocations. A file
   allocation is the number of the machine where it's stored. The 
   allocations are stored in an array of integers. The i-th file's 
   allocation is stored in the i-th position of the array.
   
   This struct can be used for both represent allocation on non-deduplicated
   file systems and to represent deduplicated file systems. Suppose there is
   a file system 1, whose FILE_ALLOCATION is FILE_A_1. After deduplication
   process, some file will be deleted and a new FILE_ALLOCATION FILE_A_2 is 
   generated. This FILE_ALLOCATION will store data for all the files which 
   originally were on FILE_A_1. But on these index FILE_A_2 will store -1, 
   to let the structure client know that the file no longer exist on the system.
*/

# ifndef FILE_ALLOCATION_H
# define FILE_ALLOCATION_H

/*
   This struct is used to keep a reference to the array mentioned above.
*/
typedef struct
{
	int *machines;
	int number_of_files;

} FILE_ALLOCATION;

/*
   Constructs a FILE_ALLOCATION struct to store the alocation of 
   the given number of files. As it should use malloc, the returned
   FILE_ALLOCATION must be used on a free call.
*/
FILE_ALLOCATION *construct_file_allocation(int number_of_files);

/*
   Destructs a FILE_ALLOCATION struct using free.
*/
void destruct_file_allocation(FILE_ALLOCATION *file_allocation);

/*
   Creates a FILE_ALLOCATION struct that holds the data stored on the
   given file. The struct is created using construct_file_allocation and
   the given number of files.
*/
//FILE_ALLOCATION *load_file_allocation(FILE *file, int number_of_files);

/*
   Returns 1 if file_index_1 and file_index_2 are stored in the same
   machine. Returns 0 otherwise.
*/
int co_allocated(FILE_ALLOCATION *file_allocation, int file_index_1, 
					int file_index_2);

/*
   Returns 1 if file_index_1 exist on the FILE_ALLOCATION.
   Returns 0 otherwise.
*/
int exist(FILE_ALLOCATION *file_allocation, int file_index);


# endif
