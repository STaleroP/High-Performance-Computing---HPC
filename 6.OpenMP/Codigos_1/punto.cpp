#include <stdio.h>
#include <stdlib.h>

#define SIZE 25000000


double punto(double* a, double* b, int size)
{
	double c = 0;

	#pragma omp parallel for reduction(+:c)
	for (int i = 0; i < size; ++i)
	{
		c += a[i]*b[i];
	}
	return c;
}


int main()
{
	double* a = (double*)malloc(sizeof(double)*SIZE);
	double* b = (double*)malloc(sizeof(double)*SIZE);

	double c = punto(a, b, SIZE);

	free(b);
	free(a);

	return 0;
}
