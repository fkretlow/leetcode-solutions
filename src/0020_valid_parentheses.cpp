/*************************************************************************************************
 *
 * 20. Valid Parentheses
 *
 * Given a string containing just the characters '(',')','{','}','[',']', determine if the input
 * string is valid.
 *
 * Simple use case for a stack. Faster than 100% (too small a problem), less memory than 75.82% of
 * C++ submissions.
 *
 ************************************************************************************************/

#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isValid(const string& s) const
    {
        stack<char> pairs;
        for (const char& c : s) {
            switch (c) {
                case '(':
                case '{':
                case '[':
                    pairs.push(c);
                    break;
                case ')':
                    if (pairs.empty() || pairs.top() != '(') return false;
                    pairs.pop();
                    break;
                case '}':
                    if (pairs.empty() || pairs.top() != '{') return false;
                    pairs.pop();
                    break;
                case ']':
                    if (pairs.empty() || pairs.top() != '[') return false;
                    else pairs.pop();
                    break;
            }
        }
        return pairs.empty();
    }
};


int main(void)
{
    vector<string> tests { "()", "()[]{}", "(]", "([)]", "{[]}", "(", "(abc)", "())(" };
    cout << boolalpha;
    for (const string& t : tests) {
        cout << t << ": " << Solution().isValid(t) << endl;
    }
    return 0;
}
