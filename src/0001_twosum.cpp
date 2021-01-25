/*************************************************************************************************
 *
 * 1. Two Sum
 * Given an array of integers `nums` and an integer `target`, return indices of two numbers in
 * `nums` such that they add up to `target`. (Assume exactly one solution exists.)
 *
 * Simple nested for-loops. Faster than 82.75% and using less memory than 95.13% of C++ solutions.
 *
 ************************************************************************************************/

#include <exception>
#include <iostream>
#include <vector>

using namespace std;

vector<int> two_sum(vector<int>& nums, int target)
{
    for (int i = 0; i < nums.size(); ++i) {
        for (int j = i+1; j < nums.size(); ++j) {
            if (nums[i] + nums[j] == target) return { i, j };
        }
    }
    throw domain_error("no solution");
}


/* The rest is testing stuff. */

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& V)
{
    os << '[';
    if (!V.empty()) {
        for (typename vector<T>::size_type i = 0; i < V.size() - 1; ++i) {
            os << V[i] << ',';
        }
        os << V.back();
    }
    return os << ']';
}

int main(void)
{
    vector<int> nums { 3,3 };
    int target = 6;
    cout << two_sum(nums, target) << endl;
    return 0;
}
