/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains prototypes of functions that will execute the model.
*/

/*
# ifndef DEDUPLICATION_MODEL_H
# define DEDUPLICATION_MODEL_H
*/
# include "../file_allocation/file_allocation.h"
# include "../file_popularity/file_popularity.h"
# include "../file_similarity/file_similarity.h"

/*
  It returns the impact on the time of access of the files per opertion
  using the given FILE_ALLOCATION, FILE_SIMILARITY, FILE_POPULARITY and
  access times.
*/
double time_access_impact_per_operation(
				FILE_ALLOCATION *allocation_initial_system, 
				FILE_ALLOCATION *allocation_final_system,
				FILE_SIMILARITY *file_similarity,
				FILE_POPULARITY *file_popularity, 
				double remote_access_time, 
				double local_access_time);


/*
# endif 
*/
