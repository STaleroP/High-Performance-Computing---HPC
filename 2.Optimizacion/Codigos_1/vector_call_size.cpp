// g++ vector_call_size.cpp -o vector_call_size
// time ./vector_call_size

#include <vector>

int main(){
	int size = 10000000;
	std::vector<int> a(size);
	
	for (int t = 0; t < 120; ++t){
		for (int i = 0; i < a.size(); ++i){
			a[i] = i;
		}
	}
	
	return a[size - 1];
}
