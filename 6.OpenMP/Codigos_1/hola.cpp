#include <stdio.h>


int main()
{
	#pragma omp parallel
	{
		printf("Hola mundo\n");
	}

	return 0;
}
