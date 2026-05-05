#pragma once

#include <string>
#include <vector>

// Bottom-up
namespace tabular
{
	int LongestCommonSubseq(const std::string& str1, const std::string& str2)
	{
		size_t m = str1.size();
		size_t n = str2.size();
		std::vector<std::vector<int>> memo(m + 1, std::vector<int>(n + 1, 0));

		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++) {
				if (str1[i - 1] == str2[j - 1]) {
					memo[i][j] = memo[i - 1][j - 1] + 1;
				}
				else {
					memo[i][j] = std::max(memo[i - 1][j], memo[i][j - 1]);
				}
			}

		return memo[m][n];
	}
}

// Top-down
namespace memoization
{
	int CommonSubseqHelper(const std::string& str1, const std::string& str2, std::vector<std::vector<int>>& memo, size_t i, size_t j) 
	{
		if (i == 0 || j == 0) return 0;

		if (memo[i][j] != -1) return memo[i][j];

		if (str1[i - 1] == str2[j - 1])
			memo[i][j] = CommonSubseqHelper(str1, str2, memo, i - 1, j - 1) + 1;
		else
			memo[i][j] = std::max(CommonSubseqHelper(str1, str2, memo, i - 1, j), CommonSubseqHelper(str1, str2, memo, i, j - 1));

		return memo[i][j];
	}

	int LongestCommonSubseq(const std::string& str1, const std::string& str2)
	{
		size_t m = str1.size();
		size_t n = str2.size();
		std::vector<std::vector<int>> memo(m + 1, std::vector<int>(n + 1, -1));

		return CommonSubseqHelper(str1, str2, memo, m, n);
	}
}