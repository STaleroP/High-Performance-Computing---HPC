#include <assert.h>

#define ROWS 10000000
#define COLS 100

void Set(char* matrix, int i, int j, char value)
{
	assert((i >= 0) && (i < ROWS));
	assert((j >= 0) && (j < COLS));

	matrix[i*COLS + j] = value;
}


int main()
{
	char* matrix = new char[ROWS*COLS];

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			Set(matrix, i, j, 0);
		}
	}

	delete [] matrix;

	return 0;
}
