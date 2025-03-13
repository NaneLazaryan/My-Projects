#ifndef DoubleLinkedList_H_
#define DoubleLinkedList_H_

#include <iostream>

template <typename T>
class DoubleLinkedList {
public:
	struct Node {
		Node* next;
		Node* prev;
		T data;

		Node(T value) :data(std::move(value)), next(nullptr), prev(nullptr) {}
	};

	DoubleLinkedList() :head(nullptr) {}
	~DoubleLinkedList() { clear(); }

	bool empty() const {
		return head == nullptr;
	}

	std::size_t size() const {
		if (empty()) return 0;

		Node* node = head;
		std::size_t size = 0;
		while (node != nullptr) {
			node = node->next;
			size++;
		}

		return size;
	}

	Node* first() {
		return head;
	}

	Node* last() {
		Node* pNode = head;
		while (pNode->next != nullptr && pNode != nullptr) {
			pNode = pNode->next;
		}
		return pNode;
	}

	template <typename... Args>
	void insert(Node* pNode, Args&&... args) {
		if (!pNode) return;

		Node* newNode = new Node(std::forward<Args>(args)...);
		newNode->prev = pNode;
		newNode->next = pNode->next;
		pNode->next = newNode;
		(newNode->next)->prev = newNode;
	}

	template <typename... Args>
	void push_front(Args&&... args) {
		Node* newNode = new Node(std::forward<Args>(args)...);
		if (!head) {
			head = newNode;
			return;
		}
		head->prev = newNode;
		newNode->next = head;
		head = newNode;
	}

	template <typename... Args>
	void push_back(Args&&... args) {
		Node* newNode = new Node(std::forward<Args>(args)...);
		if (!head) {
			head = newNode;
			return;
		}
		Node* lastNode = last();
		lastNode->next = newNode;
		newNode->prev = lastNode;
	}

	void clear() {
		Node* pNode = head;
		while (pNode != nullptr) {
			Node* nextNode = pNode->next;;
			delete pNode;
			pNode = nextNode;
		}
		head = nullptr;
	}

	void pop_back() {
		if (!head) return;
		Node* lastNode = last();
		(lastNode->prev)->next = nullptr;
		delete lastNode;
	}

	void pop_front() {
		if (!head) return;
		Node* firstNode = head;
		head = head->next;
		head->prev = nullptr;
		delete firstNode;
	}

	void remove(const T& value) {
		if (!head) return;

		if (head->data == value) {
			pop_front();
			return;
		}

		Node* prevNode = head;
		while (prevNode->next && prevNode->next->data != value) {
			prevNode = prevNode->next;
		}

		if (prevNode->next) {
			Node* pNode = prevNode->next;
			prevNode->next = prevNode->next->next;
			if (pNode->next) {
				pNode->next->prev = prevNode;
			}
			delete pNode;
		}
	}

	void splice(DoubleLinkedList<T>& other) {
		Node* lastNode = last();
		if (lastNode == nullptr) {
			head = other.head;
		}
		else {
			lastNode->next = other.head;
			other.head->prev = lastNode;
		}
		other.head = nullptr;
	}

	void reverse() {
		if (head == nullptr) return;
		Node* pNode = head->next;
		Node* prevNode = head;
		Node* nextNode = nullptr;

		prevNode->next = nullptr;

		while (pNode != nullptr) {
			nextNode = pNode->next;
			pNode->next = prevNode;
			pNode->prev = nextNode;
			//nextNode->next = pNode;
			prevNode = pNode;
			pNode = nextNode;
		}
		head = prevNode;
	}

	void display() {
		if (head == nullptr) {
			std::cout << "List empty." << std::endl;
			return;
		}

		Node* p = head;

		while (p) {
			std::cout << p->data;
			if (p->next) {
				std::cout << " -> ";
			}
			p = p->next;
		}
		std::cout << std::endl << "=====================================" << std::endl;
	}

private:
	Node* head;
};

#endif // !DoubleLinkedList_H_