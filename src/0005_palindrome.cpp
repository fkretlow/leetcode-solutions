#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s)
    {
        string max;
        string::size_type i, j, k;
        for (i = 0; i < s.size(); ++i) {
            if (s.size() - i <= max.size() / 2) break;

            j = k = i;
            while (j > 0 && k < s.size() - 1 && s[j-1] == s[k+1]) { --j; ++k; }
            if (k - j >= max.size()) max = s.substr(j, k - j + 1);

            j = k = i;
            if (k < s.size() - 1 && s[j] == s[j+1]) ++k;
            while (j > 0 && k < s.size() - 1 && s[j-1] == s[k+1]) { --j; ++k; }
            if (k - j >= max.size()) max = s.substr(j, k - j + 1);
        }
        return max;
    }
};

int main()
{
    Solution instance;
    string word;
    while (cin >> word) {
        cout << instance.longestPalindrome(word) << endl;
    }
    return 0;
}
