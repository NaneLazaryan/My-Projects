#ifndef SET_H_
#define SET_H_

#include "Node.h"
#include <stack>

template <typename T>
class Set {
public:

	Set() :root(nullptr), m_size(0) {}
	~Set() {
		clear();
	}

	class Iterator {
	private:
		Node<T>* currentNode;
		std::stack<Node<T>*> nodeStack;
	public:
		Iterator() noexcept : currentNode(nullptr) {}
		Iterator(Node<T>* root) noexcept : currentNode(nullptr) {
			while (root) {
				nodeStack.push(root);
				root = root->getLeftChild();
			}
			if (!nodeStack.empty()) {
				currentNode = nodeStack.top();
			}
		}

		Iterator& operator=(Node<T>* node) {
			currentNode = node;
			return *this;
		}

		T operator*() const {
			return currentNode->getData();
		}

		Iterator& operator++() {
			if (nodeStack.empty()) {
				currentNode = nullptr;
				return *this;
			}

			Node<T>* node = nodeStack.top();
			nodeStack.pop();

			if (node->getRightChild()) {
				node = node->getRightChild();
				while (node) {
					nodeStack.push(node);
					node = node->getLeftChild();
				}
			}

			if (nodeStack.empty()) {
				currentNode = nullptr;
			}
			else {
				currentNode = nodeStack.top();
			}
			return *this;
		}

		bool operator==(const Iterator& it) const {
			return currentNode == it.currentNode;
		}

		bool operator!=(const Iterator& it) const {
			return currentNode != it.currentNode;
		}
	};

	Iterator begin() {
		if (empty()) return end();
		return Iterator(root);
	}

	Iterator end() {
		return Iterator();
	}

	void insert(const T& value) {
		if (!root->containsNode(root, value)) {
			root = root->insert(root, value);
			m_size++;
		}
	}

	bool contains(const T& value) const {
		return root->containsNode(root, value);
	}

	size_t size() const {
		return m_size;
	}

	bool empty() const {
		return m_size == 0;
	}

	void remove(const T& value) {
		if (root->containsNode(root, value)) {
			root = root->remove(root, value);
			m_size--;
		}
	}

	void clear() {
		root->deleteTree(root);
		root = nullptr;
		m_size = 0;
	}

	void print() const {
		root->inorder(root);
		std::cout << std::endl;
	}

private:
	Node<T>* root;
	size_t m_size;
};

#endif // !SET_H_

