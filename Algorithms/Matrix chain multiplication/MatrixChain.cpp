
#include <iostream>
#include "MatrixMultiplication.h"


int main()
{
    std::vector<int> arr = { 2, 1, 3, 4 }; //{ 2, 3, 4, 2, 2 };
    std::cout << "\n[Tabular] Minimum multiplication = " << tabular::MatrixChainOrder(arr) << std::endl;
    std::cout << "[Memoization] Minimum multiplication = " << memoization::MatrixMultiplication(arr) << std::endl;
    return 0;
}
