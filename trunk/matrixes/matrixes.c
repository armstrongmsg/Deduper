# include <stdio.h>
# include "matrixes.h"

void print_matrix(int *matrix, int rows, int columns)
{
        int i = 0;

        for ( ; i < rows*columns; i++)
        {
                if (!(i % columns))
                {
                        printf("\n");
                }               
		
		printf("%d ", matrix[i]);
        }
	
	printf("\n");
}
