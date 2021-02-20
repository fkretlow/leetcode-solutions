/*************************************************************************************************
 *
 * 17. Letter Combinations of a Phone Number
 * Given a string containing digits from 2 to 9 inclusive, return all possible letter combinations
 * that the number could represent:  { 2: abc, 3: def, ..., 7: pqrs, 8: tuv, 9: wxyz }
 *
 * Recursive solution, faster than 100% (well, too few test cases to measure), less memory than
 * 92.51% of C++ submissions.
 *
 ************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

#include "util.h"

using namespace std;

class Solution {
public:
    vector<string> letterCombinations(const string& digits_)
    {
        if (digits_.empty()) return {};
        solution.clear();
        digits = digits_;
        solve(0, "");
        return solution;
    }
private:
    static vector<string> letters;
    vector<string> solution;
    string digits;
    void solve(const unsigned short i, const string cur)
    {
        if (i == digits.size()) { solution.push_back(cur); return; }
        for (const char& c : letters[digits[i]-50]) { // '0' == 48, -2 index in letters
            solve(i+1, cur + c);
        }
    }
};

vector<string> Solution::letters { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };


int main(void)
{
    cout << Solution().letterCombinations("23") << endl;
    cout << Solution().letterCombinations("") << endl;
    cout << Solution().letterCombinations("2") << endl;
    cout << Solution().letterCombinations("2582") << endl;
    return 0;
}
