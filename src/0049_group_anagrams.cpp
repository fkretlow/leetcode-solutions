/*************************************************************************************************
 *
 * 49. Group Anagrams
 * Given an array of strings, group the anagrams together. An anagram is a permutation of the
 * letters of another string.
 *
 * Runtime: 88.61%, memory usage: 69.83%
 *
 ************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include "util.h"

class Solution {
public:
    std::vector<std::vector<std::string>>
    groupAnagrams(std::vector<std::string> const& words) const noexcept
    {
        std::unordered_map<std::string, std::vector<short unsigned>> M;
        for (short unsigned i = 0; i < words.size(); ++i) {
            std::string w = words.at(i);
            std::sort(w.begin(), w.end());
            M[w].push_back(i);
        }
        std::vector<std::vector<std::string>> anagrams;
        for (std::pair<std::string, std::vector<short unsigned>> const& p : M) {
            anagrams.emplace_back();
            for (short unsigned const& i : p.second) {
                anagrams.back().push_back(words.at(i));
            }
        }
        return anagrams;
    }
};

void test(const std::vector<std::string> words)
{
    static const Solution instance;
    std::cout << words << " -> "
              << instance.groupAnagrams(words)
              << std::endl;
}

int main()
{
    test({ "" });
    test({ "a" });
    test({ "eat", "tea", "tan", "ate", "nat", "bat" });
    return 0;
}
