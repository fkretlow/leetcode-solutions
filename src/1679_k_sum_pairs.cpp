/*************************************************************************************************
 *
 * 1679. Maximum number of k-sum pairs
 *
 * You are given an integer array `nums` and an integer `k`. In one operation you can pick two
 * numbers from the array whose sum equals `k` and remove them from the array. Return the maximum
 * number of operations you can perform on the array.
 *
 * Sort and traverse from both ends. Faster than 93.53%, less memory than 78% of C++ submissions.
 *
 ************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int max_operations(vector<int>& nums, int k)
{
    if (nums.size() < 2) return 0;

    sort(nums.begin(), nums.end());
    vector<int>::size_type i = 0;
    vector<int>::size_type j = nums.size() - 1;
    int count = 0;

    while (i < j) {
        while (i < j && nums[j] > k - nums[i])  --j;
        if (i == j)                             break;
        if (nums[i] + nums[j] == k)             { --j; ++count; }
        ++i;
    }

    return count;
}

int main()
{
    vector<int> nums { 0,1,2,3,3,4,5,5,6,8,10,11 };
    int k = 11;
    cout << max_operations(nums, k) << endl;
    return 0;
}
