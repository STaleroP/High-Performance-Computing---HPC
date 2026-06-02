// g++ vector_simple.cpp -o vector_simple
// time ./vector_simple

#include <vector>

int main(){
	int size = 10000000;
	std::vector<int> a(size);
	
	for (int t = 0; t < 120; ++t){
		for (int i = 0; i < size; ++i){
			a[i] = i;
		}
	}
	
	return a[size - 1];
}
