#pragma once

#include <string>
#include "linkedStack.h"
#include <exception>

enum class Operator 
{
	Add,      // +
	Subtract, // -
	Multiply, // *
	Divide,   // /
	Power,    // ^
	UNKONWN
};

Operator toOperator(char c)
{
	switch (c)
	{
	case '+': return Operator::Add;
	case '-': return Operator::Subtract;
	case '*': return Operator::Multiply;
	case '/': return Operator::Divide;
	case '^': return Operator::Power;
	default: return Operator::UNKONWN;
	}
}

char getPrevious(const std::string& str, size_t index)
{
	if (index <= 0) return '\0';
	return str[index - 1];
}

char getNext(const std::string& str, size_t index)
{
	if (index >= str.size() - 1) return '\0';
	return str[index + 1];
}

bool isOperand(char c)
{
	return std::isalpha(c) || std::isdigit(c);
}

bool isOperator(char c)
{
	if (toOperator(c) == Operator::UNKONWN) return false;
	return true;
}

// Check validation of input string
bool isValid(const std::string input)
{
	size_t index = -1;
	int count = 0;  // for checking parenthesis 

	for (char c : input) {
		index++;
		char prev = getPrevious(input, index);
		char next = getNext(input, index);

		if (isOperator(c)) {
			if (index == 0 || index == input.size() - 1) {
				std::cout << "Invalid Input: Expression cannot start or end with operator " << c << std::endl;
				return false;
			}

			if (next == ')' || prev == '(') {
				std::cout << "Invalid Input: An operator should always be surrounded by operands" << std::endl;
				return false;
			}

			if (isOperator(next)) {
				std::cout << "Invalid Input: Two operators should not appear consecutively " << std::endl;
				return false;
			}
		}
		if (std::isalpha(c) && index < input.size() - 1 && isOperand(c) && !isOperator(next) && next != ')') {
			std::cout << "Invalid Input: Two operands should not appear consecutively" << std::endl; // For numbers allowed
			return false;
		}
		if (c == '(' && next == ')') {
			std::cout << "Invalid Input: Empty set of parentheses ()" << std::endl;
			return false;
		}
		if (c == '(') count++;
		if (c == ')') count--;
	}

	if (count != 0) {
		std::cout << "Invalid Input: Every opening parenthesis must have a closing parenthesis" << std::endl;
		return false;
	}

	return true;
}


int priority(char c)
{
	Operator op = toOperator(c);
	switch (op)
	{
	case Operator::Add:
	case Operator::Subtract:
		return 1;
	case Operator::Multiply:
	case Operator::Divide:
		return 2;
	case Operator::Power:
		return 3;
	}
	return -1;
}


std::string toPostfix(const std::string& input)
{
	linkedStack<char> st;
	std::string result;
	 
	for (char c : input) {
		if (c == '(')
			st.push(c);
		else if (c == ')') {
			while (!st.empty() && st.top() != '(') {
				result.push_back(' ');
				result.push_back(st.top());
				st.pop();
			}
			st.pop();
		}
		else if (isOperator(c)) {
			result.push_back(' ');
			while (!st.empty() && priority(c) <= priority(st.top())) {
				result.push_back(st.top());
				st.pop();
			}
			st.push(c);
		}
		else {
			result.push_back(c);
		}
	}
	result.push_back(' ');

	while (!st.empty()) {
		result.push_back(st.top());
		st.pop();
	}
	result.push_back('\n');
	return result;
}