/*************************************************************************************************
 *
 * 55. Jump Game
 *
 * You are given an array of non-negative numbers, where each number represents your maximum jump
 * length at that position. Starting at the first index, determine if you are able to reach the
 * last index.
 * O(n), Runtime: 93.24%, memory usage: 96.39%.
 *
 ************************************************************************************************/

#include <iomanip>
#include <iostream>
#include <vector>
#include "util.h"

class Solution {
public:
    bool canJump(const std::vector<int> &V) const
    {
        if (V.size() == 1) return true;

        size_t i = 0;
        size_t next = 0;
        size_t max = 0;
        while (i < V.size()) {
            for (size_t j = i+1; j <= i + V.at(i); ++j) {
                if (j + V.at(j) > max) {
                    max = j + V.at(j);
                    if (max >= V.size()-1) return true;
                    next = j;
                }
            }
            if (next > i)   i = next;
            else            break;
        }
        return false;
    }
};


void test(const std::vector<int> &&V)
{
    static const Solution instance;
    std::cout << V << " -> " << std::boolalpha << instance.canJump(V) << std::endl;
}

int main()
{
    test({ 2,3,1,1,4 });
    test({ 3,2,1,0,4 });
    test({ 0 });
    return 0;
}
