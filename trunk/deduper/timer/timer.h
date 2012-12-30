/*
   Federal University of Campina Grande
   Distributed Systems Laboratory

   Author: Armstrong Mardilson da Silva Goes
   Contact: armstrongmsg@lsd.ufcg.edu.br
*/

/*
   This file contains prototypes of functions
   that deals with times during the model running
*/

#ifndef TIMER_H
#define TIMER_H

# include <time.h>

# define CLOCKS_PER_MILISEC ((CLOCKS_PER_SEC)/(1000))

typedef struct
{
	long time_start_running;
	long time_finish_running;
	long time_after_generate_allocation;
	long time_after_generate_popularity;
	long time_after_generate_similarity;
	long time_after_deduplicating;
	long time_after_calculating_impact;
} TIMES;

TIMES *construct_times(
	long time_start_running,
	long time_finish_running,
	long time_after_generate_allocation,
	long time_after_generate_popularity,
	long time_after_generate_similarity,
	long time_after_deduplicating,
	long time_after_calculating_impact);

TIMES *construct_empty_times(void);

void destruct_times(TIMES *times);

long get_time_millis(void);

void print_times(TIMES *times);

#endif
