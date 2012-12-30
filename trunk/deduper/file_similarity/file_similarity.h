/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains structs used to store matrixes of similarity 
   between files. The current implementation of these matrixes uses
   an array. So I represent a bidimensional struture with an 
   unidimensional structure. It can represent only square matrixes.
   If the represented matrix has r rows, the element of the i-th 
   row and the j-th column is the (r*i + j)-th element of the array.
  
   If the (r*i + j)-th element of the array is 1, then the i-th file
   is similar to the j-th file. Otherwise, they are not similar.
*/
# ifndef FILE_SIMILARITY_H
# define FILE_SIMILARITY_H

# include "../file_allocation/file_allocation.h"
/*
   This struct is used to keep a reference to the array mentioned above.
*/
typedef struct
{
	int *similar_files;
	int number_of_files;

} FILE_SIMILARITY;

/*
   Constructs a FILE_SIMILARITY struct to store the similarity matrix of 
   the given number of files. As it should use malloc, the returned
   FILE_SIMILARITY must be used on a free call.
*/
FILE_SIMILARITY *construct_file_similarity(int number_of_files);

/*
   Destructs a FILE_SIMILARITY struct using free.

*/
void destruct_file_similarity(FILE_SIMILARITY *file_similarity);
//FILE_SIMILARITY *load_file_similarity(FILE *file, int number_of_files);

/*
   Returns the indexes of the files that are similar to the given file
   considering the given FILE_SIMILARITY.
   The memory to store the indexes is allocated with malloc, so it's a must
   to call free on the returned pointer.
   The end of the list of indexes is indicated by a -1.
*/
int *get_similar_files(int file_index, FILE_SIMILARITY *similarity);

/*
   Modifies the given FILE_SIMILARITY in a way that the given similar 
   files are similar on the structure.
 
   Example:
	
	similarity is a 3X3 matrix.
	All the elements in similarity are zero.
	Given similar_files={0,1}.

	So, after call set_similar_files similarity will
	look like this:

  	   0  1  2
	0  1  1  0
	1  1  1  0
	2  0  0  0
*/
void set_similar_files(FILE_SIMILARITY *similarity, 
			int *similar_files,
			int number_of_similar_files);

/*
   Returns 1 if there is at least one file coalocated with
   and not equal to the file indexed by the given index and 
   similar to it after deduplication, and returns 0 otherwise.
   If the given file doesn't exist in the given allocation, 
   the function returns 0
*/
int there_is_similar_file_on_machine_after_deduplication(FILE_SIMILARITY *similarity, 
				     FILE_ALLOCATION *initial_file_allocation,
			  	     FILE_ALLOCATION *final_file_allocation, 
				     int file);

/*
   Returns 1 if there is at least one file similar to the
   given file in the given similarity
*/
int has_duplicatas(FILE_SIMILARITY *similarity, 
			int file);

/*
   Returns the number of duplicatas of the given file
   on the given similarity
*/
int number_of_duplicatas(FILE_SIMILARITY *similarity,
			int file);
# endif
