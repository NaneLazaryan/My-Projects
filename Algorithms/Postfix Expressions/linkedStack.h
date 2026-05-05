#pragma once

#include "stack.h"
#include "node.h"
#include <assert.h>

template <typename T>
class linkedStack : public Stack<T>
{
public:
	linkedStack() : m_top(nullptr) {}

	// copy constructor / assignment 
	linkedStack(const linkedStack&);
	const linkedStack& operator=(const linkedStack&);

	// move constructor / assignment 
	linkedStack(linkedStack&&) noexcept;
	const linkedStack& operator=(linkedStack&&) noexcept; 

	~linkedStack() = default;

	virtual void push(const T&) override;
	virtual void pop() override;
	virtual void clear() override;
	virtual const T& top() const override;
	virtual bool empty() const override;
private:
	Node<T>* m_top;
};


#include "linkedStack.ipp"