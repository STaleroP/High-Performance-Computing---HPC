// g++ other_simple.cpp -o other_simple
// time ./other_simple

template <typename T>
struct vector
{
	T* entry;
	int size;
	
	vector(int new_size = 0)
	:	entry(new T[new_size]),
		size(new_size)
	{
	}

	~vector() throw()
	{
		delete [] entry;
	}
};

int main()
{
	int size = 10000000;
	vector<int> a(size);
	
	for (int t = 0; t < 120; ++t)
	{
		for (int i = 0; i < a.size; ++i)
		{
			a.entry[i] = i;
		}
	}
	
	return a.entry[size - 1];
}
