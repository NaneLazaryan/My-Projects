#include <iostream>
#include <vector>

template <typename It>
void BubbleSort(It begin, It end) {
	It lastUnordered = end;
	for (auto i = begin; i != end; i++) {
		bool swapped = false;
		for (auto j = begin; std::next(j) != lastUnordered; j++) {
			It nextIt = std::next(j);
			if (*j > *nextIt) {
				std::swap(*j, *nextIt);
				swapped = true;
			}
		}
		lastUnordered--;
		if (!swapped) break;
	}
}

int main() {

	std::vector<int> arr = { 9,2,3,4,10,1,61,5 }; 
	std::cout << "Before Bubble sort." << std::endl;
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;

	BubbleSort(arr.begin(),arr.end());
	std::cout << "After Bubble sort." << std::endl;
	for (int i = 0; i < arr.size(); i++) {
		std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}
