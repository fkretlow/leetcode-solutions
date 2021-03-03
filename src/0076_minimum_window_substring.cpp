/*************************************************************************************************
 *
 * 76. Minimum Window Substring
 * Given to strings s and t, return the mimimum window in s which contains all the characters in
 * t or the empty string if there is no such window.
 *
 * This solution considers only unique characters in t, which is not what leetcode expects.
 *
 ************************************************************************************************/

#include <algorithm>
#include <climits>
#include <iostream>
#include <map>
#include <string>

std::ostream& operator<<(std::ostream& os, const std::map<char, short unsigned>& M)
{
    std::cout << '{';
    for (const auto& p : M) {
        std::cout << p.first << ":" << p.second << ",";
    }
    return std::cout << '}';
}

class Solution {
public:
    std::string operator()(const std::string& s, const std::string& t) { return minWindow(s, t); }
    std::string minWindow(const std::string& s, const std::string& t)
    {
        short chars[123] { SHRT_MIN }; // `z` == 122
        short charsCount = 0;
        for (const char& c : t) {
            if (chars[c] == SHRT_MIN) chars[c] = 0;
            ++chars[c];
            ++charsCount;
        }

        short unsigned start = 0, len = USHRT_MAX;
        for (short unsigned i = 0, j = 0; j < s.size(); ++j) {
            if (chars[s[j]] > 0)            --charsCount;
            if (chars[s[j]] != SHRT_MIN)   --chars[s[j]];

            while (i < j) {
                if (chars[s[i]] < 0) {
                    if (chars[s[i]] != SHRT_MIN)   ++chars[s[i]];
                    ++i;
                } else {
                    break;
                }
            }

            if (charsCount == 0 && j+1 - i < len) {
                start = i;
                len = j+1 - i;
            }
        }
        if (len == USHRT_MAX) len = 0;
        return s.substr(start, len);
    }
};


void test(const std::string s, const std::string t)
{
    static Solution instance;
    std::string res = instance.minWindow(s, t);
    std::cout << s << ", " << t << " -> " << res << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc >= 1 && std::string("-i") == argv[1]) {
        Solution minWindow;
        for ( ;; ) {
            std::string s, t;
            std::cin >> s;
            std::cin >> t;
            std::cout << "-> " << minWindow(s, t) << std::endl << std::endl;
        }

    } else {
        test("ADOBECODEBANC", "ABC");
        test("A", "A");
        test("ABC", "D");
    }
    return 0;
}
