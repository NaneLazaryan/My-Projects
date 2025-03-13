#include <iostream>
using namespace std;

void merge(int arr[], int start, int end, int mid) {
	int n1 = mid - start + 1;
	int n2 = end - mid;
	int new_arr1[20], new_arr2[20];
	
	for (int i = 0; i < n1; i++)
		new_arr1[i] = arr[start + i];
	for (int i = 0; i < n2; i++)
		new_arr2[i] = arr[mid + 1 + i];

	int i = 0, j = 0, k = start;

	while (i < n1 && j < n2) {
		if (new_arr1[i] <= new_arr2[j]) {
			arr[k] = new_arr1[i];
			i++;
		}
		else {
			arr[k] = new_arr2[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = new_arr1[i];
		k++;
		i++;
	}

	while (j < n2) {
		arr[k] = new_arr2[j];
		k++;
		j++;
	}
}

void merge_sort(int arr[], int start, int end) {
	if (start < end) {
		int mid = (start + end) / 2;

		merge_sort(arr, start, mid);
		merge_sort(arr, mid + 1, end);

		merge(arr, start, end, mid);
	}
}

int binery_search(int arr[], int n, int value) {
	int start = 0, end = n - 1;

	while (start <= end) {
		int mid = (start + end) / 2;

		if (arr[mid] == value) return mid; 
		else if (arr[mid] > value) end = mid - 1; 
		else start = mid + 1; 
	}
	return -1;
}

void print_arr(int arr[], int n) {
	for (int i = 0; i < n; i++) cout << arr[i] << " ";
	cout << endl;
}

int main()
{
	int x[20], n, i;
	do { cout << "n = "; cin >> n; } while (n < 2 || n>20);

	for (i = 0; i < n; i++) {
		cout << "arr[" << i << "] = ";
		cin >> x[i];
	}

	cout << endl;

	merge_sort(x, 0, n - 1);
	cout << "Sorted array." << endl;
	print_arr(x, n);

	cout << endl;

	int element;
	cout << "Enter the element to search for: "; cin >> element;

	int search_position = binery_search(x, n, element);
	if (search_position == -1) 	cout << "Element is missing in the array." << endl;
	else cout << "Element position: " << search_position << endl;

}
