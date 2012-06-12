/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains the implementations for the functions
   declared on "file_popularity.h". These functions deal with
   the FILE_POPULARITY struct.
*/
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <string.h>
# include "file_popularity.h"

FILE_POPULARITY *construct_file_popularity(int number_of_files)
{
	assert(number_of_files > 0);
	
	FILE_POPULARITY *new_file_popularity = 
		(FILE_POPULARITY *) malloc(sizeof(FILE_POPULARITY));

	assert(new_file_popularity);
	
	int *popularity = (int *) malloc(sizeof(int)*number_of_files);
	memset(popularity, '\0', sizeof(int)*number_of_files);
	
	assert(popularity);

	new_file_popularity->popularity = popularity;
	new_file_popularity->number_of_files = number_of_files;

	return new_file_popularity;
}

void destruct_file_popularity(FILE_POPULARITY *file_popularity)
{
	assert(file_popularity);
	
	if (file_popularity->popularity)
	{
		free(file_popularity->popularity);
	}

	free(file_popularity);	
}

/*
FILE_POPULARITY *load_file_popularity(FILE *file, int number_of_files)
{
	assert(file);

	FILE_POPULARITY *file_popularity = construct_file_popularity(number_of_files);
	assert(file_popularity);
	int read_popularity = 0;
	int popularity = 0;
	int reading_result = 0;

	for (; read_popularity < number_of_files; read_popularity++)
	{
		reading_result = fscanf(file, "%d", &popularity);
		assert(reading_result == 1);
		file_popularity->popularity[read_popularity] = popularity;
	}
	
	return file_popularity;	
}*/

long system_popularity(FILE_POPULARITY *file_popularity)
{
	long system_popularity = 0;
	int i = 0;

	assert(file_popularity);

	for ( ; i < file_popularity->number_of_files; i++)
	{
		system_popularity += file_popularity->popularity[i];
	}

	return system_popularity;
}

