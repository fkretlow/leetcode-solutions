/*************************************************************************************************
 *
 * 15. 3-sum
 *
 * Given an array of integers, return all possible unique sub-arrays of three integers that sum up
 * to 0.
 *
 * (My original submission was accepted, but this more elegant (and faster) one is not entirely my
 * own, but inspired by someone else's solution.)
 *
 ************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> three_sum(vector<int> nums) // by value only for testing (literal arrays)
{
    if (nums.size() < 3) return { };

    sort(nums.begin(), nums.end());
    vector<vector<int>> triplets;

    vector<int>::size_type i, j, k;
    for (i = 0; i < nums.size() - 2; ++i) {
        if (nums[i] > 0)                    break;
        if (i > 0 && nums[i] == nums[i-1])  continue;
        j = i + 1;
        k = nums.size() - 1;
        while (j < k) {
            if (nums[j] + nums[k] == -nums[i]) {
                vector<int> t { nums[i], nums[j], nums[k] };
                triplets.push_back(t);
                while (j < k && nums[j] == t[1]) ++j;
                while (j < k && nums[k] == t[2]) --k;
            }
            else if (nums[j] + nums[k] < -nums[i]) ++j;
            else                                   --k;
        }
    }

    return triplets;
}

/* For testing... */

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

int main()
{
    const auto triplets = three_sum({ -5,3,2,7,-1,-1,-1,3,4,0,-2 });
    for (const auto& t : triplets) cout << t << endl;

    return 0;
}
