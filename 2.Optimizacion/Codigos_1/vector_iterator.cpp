// g++ vector_iterator.cpp -o vector_iterator
// time ./vector_iterator

#include <vector>

int main(){
	int size = 10000000;
	std::vector<int> a(size);
	
	for (int t = 0; t < 120; ++t){
		int i = 0;
		for (std::vector<int>::iterator it = a.begin(); it != a.end(); ++it, ++i){
			*it = i;
		}
	}
	
	return a.back();
}
