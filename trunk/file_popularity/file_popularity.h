/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains structs used to store file popularities and
   functions to deal with these structs.
   A file popularity is an integer and is stored in an array of integers.
   The i-th file's popularity is stored in the i-th position of the array.
*/
# ifndef FILE_POPULARITY_H
# define FILE_POPULARITY_H

/*
   This struct is used to keep a reference to the array mentioned above.
*/
typedef struct
{
	int *popularity;	
	int number_of_files;

} FILE_POPULARITY;

/*
   Constructs a FILE_POPULARITY struct to store the popularity of 
   the given number of files. As it should use malloc, the returned
   FILE_POPULARITY must be used on a free call.
*/
FILE_POPULARITY *construct_file_popularity(int number_of_files);

/*
   Destructs a FILE_POPULARITY struct using free.

*/
void destruct_file_popularity(FILE_POPULARITY *file_popularity);

/*
   Creates a FILE_POPULARITY struct that holds the data stored on the
   given file. The struct is created using construct_file_popularity and
   the given number of files.
*/
//FILE_POPULARITY *load_file_popularity(FILE *file, int number_of_files);

/*
   Returns the sum of the popularity of all files on the system.
*/
long system_popularity(FILE_POPULARITY *file_popularity);

# endif
