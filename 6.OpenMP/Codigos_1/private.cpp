// PrivateVsFirstprivate.cpp
#include <stdio.h>

int main()
{
	int a = 7;

	#pragma omp parallel private(a)
	{
		printf("private a = %i\n", a);
	}

	#pragma omp parallel firstprivate(a)
	{
		printf("firstprivate a = %i\n", a);
	}

	return 0;
}
