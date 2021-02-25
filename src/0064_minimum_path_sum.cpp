/*************************************************************************************************
 *
 * 64. Minimum Path Sum
 * Given a m x n matrix filled with non-negative integers, find a path from the top-left to the
 * bottom right corner that minimizes the sum of the numbers on the path and return the sum.
 *
 * Runtime: 92.47%, memory usage: 51.42%
 *
 ************************************************************************************************/

#include <iostream>
#include <vector>
#include "util.h"

class Solution {
public:
    int minPathSum(std::vector<std::vector<int>> const& M) const
    {
        std::vector<std::vector<int>> dp(M.size(), std::vector<int>(M[0].size(), 0));
        dp[0][0] = M[0][0];
        for (size_t i = 1; i < M.size(); ++i) {
            dp[i][0] = dp[i-1][0] + M[i][0];
        }
        for (size_t j = 1; j < M[0].size(); ++j) {
            dp[0][j] = dp[0][j-1] + M[0][j];
        }
        for (size_t i = 1; i < M.size(); ++i) {
            for (size_t j = 1; j < M[0].size(); ++j) {
                dp[i][j] = std::min(dp[i-1][j], dp[i][j-1]) + M[i][j];
            }
        }
        return dp.back().back();
    }
};


void test(const std::vector<std::vector<int>> M)
{
    static const Solution instance;
    int res = instance.minPathSum(M);
    std::cout << M << " -> " << res << std::endl;
}


int main()
{
    test({ {1,3,1}, {1,5,1}, {4,2,1} });
    test({ {1,2,3}, {4,5,6} });
    test({ {1} });
    return 0;
}
