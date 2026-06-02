// sum5.cpp
#include <stdio.h>

float a[] = {1.0, 1.0e-8, 2.0e-8,
             3.0e-8, 4.0e-8, 5.0e-8,
             1.0e-8, 2.0e-8, 3.0e-8,
             4.0e-8, 5.0e-8};

int main()
{
	float sum = 0;
	float c = 0;
	for (int i = 0; i < 11; ++i)
	{
		float y = a[i] + c;
		float t = sum + y;
		c = y - (t - sum);
		sum = t;
	}

	printf("Sum = %1.9f\n", sum);

	return 0;
}
