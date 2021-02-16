/*************************************************************************************************
 *
 * 41. First Missing Positive
 *
 * Given an unsorted array of integers, find the smallest missing positive integer.
 *
 * The result can be at most max = |A| + 1. Traverse the array, push all integers in [0:max] onto
 * a priority queue, decrease max for every integer outside the range. Dequeue one by one and
 * report the first gap.
 *
 * Runtime: 100%, Memory Usage: 74.51%.
 *
 ************************************************************************************************/

#include <functional>
#include <iostream>
#include <queue>
#include <vector>
#include "tests.h"

class Solution {
public:
    int firstMissingPositive(const std::vector<int> &A)
    {
        int max = A.size() + 1;
        std::priority_queue<int, std::vector<int>, std::greater<int>> Q;
        for (const int &i : A) {
            if (i <= 0 || i > max)  --max;
            else                    Q.push(i);
        }
        int i = 0;
        while (!Q.empty()) {
            if (Q.top() > i + 1)    break;
            if (Q.top() == i + 1)   i = Q.top();
            Q.pop();
        }
        return i + 1;
    }
};

void test(const std::vector<int> V)
{
    std::cout << V
              << " -> " << Solution().firstMissingPositive(V)
              << std::endl;
}

int main(void)
{
    test({ 1,2,0 });
    test({ 3,4,-1,1 });
    test({ 7,8,9,11,12 });
    test({ });
    return 0;
}
