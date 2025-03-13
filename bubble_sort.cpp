// bubble_sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

//void BubbleSort(std::vector<int>& A) {
//	int size = A.size();
//	for (int i = 0; i < size-1; i++) {
//		bool swapped = false;
//		for (int j = 0; j < size - i - 1; j++) {
//			if (A[j] > A[j + 1]) {
//				std::swap(A[j], A[j + 1]);
//				swapped = true;
//			}
//		}
//		if (!swapped) break;
//	}
//}


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