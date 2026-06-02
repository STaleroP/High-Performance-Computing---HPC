#include <stdio.h>
#include <omp.h>

int main()
{

	int m = omp_get_max_threads();
	printf("omp_get_max_threads = %i\n", m);

	#pragma omp parallel
	{
		int t = omp_get_thread_num();
		printf("  omp_get_thread_num = %i\n", t);
	}

	return 0;
}
