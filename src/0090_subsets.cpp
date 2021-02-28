/*************************************************************************************************
 *
 * 90. Subsets II
 * Given an array of non-unique integers, return all possible subsets.
 *
 ************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include "util.h"


class Solution {
public:
    std::vector<std::vector<int>> operator()(const std::vector<int>& V)
    {
        return subsets(V);
    }
    std::vector<std::vector<int>> subsets(const std::vector<int>& V)
    {
        solution.clear();
        solve__r(V, {}, 0);
        return std::vector<std::vector<int>>(solution.begin(), solution.end());
    }
private:
    std::set<std::vector<int>> solution;
    void solve__r(const std::vector<int>& V, std::vector<int> subset, size_t i)
    {
        if (i == V.size()) {
            solution.insert(subset);
            return;
        }

        solve__r(V, subset, i+1);
        subset.push_back(V[i]);
        sort(subset.begin(), subset.end());
        solve__r(V, subset, i+1);
    }
};


void test(std::vector<int>&& V)
{
    static Solution generateSubsets;
    std::vector<std::vector<int>> subsets = generateSubsets(V);
    std::cout << V << std::endl
              << subsets << std::endl;
}

int main()
{
    test({4,4,4,1,4});
    test({1,2,2});
    test({1,2});
    test({1});
    test({});
    return 0;
}
