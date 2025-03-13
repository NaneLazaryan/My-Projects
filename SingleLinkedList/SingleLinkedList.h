#ifndef SingleLinkedList_H_
#define SingleLinkedList_H_

#include <iostream>

template <typename T>
class SingleLinkedList {
public:
	struct Node {
		T data;
		Node* next;

		Node(T value) :data(std::move(value)), next(nullptr) {}
	};

	SingleLinkedList() :m_head(nullptr) {}
	~SingleLinkedList() {
		clear();
	}

	class Iterator {
	private:
		Node* current_node;
	public:
		Iterator() noexcept : current_node(m_head) {}
		Iterator(Node* node) noexcept : current_node(node) {}
		~Iterator() {}

		Iterator& operator=(Node* node) {
			current_node = node;
			return *this;
		}

		// ++it
		Iterator& operator++() {
			if (current_node) {
				current_node = current_node->next;
			}
			return *this;
		}

		// it++
		Iterator operator++(int) {
			Iterator it = *this;
			++(*this);
			return it;
		}

		T operator*() {
			return current_node->data;
		}

		bool operator==(const Iterator& it) {
			return (current_node = it.current_node);
		}

		bool operator!=(const Iterator& it) {
			return (current_node != it.current_node);
		}
		
	};

	Iterator begin() {
		return Iterator(m_head);
	}

	Iterator end() {
		return Iterator(nullptr);
	}

	bool empty() const {
		return m_head == nullptr;
	}

	std::size_t size()  const {
		if (empty()) return 0;

		const Node* p = m_head;
		std::size_t size = 0;

		while (p != nullptr) {
			p = p->next;
			size++;
		}
		return size;
	}

	const Node* first() const {
		return m_head;
	}

	Node* first() {
		return m_head;
	}

	const Node* last() const {
		Node* p = m_head;
		while (p != nullptr && p->next != nullptr) {
			p = p->next;
		}
		return p;
	}

	Node* last() {
		return const_cast<Node*> (const_cast<const SingleLinkedList<T>*> (this)->last());
	}

	template <typename... Ts>
	void insert(Node* p_node, Ts&&... values) {
		if (!p_node) return;
		Node* newNode = new Node(std::forward<Ts>(values)...);
		newNode->next = p_node->next;
		p_node->next = newNode;
	}

	template <typename... Ts>
	void push_front(Ts&&... values) {
		Node* newNode = new Node(std::forward<Ts>(values)...);
		if (m_head == nullptr) {
			m_head = newNode;
			return;
		}
		newNode->next = m_head;
		m_head = newNode;
	}

	template <typename... Ts>
	void push_back(Ts&&... values) {
		Node* newNode = new Node(std::forward<Ts>(values)...);
		if (m_head == nullptr) {
			m_head = newNode;
			return;
		}
		Node* lastNode = last();
		lastNode->next = newNode;
	}

	void remove(const T& value) {
		if (!m_head) return;

		if (m_head->data == value) {
			Node* p_node = m_head;
			m_head = m_head->next;
			delete p_node;
			return;
		}

		Node* prev = m_head;
		while (prev->next && prev->next->data != value) {
			prev = prev->next;
		}

		if (prev->next) {
			Node* p_node = prev->next;
			prev->next = prev->next->next;
			delete p_node;
		}
	}

	void clear() {
		Node* p = m_head;
		while (p != nullptr) {
			Node* p_next = p->next;
			delete p;
			p = p_next;
		}
		m_head = nullptr;
	}	

	void splice(SingleLinkedList<T>& other) {
		Node* last_node = last();
		if (last_node == nullptr) {
			m_head = other.m_head;
		}
		else {
			last_node->next = other.m_head;
		}
		other.m_head = nullptr;
	}

	void reverse() {
		if (m_head == nullptr) return;

		Node* p_node = m_head->next;
		Node* prev_node = m_head;
		Node* next_node = nullptr;

		prev_node->next = nullptr;

		while (p_node != nullptr) {
			next_node = p_node->next;
			p_node->next = prev_node;
			prev_node = p_node;
			p_node = next_node;
		}
		m_head = prev_node;
	}

	void display() {
		if (m_head == nullptr) {
			std::cout << "List empty." << std::endl;
			return;
		}

		Node* p = m_head;
		while (p) {
			std::cout << p->data;
			if (p->next) {
				std::cout << " -> ";
			}
			p = p->next;
		}
		std::cout << std::endl;
	}

private:
	Node* m_head;
};

#endif // !SingleLinkedList_H_
