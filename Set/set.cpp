#include "set.h"

int main() {
	Set<int> mSet;

	if (mSet.empty()) {
		std::cout << "Set empty...\n" << std::endl;
	}

	mSet.insert(5);
	mSet.insert(45);
	mSet.insert(10);
	mSet.insert(9);
	mSet.insert(10);
	mSet.insert(165);
	mSet.insert(22);
	mSet.print();
	std::cout << "Set's size: " << mSet.size() << std::endl;
	
	mSet.remove(10);
	std::cout << "\nSet after removing 10: " << std::endl;
	mSet.print();
	std::cout << "Set's size: " << mSet.size() << std::endl;

	mSet.remove(45);
	std::cout << "\nSet after removing 45: " << std::endl;
	for (auto it = mSet.begin(); it != mSet.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << "\nSet's size: " << mSet.size() << std::endl;

	if (mSet.contains(30)) std::cout << "\nSet contains 30" << std::endl;
	else std::cout << "\nSet does not contain 30" << std::endl;
	
	mSet.clear();
	if (mSet.empty()) {
		std::cout << "Set empty..." << std::endl;
	}
	return 0;
}
