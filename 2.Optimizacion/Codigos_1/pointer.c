// gcc pointer.c -o pointer
// time ./pointer

#include <malloc.h>

int main(void)
{
	int size;
	int* a;
	int t, i;

	size = 10000000;
	a = (int*)malloc(size*sizeof(int));
	
	for (t = 0; t < 120; ++t)
	{
		for (i = 0; i < size; ++i)
		{
			a[i] = i;
		}
	}

	return a[size - 1];
}
