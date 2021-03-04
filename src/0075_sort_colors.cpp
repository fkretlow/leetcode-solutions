/*************************************************************************************************
 *
 * 75. Sort Colors
 * Given an array with n objects colored red, white, or blue, sort them in-place so that objects
 * of the same color are adjacent, with the colors in the order red, white, and blue. We will use
 * the integers 0, 1, and 2 to represent the colors.
 *
 * Since there are only 3 distinct values, we can do this with a single pass and at most two swaps
 * for each position if we keep track of the start indices of the equal ranges in the array.  That
 * gives time O(n) and space O(1), significantly faster than O(n log n) for a full-fledged sorting
 * algorithms.
 *
 * Runtime: "100%", memory usage: 99.76%
 *
 ************************************************************************************************/

#include <exception>
#include <iostream>
#include <vector>
#include "util.h"

/* Log a format string to stdout: log("... %1 ... %2 ... %3 ...", a, b, c, ...) */
template <typename ... Args>
void log(const std::string& fmt, const Args& ... args)
{
    std::cout << "LOG   ";
    std::string::size_type i = 0;
    auto printFmt = [&fmt, &i]()
    {
        while (i < fmt.size()) {
            if (fmt.at(i) == '%') {
                ++i;
                if      (fmt.at(i) == '%')      { ++i; std::cout << '%'; }
                else if (isdigit(fmt.at(i)))    { ++i; break; }
                else throw std::runtime_error("invalid format string");
            }
            else std::cout << fmt.at(i++);
        }
    };
    ((printFmt(), std::cout << args), ..., (std::cout << fmt.substr(i) << std::endl));
}

class Solution {
public:
    void sortColors(std::vector<int>& A) const
    {
        int start[] { -1, -1, -1 };
        for (int i = 0; static_cast<size_t>(i) < A.size(); ++i) {
            log("i=%1, before: %2, start indices [%3,%4,%5]", i, A, start[0], start[1], start[2]);
            switch (A[i]) {
                case 0:
                    if (start[1] > -1) {
                        std::swap(A[start[1]], A[i]);
                        if (start[0] == -1) start[0] = start[1];
                        ++start[1];
                        if (start[2] > -1) {
                            std::swap(A[start[2]], A[i]);
                            ++start[2];
                        }
                    } else if (start[2] > -1) {
                        std::swap(A[start[2]], A[i]);
                        if (start[0] == -1) start[0] = start[2];
                        ++start[2];
                    } else if (start[0] == -1) {
                        start[0] = i;
                    }
                    break;
                case 1:
                    if (start[2] > -1) {
                        std::swap(A[start[2]], A[i]);
                        if (start[1] == -1) start[1] = start[2];
                        ++start[2];
                    } else if (start[1] == -1) {
                        start[1] = i;
                    }
                    break;
                default:
                    if (start[2] == -1) start[2] = i;
                    break;
            }
            log("i=%1, after:  %2, start indices [%3,%4,%5]", i, A, start[0], start[1], start[2]);
            if (start[1] > -1) {
                if (A[start[1]] != 1 || (start[1] > 0 && A[start[1]-1] != 0)) {
                    throw std::logic_error("start[1] corrupted");
                }
            }
            if (start[2] > -1) {
                if (A[start[2]] != 2 || (start[2] > 0 && A[start[2]-1] == 2)) {
                    throw std::logic_error("start[2] corrupted");
                }
            }
        }
    }
};

void test(std::vector<int>&& A)
{
    static const Solution instance;
    std::cout << A << std::endl;
    instance.sortColors(A);
    std::cout << A << std::endl;
}

int main()
{
    test({ 2,0,2,1,1,0 });
    test({ 1 });
    test({ 0,1,2 });
    test({ });
    test({ 2,1,0 });
    test({ 2,0 });
    return 0;
}
