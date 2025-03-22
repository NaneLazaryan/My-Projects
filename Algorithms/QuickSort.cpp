// QuickSort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

template <typename T>
size_t Partition(std::vector<T>& A, size_t p, size_t r) {
	T pivot = A[r];
	size_t i = p - 1;
	for (size_t j = p; j <= r - 1; j++) {
		if (A[j] <= pivot) {
			i++;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[i + 1], A[r]);
	return i + 1;
}

template <typename T>
void QuickSort(std::vector<T>& A, size_t p, size_t r) {
	if (p < r) {
		size_t q = Partition(A, p, r);
		if (q > 0) QuickSort(A, p, q - 1);
		QuickSort(A, q + 1, r);
	}
}

int main() {
	// Test for int type
	std::vector<int> vec1 = { 5,2,10,9,65,13,1 };
	std::cout << "Vector before Quick Sort." << std::endl;
	for (const int& i : vec1) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	QuickSort(vec1, 0, vec1.size() - 1);
	std::cout << "Vector after Quick Sort." << std::endl;
	for (const int& i : vec1) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	// Test for double type
	std::vector<double> vec2 = { 5.2,0,1.3,6.5 };
	std::cout << "\nVector before Quick Sort." << std::endl;
	for (const double& i : vec2) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	QuickSort(vec2, 0, vec2.size() - 1);
	std::cout << "Vector after Quick Sort." << std::endl;
	for (const double& i : vec2) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	return 0;
}
