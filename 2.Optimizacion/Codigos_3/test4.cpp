// time ./test4 50000000

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
	
	for (int i = 0; i < size; ++i)
	{
		X.data[i] = X.data[i] + a*P.data[i];
		R.data[i] = R.data[i] + a*W.data[i];
	}

	return 0;
}
