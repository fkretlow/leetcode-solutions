/*************************************************************************************************
 *
 * 33. Search in Rotated Sorted Array
 * Given a rotated sorted array, return the index of an integer x in the array or -1 if it
 * doesn't exist.
 *
 * Faster than 82.45%, less memory than 57.93% of C++ submissions.
 *
 ************************************************************************************************/

#include <exception>
#include <iostream>
#include <vector>

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
    ((printFmt(), std::cout << args), ..., (std::cout << std::endl));
}

class Solution {
public:
    int search(const std::vector<int>& A, const int x) const
    {
        if (A.size() == 1) return A.at(0) == x ? 0 : -1;

        int p, lo, hi, m;
        p = findPivot(A);
        if      (p == 0)        { lo = 0; hi = A.size()-1; }
        else if (x > A.at(0))   { lo = 0; hi = p-1; }
        else if (x < A.at(0))   { lo = p; hi = A.size()-1; }
        else /* x == A[0] */    return 0;

        while (lo <= hi) {
            m = (lo + hi) / 2;
            if      (A.at(m) == x)      return m;
            else if (A.at(m) < x)       lo = m + 1;
            else                        hi = m - 1;
        }

        return -1;
    }
private:
    int findPivot(const std::vector<int>& A) const
    {
        if (A.at(0) < A.back()) return 0;
        int lo, hi, m;
        lo = 0; hi = A.size()-1;
        while (lo <= hi) {
            m = (lo + hi) / 2;
            if      (m == 0 && A.at(0) > A.at(1))   return 1;
            else if (A.at(m) < A.at(m-1))           return m;
            else if (A.at(m) > A.at(0))             lo = m + 1;
            else if (A.at(m) < A.at(0))             hi = m - 1;
            else throw std::invalid_argument("bad array");
        }
        return -1;
    }
};


int main(void)
{
    const Solution instance;
    std::vector<int> nums { 4,5,6,7,0,1,2,3 };
    // std::vector<int> nums { 4,5,6,7,0,1,2 };
    // std::vector<int> nums { 1 }
    // std::vector<int> nums { 3,1,2 };
    std::cout << instance.search(nums, -12) << std::endl;
    return 0;
}
