#include "DoubleLinkedList.h"

int main() {
	DoubleLinkedList<double> list;

	std::cout << "Is list empty? " << (list.empty() ? "Yes" : "No") << std::endl;

	list.push_back(5.12);
	list.push_front(20);
	list.push_back(-6);
	list.push_front(-6.5);

	list.display();

	list.pop_back();
	list.pop_front();

	list.reverse();
	std::cout << "After pop and reverse..." << std::endl;
	list.display();

	list.remove(20);
	std::cout << "After removing (20)..." << std::endl;
	list.display();

	list.clear();
	std::cout << "After clearing..." << std::endl;
	list.display();

}
