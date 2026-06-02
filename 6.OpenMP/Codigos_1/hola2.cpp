#include <stdio.h>
#include <omp.h>


int main()
{
	#pragma omp parallel
	{
		int thread = omp_get_thread_num();
		printf("Hola mundo (thread %i)\n", thread);
	}

	return 0;
}
