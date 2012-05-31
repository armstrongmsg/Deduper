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

# ifndef MODEL_RUNNER_H
# define MODEL_RUNNER_H

/*
   This function will run the model using a generated input:
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

/*
   This function will run the model using a generated input:
   1- the storage will be equalized. So all the machines will
      store approximately the same number of files. 
   2- the file will have linear popularity. So the i-th file stored
      in a machine will have popularity equal to i*popularity_factor
*/
double run_with_linear_popularity_equalized_storage(
				double duplication_level,
				int popularity_factor,
				int number_of_files,
				int number_of_machines,
				double remote_access_time,
				double local_access_time);

# endif
