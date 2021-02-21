/*************************************************************************************************
 *
 * 56. Merge Intervals
 * Given an array of intervals, merge all overlapping intervals and return an array of the
 * non-overlapping intervals that cover all the intervals in the array.
 *
 * Sort and traverse.
 * Runtime: 80.38%, memory usage: 67.96%
 *
 ************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include "util.h"

class Solution {
public:
    std::vector<std::vector<int>> merge(std::vector<std::vector<int>> const& intervals) const
    {
        std::vector<int> sorted(intervals.size());
        std::iota(sorted.begin(), sorted.end(), 0);
        std::sort(sorted.begin(), sorted.end(),
                [&intervals](int const& i, int const& j)
                {
                    if (intervals.at(i)[0] < intervals.at(j)[0]) {
                        return true;
                    } else if (intervals.at(i)[0] == intervals.at(j)[0]) {
                        return (intervals.at(i)[1] < intervals.at(j)[1]);
                    }
                    return false;
                });

        std::vector<std::vector<int>> merged { intervals.at(sorted.front()) };
        for (size_t i = 1; i < sorted.size(); ++i) {
            int j = sorted.at(i);
            if (intervals.at(j)[0] <= merged.back()[1]) {
                merged.back()[1] = std::max(merged.back()[1], intervals[j][1]);
            } else {
                merged.push_back(intervals.at(j));
            }
        }
        return merged;
    }
};

void test(const std::vector<std::vector<int>> intervals)
{
    const static Solution instance;
    std::cout << intervals
              << " -> "
              << instance.merge(intervals)
              << std::endl;
}

int main()
{
    test({ {1,4}, {0,0} });
    test({ {1,3}, {8,10}, {2,6}, {15,18} });
    test({ {1,2}, {1,3}, {1,4} });
    test({ {1,8}, {2,3}, {3,4} });
    test({ {1,4}, {4,5} });
    test({ {1,2} });
    return 0;
}
