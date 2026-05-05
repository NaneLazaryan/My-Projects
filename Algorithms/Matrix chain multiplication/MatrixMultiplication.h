#pragma once

#include <vector>
#include <string>

namespace tabular
{
	std::string printOptimalParens(std::vector<std::vector<int>>& index, int i, int j)
	{
		if (i == j)
			return "A" + std::to_string(i + 1);
		else {

			return "(" + printOptimalParens(index, i, index[i][j]) + " x " + printOptimalParens(index, index[i][j] + 1, j) + ")";
		}
	}

	int MatrixChainOrder(std::vector<int>& dims)
	{
		size_t n = dims.size() - 1;
		std::vector<std::vector<int>> costs(n, std::vector<int>(n, 0));
		std::vector<std::vector<int>> index(n, std::vector<int>(n, 0));
		
		for (int l = 2; l <= n; l++) {  // chain length
			for (int i = 0; i < n - l + 1; i++) {
				int j = i + l - 1;
				costs[i][j] = INT_MAX;
				for (int k = i; k < j; k++) {
					int cost = costs[i][k] + costs[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
					if (cost < costs[i][j]) {
						costs[i][j] = cost;
						index[i][j] = k;
					}
				}
			}
		}

		std::cout << "Optimal parentheziation: " << printOptimalParens(index, 0, n - 1);
		return costs[0][n - 1];
	}
}

namespace memoization
{
	int MatrixChainOrder(std::vector<int>& dims, std::vector<std::vector<int>>& memo, int i, int j)
	{
		if (i == j) return 0;
		if (memo[i][j] != INT_MAX) return memo[i][j];

		for (int k = i; k < j; k++) {
			int res = MatrixChainOrder(dims, memo, i, k) + MatrixChainOrder(dims, memo, k + 1, j) + dims[i] * dims[k + 1] * dims[j + 1];
			memo[i][j] = std::min(res, memo[i][j]);
		}
		
		return memo[i][j];
	}

	int MatrixMultiplication(std::vector<int>& dims)
	{
		size_t n = dims.size() - 1;
		std::vector<std::vector<int>> memo(n, std::vector<int>(n, INT_MAX));
		return MatrixChainOrder(dims, memo, 0, n - 1);
	}

}
