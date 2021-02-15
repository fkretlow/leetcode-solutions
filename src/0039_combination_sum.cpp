/*************************************************************************************************
 *
 * 39. Combination Sum
 *
 * I got runtime results between 50% and 100% for this exact same solution. That's a little sad,
 * it seems the results are pretty random.
 *
 ************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
#include "tests.h"

class Solution {
public:
    std::vector<std::vector<int>> combinationSum(const std::vector<int> V, const int x)
    {
        solve_r(V, V.cbegin(), x);
        return solutions;
    }
private:
    std::vector<std::vector<int>> solutions;
    std::vector<int> cur;
    void solve_r(const std::vector<int> &V, std::vector<int>::const_iterator it, const int rem)
    {
        if (rem == 0)       { solutions.push_back(cur); return; }
        if (it == V.end())  return;

        solve_r(V, it+1, rem);

        int k, v;
        for (k = 1, v = *it; v <= rem; ++k, v += *it)
        {
            cur.push_back(*it);
            solve_r(V, it+1, rem - v);
        }
        for (int i = 0; i < k-1; ++i) cur.pop_back();
    }
};

void test(const std::vector<int> candidates, const int target)
{
    std::cout << "candidates = " << candidates
        << ", target = " << target
        << " -> result = " << Solution().combinationSum(candidates, target) << std::endl;
}

int main(void)
{
    test({ 2,3,6,7 }, 7);
    test({ 2,3,5 }, 8);
    test({ 2 }, 1);
    test({ 1 }, 1);
    test({ 1 }, 2);
    return 0;
}
