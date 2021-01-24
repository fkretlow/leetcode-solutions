#include <cctype>
#include <climits>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    int myAtoi(string s)
    {
        string::size_type i = 0;
        while (s[i] == ' ') ++i;

        char sign = '+';
        if (s[i] == '+' || s[i] == '-') sign = s[i++];

        int64_t res = 0;
        while (isdigit(s[i])) {
            res *= 10;
            res += s[i++] - 48; // '0' == 48
            if (sign == '+' && res > INT_MAX)       return INT_MAX;
            if (sign == '-' && res > INT_MAX + 1l)  return INT_MIN;
        }

        return static_cast<int>((sign == '+' ? 1 : -1) * res);
    }
};

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cout << "USAGE: stoi <number>" << endl;
        return -1;
    }

    Solution instance;
    cout << instance.myAtoi(argv[1]) << endl;
    return 0;
}
