// time ./test3 50000000

#include "Vector.h"
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 2) return 1;

	int size = atoi(argv[1]);

	Vector X(size);
	Vector P(size);
	Vector W(size);
	Vector R(size);
	double a = 1;
	
	X = X + a*P;
	R = R + a*W;
	
	return 0;
}
