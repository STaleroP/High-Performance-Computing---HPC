// sum3.cpp
#include <stdio.h>

float a[] = {1.0e-8, 1.0e-8, 2.0e-8,
             2.0e-8, 3.0e-8, 3.0e-8,
             4.0e-8, 4.0e-8, 5.0e-8,
             5.0e-8, 1.0};

int main()
{
	float sum = 0;
	for (int i = 0; i < 11; ++i)
	{
		sum += a[i];
	}

	printf("Sum = %1.9f\n", sum);

	return 0;
}
