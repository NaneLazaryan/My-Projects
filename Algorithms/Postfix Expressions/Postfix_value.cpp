#include <iostream>
#include "parser.h"
#include <cmath>

double toNum(const std::string& str)
{
	double number = 0;

	for (char c : str) {
		int digit = c - '0';
		number = number * 10 + digit;
	}

	return number;
}

double exprValue(const std::string& expr)
{
	linkedStack<double> st;
	std::string digit;
	
	for (char c : expr) {
		if (std::isalpha(c)) 
			throw std::invalid_argument("Character not allowed for value.");

		if (!isOperator(c)) {
			if (std::isspace(c)) {
				if (!digit.empty()) {
					st.push(toNum(digit));
					digit.clear();
				}
				continue;
			}
			digit.push_back(c);
		}
		else {
			Operator op = toOperator(c);
			double operand1 = 0, operand2 = 0;

			if (!st.empty()) {
				operand2 = st.top();
				st.pop();
			}
			if (!st.empty()) {
				operand1 = st.top();
				st.pop();
			}

			switch (op)
			{
			case Operator::Add:
				st.push(operand1 + operand2);
				break;
			case Operator::Subtract:
				st.push(operand1 - operand2);
				break;
			case Operator::Multiply:
				st.push(operand1 * operand2);
				break;
			case Operator::Divide:
				st.push(operand1 / operand2);
				break;
			case Operator::Power:
				st.push(std::pow(operand1, operand2));
				break;
			}
		}		
	}

	if (st.empty()) throw "Invalid Expression!";
	return st.top();
}

int main()
{
	std::string input;

	do {
		std::cout << "input: ";
		std::getline(std::cin, input);
	} while (!isValid(input));

	std::string expr = toPostfix(input);
	std::cout << expr << std::endl;

	try {
		std::cout << "Postfix expression value: " << exprValue(expr) << std::endl;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	catch (...) {
		std::cout << "Invalid Expression!" << std::endl;
	}
	return 0;
}
