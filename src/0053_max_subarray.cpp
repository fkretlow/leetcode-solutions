#include <climits>
#include <iostream>
#include <vector>
#include "util.h"

class Solution {
public:
    int maxSubArray(const std::vector<int>& A) const
    {
        int max = A[0];
        int cur = A[0];
        size_t maxr = 1;

        for (size_t i = 1; i < A.size(); ++i) {
            cur += A[i];
            // std::cout << "cur=" << cur << std::endl;
            if (cur > max) {
                max = cur;
                maxr = i+1;
                // std::cout << "cur > max; new max=" << max << std::endl;
            }
        }
        // std::cout << "maxr=" << maxr << std::endl;
        cur = max;
        for (size_t i = 0; i < maxr-1; ++i) {
            cur -= A[i];
            // std::cout << "cur=" << cur << std::endl;
            if (cur > max) {
                max = cur;
            }
        }

        return max;
    }
};

void test(const std::vector<int> &&A)
{
    static const Solution instance;
    int res = instance.maxSubArray(A);
    std::cout << A << " -> " << res << std::endl;
}

int main()
{
    test({ -2,1,-3,4,-1,2,1,-5,4 });
    test({ 1 });
    test({ 5,4,-1,7,8 });
    test({ 1,-1,-1,-1,-1,-1,-1 });
    test({ 1,-1,-1,-1,-1,-1,-1,20 });
    test({ -1 });
    test({ -2,1 });
    test({ -2,-1 });
    return 0;
}
