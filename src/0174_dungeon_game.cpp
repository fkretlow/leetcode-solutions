/*************************************************************************************************
 *
 * 174. Dungeon Game
 * Runtime: 79.76%, Memory usage: 46.12%
 *
 ************************************************************************************************/

#include <climits>
#include <iostream>
#include <vector>
#include "util.h"

class Solution {
public:
    int calculateMinimumHP(std::vector<std::vector<int>> const& dungeon)
    {
        M = &dungeon;
        m = dungeon.size();
        n = dungeon[0].size();
        dp.clear();
        dp.insert(dp.begin(), m, std::vector<int>(n, 0));
        return calculate(0, 0);
    }
private:
    std::vector<std::vector<int>> dp;
    const std::vector<std::vector<int>> *M;
    unsigned m, n;
    int calculate(const unsigned i, const unsigned j)
    {
        if (dp[i][j] == 0) {
            if (i == m-1 && j == n-1) dp[i][j] = (*M)[i][j] > 0 ? 1 : -(*M)[i][j] + 1;
            else if (i == m-1) dp[i][j] = std::max(1, calculate(i, j+1) - (*M)[i][j]);
            else if (j == n-1) dp[i][j] = std::max(1, calculate(i+1, j) - (*M)[i][j]);
            else dp[i][j] = std::max(1, std::min(calculate(i, j+1), calculate(i+1, j)) - (*M)[i][j]);
        }
        return dp[i][j];
    }
};

void test(const std::vector<std::vector<int>> dungeon)
{
    static Solution instance;
    std::cout << dungeon << " -> " << instance.calculateMinimumHP(dungeon) << std::endl;
}

int main()
{
    test({ {-2,-3,3}, {-5,-10,1}, {10,30,-5} });
    test({ {-2} });
    test({ {-1,1}, {2,-2} });
    return 0;
}
