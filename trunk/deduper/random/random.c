# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include "random.h"

int choose_number(int *numbers, int n)
{
	int seed = 0;
	int random_index = 0;

	if (!n)
	{
		return 0;
	}	
	
	seed = time(NULL);
	srand(seed);
	random_index = rand() % n;

	return numbers[random_index];
}
