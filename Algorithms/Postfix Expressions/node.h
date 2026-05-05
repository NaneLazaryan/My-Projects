#pragma once

template <typename T>
struct Node
{
	Node(const T& v, Node<T>* n = nullptr) : val(v), next(n) {}

	T val;
	Node<T>* next;
};