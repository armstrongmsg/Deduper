# include <stdio.h>
# include <assert.h>
# include "timer.h"

void test_construct_empty_times(void)
{
	TIMES *new_times = construct_empty_times();

	assert(new_times);

	assert(new_times->time_start_running == -1);
	assert(new_times->time_finish_running == -1);
	assert(new_times->time_after_generate_allocation == -1);
        assert(new_times->time_after_generate_popularity == -1);
        assert(new_times->time_after_generate_similarity == -1);
        assert(new_times->time_after_deduplicating == -1);
       	assert(new_times->time_after_calculating_impact == -1);

	destruct_times(new_times);
}

void test_get_time_millis(void)
{
	long time_start_running = clock()/(CLOCKS_PER_SEC/1000);

	long get_time_millis_call_1 = get_time_millis();
	long get_time_millis_call_2 = get_time_millis();
	assert(get_time_millis_call_1 >= time_start_running);
	assert(get_time_millis_call_2 >= get_time_millis_call_1);
}

int main(void)
{
	test_construct_empty_times();
	puts("passed on test_construct_empty_times");
	test_get_time_millis();
	puts("passed on test_get_time_millis");

	return 0;
}

