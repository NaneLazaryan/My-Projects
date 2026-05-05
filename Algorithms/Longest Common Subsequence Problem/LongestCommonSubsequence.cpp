// LongestCommonSubsequence.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "LongestCommonSubsequence.h"

int main()
{
	std::cout << "--- Longest Common Subsequence Length ---" << std::endl;
	std::string s1 = "";
	std::string s2 = "";

	std::cout << "Enter first string: ";
	std::cin >> s1;
	std::cout << "Enter second string: ";
	std::cin >> s2;

	std::cout << "[Bottom-up]: " << tabular::LongestCommonSubseq(s1, s2) << std::endl;
	std::cout << "[Top-down]: " << memoization::LongestCommonSubseq(s1, s2) << std::endl;

	return 0;
}