/*************************************************************************************************
 *
 * 34. Find First and Last Position of Element in Sorted Array
 *
 * Given an array of integers sorted in ascending order, find the starting and edning position of
 * a given value. If it's not found, return [-1, -1].
 *
 * Simple binary search. Faster than 83.57%, less memory usage than 89.05% of C++ submissions.
 *
 ************************************************************************************************/

#include <iostream>
#include <vector>
#include "util.h"

class Solution
{
public:
    std::vector<int> searchRange(const std::vector<int> &A, const int x) const
    {
        if (A.size() == 0) return { -1, -1 };

        int lo, hi, m;
        lo = 0;
        hi = A.size()-1;
        m = 0;
        bool found = false;

        while (lo <= hi)
        {
            m = (lo + hi) / 2;
            if      (x == A.at(m))  { found = true; break; }
            else if (x < A.at(m))   hi = m - 1;
            else if (x > A.at(m))   lo = m + 1;
        }

        if (!found) return { -1, -1 };

        lo = hi = m;
        while (lo > 0                            && x == A.at(lo-1))    --lo;
        while (hi < static_cast<int>(A.size()-1) && x == A.at(hi+1))    ++hi;

        return { lo, hi };
    }
};

int main(void)
{
    std::vector<int> nums { 5,6,7,7,8,8,9,10 };
    std::cout << Solution().searchRange(nums, 3) << std::endl;
    return 0;
}
