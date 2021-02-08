#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/* class Solution {
 * public:
 *     int maxArea(vector<int> h)
 *     {
 *         vector<int>::size_type l, r, i, j;
 *         int max, cur, hl;
 *
 *         l = 0; hl = 0; max = 0;
 *         r = h.size() - 1;
 *
 *         for (i = 0; i < r; ++i) {
 *             if (h.at(i) > hl) {
 *                 cur = (r-i) * min(h.at(i), h.at(r));
 *                 if (cur > max) { max = cur; l = i; hl = h.at(l); }
 *                 for (j = r-1; j > i; --j) {
 *                     if (h.at(j) > h.at(r)) {
 *                         cur = (j - i) * min(h.at(i), h.at(j));
 *                         if (cur > max) { max = cur; l = i; hl = h.at(l); r = j; }
 *                     }
 *                     if (h.at(j) >= h.at(i)) break;
 *                 }
 *             }
 *         }
 *
 *         return max;
 *     }
 * }; */

class Solution {
public:
    int maxArea(vector<int> height) {
        int rc = 0;
        int left = 0;
        int right = height.size() - 1;
        while(left < right)
        {
            rc = max(rc, (right - left) * min(height[left], height[right]));
            if(height[left] < height[right])
                left++;
            else
                right--;
        }
        return rc;
    }
};


int main(void)
{
    Solution instance;
    cout << instance.maxArea({ 1,8,6,2,5,4,8,3,7 }) << endl;
    cout << instance.maxArea({ 1,1 }) << endl;
    cout << instance.maxArea({ 4,3,2,1,4 }) << endl;
    cout << instance.maxArea({ 1,2,1 }) << endl;
    cout << instance.maxArea({ 1,2,3,4 }) << endl;
    cout << instance.maxArea({ 4,3,2,1 }) << endl;
    cout << instance.maxArea({ 1,1,2,1,2,1,1,1,1,1 }) << endl;
}
