/************************************************************************************************
 *
 * 676. Magic Dictionary
 *
 * Design a data structure that is initialized with a list of different words. Given a string,
 * determine if you can change exactly one character in this string to match any word in the
 * dictionary.
 *
 * Array of strings sorted by length. Test only strings with equal length.
 * Initialization: O(n log n), search: O(n*m), where m is query.length.
 * Faster than 98.27%, less memory than 98.27% (sic) of C++ submissions.
 *
 ***********************************************************************************************/

#include <algorithm>
#include <iostream>
#include <set>
#include <string>

using namespace std;

class MagicDictionary {
public:
    MagicDictionary() = default;
    MagicDictionary(const vector<string>& dictionary) { buildDict(dictionary); }
    void buildDict(const vector<string>& dictionary);
    bool search(const string& query) const;
private:
    vector<string> data;
    static bool compareStringSize(const string& a, const string& b) { return a.size() < b.size(); }
};

void MagicDictionary::buildDict(const vector<string>& dictionary)
{
    data = dictionary;
    sort(data.begin(), data.end(), compareStringSize);
}

bool MagicDictionary::search(const string& query) const
{
    auto range = equal_range(data.begin(), data.end(), query, compareStringSize);
    for (auto word = range.first; word != range.second; ++word) {
        int changes = 0;
        auto i = word->begin();
        auto j = query.begin();
        while (i != word->end() && changes <= 1) {
            if (*i++ != *j++) ++changes;
        }
        if (changes == 1) return true;
    }
    return false;
}


int main(void)
{
    vector<string> words { "hello", "leetcode" };
    MagicDictionary dict { words };

    cout << boolalpha;
    cout << "search \"hello\": "      << dict.search("hello")      << endl;
    cout << "search \"hhllo\": "      << dict.search("hhllo")      << endl;
    cout << "search \"hell\": "       << dict.search("hell")       << endl;
    cout << "search \"leetcoded\": "  << dict.search("leetcoded")  << endl;
    cout << "search \"leetcore\": "   << dict.search("leetcore")   << endl;

    return 0;
}
