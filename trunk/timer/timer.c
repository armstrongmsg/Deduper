# include <stdio.h>
# include <stdlib.h>
# include <assert.h>
# include <time.h>
# include "timer.h"

TIMES *construct_times(
        long time_start_running,
        long time_finish_running,
        long time_after_generate_allocation,
        long time_after_generate_popularity,
        long time_after_generate_similarity,
        long time_after_deduplicating,
        long time_after_calculating_impact)
{
	TIMES *new_times = NULL;

	assert(time_start_running >= -1);
	assert(time_finish_running >= -1);
	assert(time_after_generate_allocation >= -1);
	assert(time_after_generate_popularity >= -1);
	assert(time_after_generate_similarity >= -1);
	assert(time_after_deduplicating >= -1);
	assert(time_after_calculating_impact >= -1);

	new_times = (TIMES *) malloc(sizeof(TIMES));
	
	assert(new_times);	

	new_times->time_start_running = time_start_running;
	new_times->time_finish_running = time_finish_running;
	new_times->time_after_generate_allocation = time_after_generate_allocation;
	new_times->time_after_generate_popularity = time_after_generate_popularity;
	new_times->time_after_generate_similarity = time_after_generate_similarity;
	new_times->time_after_deduplicating = time_after_deduplicating;
	new_times->time_after_calculating_impact = time_after_calculating_impact;

	return new_times;
}

TIMES *construct_empty_times(void)
{
	return construct_times(-1, -1, -1, -1, -1, -1, -1);
}

void destruct_times(TIMES *times)
{
	assert(times);
	free(times);
}

long get_time_millis(void)
{
	return clock()/CLOCKS_PER_MILISEC;	
}

void print_times(TIMES *times)
{
	assert(times);
	
 	printf("time_start_running->%ld\n", times->time_start_running);
 	printf("time_finish_running->%ld\n", times->time_finish_running);
 	printf("time_after_generate_allocation->%ld\n", times->time_after_generate_allocation);
 	printf("time_after_generate_popularity->%ld\n", times->time_after_generate_popularity);
 	printf("time_after_generate_similarity->%ld\n", times->time_after_generate_similarity);
 	printf("time_after_deduplicating->%ld\n", times->time_after_deduplicating);
 	printf("time_after_calculating_impact->%ld\n", times->time_after_calculating_impact);
}
