// time ./test2 50000000

#include "Vector.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 2)
		return 0;
	
	int size = atoi(argv[1]);;

	Vector A(size);
	Vector B(size);
	Vector C(size);
	double r = 1;
	
	for (int i = 0; i < size; ++i)
	{
		C.data[i] = -A.data[i] + r*B.data[i];
	}

	return 0;
}