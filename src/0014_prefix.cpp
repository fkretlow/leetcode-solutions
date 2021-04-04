/*************************************************************************************************
 *
 * 14. Longest Common Prefix
 * Given an array of strings, return the longest common prefix of all the strings in the array.
 *
 * Runtime: "100%", memory usage: 86.05%.
 *
 ************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    std::string longestCommonPrefix(const std::vector<std::string> &strings) const
    {
        if (strings.empty()) return "";
        for (std::string::size_type i = 0;; ++i)
        {
            if (i >= strings.front().size()) {
                return strings.front();
            }
            char c = strings.front().at(i);
            for (auto it = ++strings.cbegin(); it != strings.cend(); ++it)
            {
                if (i >= it->size() || it->at(i) != c) {
                    return strings.front().substr(0, i);
                }
            }
        }
    }
};


void test(std::vector<std::string> strings)
{
    static const Solution instance;
    for (const auto &s : strings) {
        std::cout << s << ' ';
    }
    std::cout << "-> " << instance.longestCommonPrefix(strings) << std::endl;
}

int main(void)
{
    test({"flower", "flow", "flight"});
    test({"dog", "racecar", "car"});
    test({});
}
