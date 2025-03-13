
#include "SingleLinkedList.h"

int main() {
    SingleLinkedList<int> list;

    std::cout << "Is list empty? " << (list.empty() ? "Yes" : "No") << std::endl;

    list.push_front(10);
    list.push_back(20);
    list.push_front(5);
    list.push_back(25);

    std::cout << "List after push operations: ";
    list.display();
    std::cout << std::endl;

    std::cout << "Size of list: " << list.size() << std::endl;

    list.remove(10);
    std::cout << "List after removing 10: ";
    list.display();
    std::cout << std::endl;

    list.reverse();
    std::cout << "List after reversing: ";
    for (SingleLinkedList<int>::Iterator it = list.begin(); it != list.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;


    list.clear();
    std::cout << "\nList after clearing: ";
    list.display();
    std::cout << std::endl;
  

    return 0;
}
