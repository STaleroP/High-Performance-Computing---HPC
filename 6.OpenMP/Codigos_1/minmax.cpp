#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000000


int main()
{
	double* a = (double*)malloc(sizeof(double)*SIZE);

	for (int i = 0; i < SIZE; ++i)
	{
		a[i] = rand()/(double)RAND_MAX;
	}
	
	double minimum = a[0];
	double maximum = a[0];
	#pragma omp parallel for reduction(min:minimum) reduction(max:maximum)
	for (int i = 1; i < SIZE; ++i)
	{
		if (minimum > a[i])
			minimum = a[i];
		else if (maximum < a[i])
			maximum = a[i];
	}

	printf("minumum = %g\nmaximum = %g\n\n", minimum, maximum);

	free(a);

	return 0;
}
