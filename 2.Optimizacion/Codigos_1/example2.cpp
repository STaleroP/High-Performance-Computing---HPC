// example2.cpp
// g++ -o example2 example2.cpp
// time ./example2

#define ROWS 10000000
#define COLS 100

int main(void)
{
	char* matrix = new char[ROWS*COLS];

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j)
		{
			matrix[i*COLS + j] = 0;
		}
	}

	delete [] matrix;

	return 0;
}
