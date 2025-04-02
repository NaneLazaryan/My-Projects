#ifndef NODE_H_
#define NODE_H_

#include <iostream>

template <typename T>
struct Node {
private:
	Node* leftChild;
	Node* rightChild;
	T data;

public:

	Node(const T& value) :data(value), leftChild(nullptr), rightChild(nullptr) {}

	Node* insert(Node* node, const T& value) {
		if (!node) {
			return new Node(value);
		}

		if (value < node->data) {
			node->leftChild = insert(node->leftChild, value);
		}
		else if (value > node->data) {
			node->rightChild = insert(node->rightChild, value);
		}
		return node;
	}

	void deleteTree(Node* node) {
		if (node) {
			deleteTree(node->leftChild);
			deleteTree(node->rightChild);
			delete node;
		}
	}

	bool containsNode(Node* node, const T& value) const {
		if (!node) {
			return 0;
		}

		if (value == node->data) {
			return 1;
		}

		if (value > node->data) {
			return containsNode(node->rightChild, value);
		}
		
		return containsNode(node->leftChild, value);
	}

	// Function to print the inorder traversal of the BST
	void inorder(Node* node)  const {
		if (!node) return;
		inorder(node->leftChild);
		std::cout << node->data << " ";
		inorder(node->rightChild);
	}

	Node* findMin(Node* node) const {
		if (!node) return nullptr;

		while (node->leftChild) {
			node = node->leftChild;
		}
		return node;
	}

	Node* findMax(Node* node) const {
		if (!node) return nullptr;

		while (node->rightChild) {
			node = node->rightChild;
		}
		return node;
	}

	Node* remove(Node* node, const T& value) {
		if (!node) return nullptr;

		if (value < node->data) {
			node->leftChild = remove(node->leftChild, value);
		}
		else if (value > node->data) {
			node->rightChild = remove(node->rightChild, value);
		}
		else {
			if (!node->leftChild) {
				Node* temp = node->rightChild;
				delete node;
				return temp;
			}
			else if (!node->rightChild) {
				Node* temp = node->leftChild;
				delete node;
				return temp;
			}
			Node* temp = findMin(node->rightChild);
			node->data = temp->data;
			node->rightChild = remove(node->rightChild, temp->data);
		}
		return node;
	}

	Node* getLeftChild() const {
		return leftChild;
	}

	Node* getRightChild() const {
		return rightChild;
	}

	T getData() const {
		return data;
	}
};

#endif // !NODE_H_
