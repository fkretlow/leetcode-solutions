/*************************************************************************************************
 *
 * 74. Search a 2D Matrix
 *
 * Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the
 * following properties:
 * - Integers in each row are sorted from left to right.
 * - The first integer in each row is greater than the last integer of the previous row.
 *
 * Faster than 100%, less memory than 50.61% of C++ submissions.
 *
 ************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
#include "util.h"

class Solution {
    public:
        bool searchMatrix(const std::vector<std::vector<int>>& M, const int x) const
        {
            if (M.empty() || M.at(0).at(0) > x) return false;

            std::vector<std::vector<int>>::size_type lo, hi, m;
            lo = 0;
            hi = M.size()-1;

            while (lo <= hi)
            {
                m = (lo + hi) / 2;
                if      ((m < M.size()-1 && M.at(m).at(0) <= x && M.at(m+1).at(0) > x)
                         || (m == M.size()-1 && M.at(m).at(0) <= x))    break;
                else if (M.at(m).at(0) > x)                             hi = m - 1;
                else if (M.at(m).at(0) < x)                             lo = m + 1;
            }

            auto row = M.at(m);
            auto pos = std::equal_range(row.begin(), row.end(), x);
            return pos.first != pos.second;
        }
};


int main(void)
{
    std::vector<std::vector<int>> M = { {1,3,5,7}, {10,11,16,20}, {23,30,34,60} };
    std::cout << std::boolalpha
              << Solution().searchMatrix(M, 20) << std::endl;
}
