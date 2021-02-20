/*************************************************************************************************
 *
 * 22. Generate Parentheses
 * Given n pairs of parentheses, write a function to generate all combinations of well-formed
 * parentheses.
 *
 * Rather slow recursive solution, faster than 38.39%, less memory than 49.09% of C++ submissions.
 *
 ************************************************************************************************/

#include <exception>
#include <iostream>
#include <string>
#include <vector>

#include "util.h"

using namespace std;

class Solution {
public:
    vector<string> generateParenthesis(const unsigned short n)
    {
        solution.clear();
        solve(n-1, n, "(");
#ifndef NDEBUG
        for (const string& result : solution) {
            if (!check(result)) throw logic_error("bad result: " + result);
        }
#endif
        return solution;
    }
private:
    vector<string> solution;
    void solve(const unsigned short opening, const unsigned short closing, const string cur)
    {
        if (opening == 0 && closing == 0) { solution.push_back(cur); return; }
        if (opening)            solve(opening-1, closing, cur + '(');
        if (closing > opening)  solve(opening, closing-1, cur + ')');
    }
#ifndef NDEBUG
    bool check(const string& result)
    {
        int count = 0;
        for (const char& p : result) {
            if (p == '(') ++count;
            else          --count;
            if (count < 0) return false;
        }
        return count == 0;
    }
#endif
};


int main(void)
{
    cout << Solution().generateParenthesis(3) << endl;
    cout << Solution().generateParenthesis(2) << endl;
    cout << Solution().generateParenthesis(1) << endl;
    return 0;
}
