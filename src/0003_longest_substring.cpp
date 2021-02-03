/*************************************************************************************************
 *
 * 3. Longest Substring Without Repeating Characters
 *
 * Given a string, find the length of the longest substring without repeating characters.
 *
 * Faster than 100% (well... too fast to measure), less memory than 81% of C++ solutions.
 *
 ************************************************************************************************/

#include <climits>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.size() < 2) return s.size();

        vector<int> last(CHAR_MAX + 1, -1);
        int max = 0;

        char c;
        for (int start = 0, cur = 0; cur < s.size(); ++cur) {
            c = s.at(cur);
            if (last.at(c) >= start) {
                start = last.at(c) + 1;
            } else {
                if (max < cur - start) max = cur - start;
            }
            last.at(c) = cur;
        }

        return max + 1;
    }
};


int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "USAGE: subs <string>" << endl;
        return -1;
    }

    cout << Solution().lengthOfLongestSubstring(argv[1]) << endl;
    return 0;
}
