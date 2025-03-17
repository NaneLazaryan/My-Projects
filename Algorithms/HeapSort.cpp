#include <iostream>
#include <vector>

int Left(int i) {
	return 2 * i + 1;
}

int Right(int i) {
	return 2 * i + 2;
}

template <typename T>
void MaxHeapify(std::vector<T>& A, int rootIndex, size_t heap_size) {
	int leftChild = Left(rootIndex);
	int rightChild = Right(rootIndex);
	int largest = rootIndex;

	if (leftChild < heap_size && A[leftChild] > A[rootIndex]) {
		largest = leftChild;
	}
	if (rightChild < heap_size && A[rightChild] > A[largest]) {
		largest = rightChild;
	}

	if (largest != rootIndex) {
		std::swap(A[largest], A[rootIndex]);
		MaxHeapify(A, largest, heap_size);
	}	
}

template <typename T>
void BuildMaxHeap(std::vector<T>& A) {
	size_t heap_size = A.size();
	for (int i = heap_size / 2 - 1; i >= 0; --i) {
		MaxHeapify(A, i, heap_size);
	}
}


template <typename T>
void HeapSort(std::vector<T>& A) {
	BuildMaxHeap(A);
	size_t heap_size = A.size();
	for (size_t i = heap_size - 1; i > 0; --i) {
		std::swap(A[0], A[i]);
		MaxHeapify(A, 0, i);
	}
}


int main() {
	std::vector<int> vec = { 5,8,10,1,0,22,3 };

	std::cout << "Vector before sorting..." << std::endl;
	for (const auto& i : vec) {
		std::cout << i << " ";
	}

	HeapSort(vec);

	std::cout << "\nVector after sorting..." << std::endl;
	for (const auto& i : vec) {
		std::cout << i << " ";
	}

	return 0;
}
