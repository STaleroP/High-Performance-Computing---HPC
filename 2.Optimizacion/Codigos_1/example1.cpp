// example1.cpp
// g++ -o example1 example1.cpp
// time ./example1

#define ROWS 10000000
#define COLS 100

int main(void)
{
	char* matrix = new char[ROWS*COLS];

	for (int j = 0; j < COLS; ++j)
	{
		for (int i = 0; i < ROWS; ++i)
		{
			matrix[i*COLS + j] = 0;
		}
	}

	delete [] matrix;

	return 0;
}
