// g++ other_operator.cpp -o other_operator
// time ./other_operator

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
	
	inline T& operator [] (int i) const throw()
	{
		return entry[i];
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
			a[i] = i;
		}
	}
	
	return a[size - 1];
}
