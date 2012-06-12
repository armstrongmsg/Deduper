/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains prototypes of functions used to simulate 
   deduplication. These functions receive some structures as 
   FILE_ALLOCATION and FILE_SIMILARITY and return deduplicated 
   versions of them.
*/

# ifndef DEDUPLICATOR_H
# define DEDUPLICATOR_H 

# include "../file_allocation/file_allocation.h"
# include "../file_similarity/file_similarity.h"

/*
   Generates a new FILE_ALLOCATION where:
	For all file i and all file j, 
	if file_similarity->similar_files[i] == file_similarity->similar_files[j] then i == j. 
*/
FILE_ALLOCATION *deduplicate(FILE_ALLOCATION *file_allocation, 
			     FILE_SIMILARITY *file_similarity);


/*
   Generates a new FILE_ALLOCATION where:
   	For all file i and all file j, 
	if file_similarity->similar_files[i] == file_similarity->similar_files[j] then i == j. 

   The choise of which file will not be deleted is made pseudo-randomically.
*/
FILE_ALLOCATION *deduplicate_randomically(FILE_ALLOCATION *file_allocation, 
					FILE_SIMILARITY *file_similarity);
# endif
