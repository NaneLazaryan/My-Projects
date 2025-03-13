#include "allocator.h"
#include <vector>
#include <iostream>

int main() {
	std::vector<int, Allocator<int>> vec;
	
	Allocator<int> allocator;

	int* p = allocator.allocate(5);

	int x = 10;
	allocator.construct(p, x);
	std::cout << *p << std::endl;

	/*vec.push_back(45);
	vec.push_back(5);
	vec.push_back(88);
	vec.push_back(-5);*/

	/*for (size_t i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << std::endl;
	}*/
	
	return 0;  
}
