#include <stdio.h>

int main()
{
	printf("Test 1\n");

#if !defined(NDEBUG)
	printf("Test 2\n");
#endif

	printf("Test 3\n");
}
