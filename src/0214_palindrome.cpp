/*************************************************************************************************
 *
 * 214. Shortest Palindrome (Hard)
 *
 * Given a string s, you can convert it to a palindrome by adding characters in front of it. Find
 * and return the shortest palindrome you can find by performing this transformation.
 *
 * We are looking for the longest leading substring of s that is a palindrome. Brute force is
 * deemed too slow. This solution is faster than 89% and uses less memory than 65% of C++
 * submissions on leetcode (yay):
 *
 * Traverse the string once to build an array of accumulated sums such that sum[i] = s[0] + s[1] +
 * ... + s[i]. If s[0:i+1] is a palindrome, then, roughly speaking, sum[i] must be twice as large
 * as sum[i/2]. If the condidition is met, push i onto a stack. Then check each i on the stack
 * until s[0:i+1] is indeed a palindrome.
 *
 ************************************************************************************************/

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    string shortestPalindrome(string s)
    {
        if (s.empty()) return s;

        int i, j, k;
        vector<int> sum(s.size());
        stack<int> candidates;
        sum[0] = s[0];
        candidates.push(0);

        for (i = 1; i < s.size(); ++i) {
            sum[i] = sum[i-1] + s[i];
            if (i & 1) {
                if (sum[i] == 2 * sum[i/2]) candidates.push(i);
            } else {
                if (sum[i] - s[i/2] == 2 * sum[i/2 - 1]) candidates.push(i);
            }
        }

        while (!candidates.empty()) {
            i = candidates.top(); candidates.pop();
            j = 0;
            k = i;
            while (j < k - 1 && s[j] == s[k]) { ++j; --k; }
            if (j == k || k - j == 1) break;
        }

        string p;
        for (k = s.size() - 1; k > i; --k) p.push_back(s[k]);
        p += s;
        return p;
    }
};

int main()
{
    Solution instance;
    string word;
    while (cin >> word) {
        cout << instance.shortestPalindrome(word) << endl;
    }
    return 0;
}
