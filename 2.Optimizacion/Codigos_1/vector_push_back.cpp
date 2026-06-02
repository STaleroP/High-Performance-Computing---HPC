// g++ vector_push_back.cpp -o vector_push_back
// time ./vector_push_back

#include <vector>

int main(){
	int size = 10000000;
	std::vector<int> a;
	
	for (int t = 0; t < 120; ++t){
		a.clear();
		for (int i = 0; i < size; ++i){
			a.push_back(i);
		}
	}
	
	return a.back();
}
