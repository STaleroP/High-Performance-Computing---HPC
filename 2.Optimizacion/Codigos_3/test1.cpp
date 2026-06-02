// time ./test1 50000000

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
	
	C = -A + r*B;
	
	return 0;
}