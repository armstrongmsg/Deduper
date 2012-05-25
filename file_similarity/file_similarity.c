/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains the implementations for the functions declared on
   "file_similarity.h". These functions deal with the FILE_SIMILARITY struct.
*/
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include "file_similarity.h"

FILE_SIMILARITY *construct_file_similarity(int number_of_files)
{
	FILE_SIMILARITY *new_file_similarity = NULL;	
	int *similar_files = NULL;

	assert(number_of_files > 0);
	
	new_file_similarity = 
			 (FILE_SIMILARITY *) malloc(sizeof(FILE_SIMILARITY));

	assert(new_file_similarity);
	
	similar_files = (int *) malloc(sizeof(int)*number_of_files*
						number_of_files);
	memset(similar_files, '\0', sizeof(int)*number_of_files*
						number_of_files);
	
	assert(similar_files);

	new_file_similarity->similar_files = similar_files;
	new_file_similarity->number_of_files = number_of_files;

	return new_file_similarity;
}

void destruct_file_similarity(FILE_SIMILARITY *file_similarity)
{
	assert(file_similarity);
	
	if (file_similarity->similar_files)
	{
		free(file_similarity->similar_files);
	}

	free(file_similarity);	
}

int read_number_from_file(FILE *file)
{
	int number = 0;
	
	fscanf(file, "%d", &number);
	fgetc(file);

	return number;
}

FILE_SIMILARITY *load_file_similarity(FILE *file, int number_of_files)
{
	int table_i = 0;
	int table_j = 0;
	FILE_SIMILARITY *file_similarity = 
			construct_file_similarity(number_of_files);

	assert(file);

	for (; table_i < number_of_files; table_i++)
	{
		for ( ; table_j < number_of_files; table_j++)
		{			
			/*	
			file_similarity->similar_files[table_i][table_j] = 
					read_number_from_file(file);
			*/
		}

		fgetc(file);	
	}

	return file_similarity;		
}

int *get_similar_files(int file_index, FILE_SIMILARITY *similarity)
{
	int *similar_files = NULL;
	int index_similar_files = 0;
	int file = 0;
	int number_of_files = similarity->number_of_files;	

	assert(file_index >= 0);
	assert(similarity);	

	/*
  	   number_of_files + 1 because we need to store the final -1.
	*/
	similar_files = (int *) malloc(sizeof(int)*(number_of_files + 1));
	
	assert(similar_files);

	for ( ; file < number_of_files; file++)
	{ 
		if (similarity->similar_files[file_index*number_of_files +
				file])
		{
			similar_files[index_similar_files] = file;
			index_similar_files++;
		}
	}		

	similar_files[index_similar_files] = -1;	
	
	return similar_files;
}

void set_similar_files(FILE_SIMILARITY *similarity,
                        int *similar_files,
                        int number_similar_files)
{
	int i = 0,j = 0;
	int file = 0;
	int total_number_of_files = 0;
	assert(similarity);

	total_number_of_files = similarity->number_of_files;

	for ( ; i < number_similar_files; i++)
	{
		file = similar_files[i];
			
		for (j = 0; j < number_similar_files; j++)
		{
			int similar = similar_files[j];
			similarity->similar_files[file*total_number_of_files + similar] = 1;
		}
	}	


}

