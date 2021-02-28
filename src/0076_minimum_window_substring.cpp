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
    std::string minWindow(const std::string& s, const std::string& t)
    {
        std::map<char, short unsigned> charsFound;
        for (const char& c : t) {
            charsFound[c] = 0;
        }

        short unsigned start = 0, end = 0, len = 0, count = 0;
        for (short unsigned i = 0, j = 0; j < s.size(); ++j) {
            if (charsFound.find(s[j]) != charsFound.end()) {
                if (charsFound[s[j]] == 0) {
                    ++count;
                    if (count == charsFound.size()) {
                        start = i;
                        end = j+1;
                        len = end - start;
                    }
                }
                ++charsFound[s[j]];
            }

            while (i < j) {
                if (charsFound.find(s[i]) == charsFound.end()) {
                    ++i;
                } else if (charsFound[s[i]] > 1) {
                    --charsFound[s[i]];
                    ++i;
                } else { /* charsFound[s[i]] == 1 */
                    if (count == charsFound.size() && j+1 - i < len) {
                        start = i;
                        end = j+1;
                        len = end - start;
                    }
                    break;
                }
            }
        }
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
    if (argc >= 3) {
        test(argv[1], argv[2]);
    } else {
        test("ADOBECODEBANC", "ABC");
        test("A", "A");
        test("ABC", "D");
    }
    return 0;
}
