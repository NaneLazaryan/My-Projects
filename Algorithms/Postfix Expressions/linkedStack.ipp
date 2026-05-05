#pragma once

#include "linkedStack.h"
#include <cassert>
#include <vector>

// Copy Constructor
template <typename T>
linkedStack<T>::linkedStack(const linkedStack<T>& other)
{
    if (other.empty()) return;

    std::vector<T> nodes;
    Node<T>* tmp = other.m_top;
    nodes.push_back(tmp->val);

    while (tmp->next) {
        tmp = tmp->next;
        nodes.push_back(tmp->val);
    }

    for (int i = nodes.size() - 1; i >= 0; i--) {
        push(nodes[i]);
    }
}

// Copy Assignment
template <typename T>
const linkedStack<T>& linkedStack<T>::operator=(const linkedStack<T>& other)
{
    if (this == &other) return *this;
    clear();  // clear old data

    if (other.empty()) return *this;

    std::vector<T> nodes;
    Node<T>* tmp = other.m_top;
    nodes.push_back(tmp->val);

    while (tmp->next) {
        tmp = tmp->next;
        nodes.push_back(tmp->val);
    }

    for (int i = nodes.size() - 1; i >= 0; i--) {
        push(nodes[i]);
    }

    return *this;
}

// Move Constructor
template <typename T>
linkedStack<T>::linkedStack(linkedStack<T>&& other) noexcept
{
    if (other.empty()) return;
    
    m_top = other.m_top;
    other.m_top = nullptr;
}

// Move Assignment
template <typename T>
const linkedStack<T>& linkedStack<T>::operator=(linkedStack<T>&& other) noexcept
{
    if (this == &other) return *this;
    clear(); // clear old data

    if (other.empty()) return *this;

    m_top = other.m_top;
    other.m_top = nullptr;

    return *this;
}


template <typename T>
bool linkedStack<T>::empty() const
{
    return m_top == nullptr;
}

template <typename T>
const T& linkedStack<T>::top() const
{
    assert(m_top != nullptr);
    return m_top->val;
}

template <typename T>
void linkedStack<T>::pop()
{
    if (empty())
        return;
    Node<T>* temp = m_top;
    m_top = m_top->next;
    delete temp;
}

template <typename T>
void linkedStack<T>::push(const T& newVal)
{
    m_top = new Node<T>(newVal, m_top);
}

template <typename T>
void linkedStack<T>::clear()
{
    while (!empty())
        pop();
}