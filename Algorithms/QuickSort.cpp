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
	std::vector<int> vec = { 5,2,10,9,65,13,1 };
	std::cout << "Vector before Quick Sort." << std::endl;
	for (const int& i : vec) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	QuickSort(vec, 0, vec.size() - 1);
	std::cout << "Vector after Quick Sort." << std::endl;
	for (const int& i : vec) {
		std::cout << i << " ";
	}
	std::cout << std::endl;

	return 0;
}
