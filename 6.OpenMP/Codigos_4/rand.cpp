// rand.cpp
// g++ -fopenmp rand.cpp -o rand
// OMP_NUM_THREADS=24; ./rand

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main()
{	
	int n = omp_get_max_threads();
	double* r = new double[n];

	printf("omp_get_max_threads = %i\n", n);

	#pragma omp parallel for
	for (int t = 0; t < n; ++t)
	{
		r[t] = rand()*3.141592654/RAND_MAX;
	}

	printf("Parallel rand()\n");
	for (int t = 0; t < n; ++t)
	{
		printf("r(%i) = %g\n", t, r[t]);
	}

	for (int t = 0; t < n; ++t)
	{
		r[t] = rand()*3.141592654/RAND_MAX;
	}

	printf("Serial rand()\n");
	for (int t = 0; t < n; ++t)
	{
		printf("r(%i) = %g\n", t, r[t]);
	}

	delete [] r;

	return 0;
}
