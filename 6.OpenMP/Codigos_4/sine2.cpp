// sine2.cpp
// g++ -fopenmp sine2.cpp -o sine2
// OMP_NUM_THREADS=1; time ./sine2

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define STEPS 20000000

int main()
{	
	int n = omp_get_max_threads();
	double* s = new double[n];
	double* r = new double[n];
	
	printf("omp_get_max_threads = %i\n", n);
	
	for (int t = 0; t < n; ++t)
	{
		r[t] = rand()*3.141592654/RAND_MAX;
	}

	#pragma omp parallel
	{
		int t = omp_get_thread_num();
		double x = r[t];
		
		double sum = x;
		double term = x;
		for (int i = 0, j = 2; i < STEPS; ++i, j += 2)
		{
			term *= -x*x/j/(j + 1);
			sum += term;
		}
		s[t] = sum;
	}

	for (int t = 0; t < n; ++t)
	{
		printf("sin(%g) = %g\n", r[t], s[t]);
	}

	delete [] r;
	delete [] s;
	return 0;
}
