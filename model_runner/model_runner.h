/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains prototypes of functions that run the
   model with determined configurations.
*/

# ifndef DEDUPLICATION_MODEL_H
# define DEDUPLICATION_MODEL_H

/*
   This function will run the model using a generated inputs:
   1- the storage will be equalized. So all the machines will
      store approximately the same number of files.
   2- all the files will have the same popularity.
*/
double run_with_same_popularity_equalized_storage(
				double duplication_level,
				int popularity,
				int number_of_files,
				int number_of_machines,
				double remote_access_time,
				double local_access_time);

# endif
