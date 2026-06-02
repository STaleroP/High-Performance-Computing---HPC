#include <stdio.h>
#include <stdlib.h>

#define SIZE 25000000


void suma(double* a, double* b, double*c, int size)
{
	#pragma omp parallel for
	for (int i = 0; i < size; ++i)
	{
		c[i] = a[i] + b[i];
	}

}


int main()
{
	double* a = (double*)malloc(sizeof(double)*SIZE);
	double* b = (double*)malloc(sizeof(double)*SIZE);
	double* c = (double*)malloc(sizeof(double)*SIZE);

	suma(a, b, c, SIZE);

	free(c);
	free(b);
	free(a);

	return 0;
}
