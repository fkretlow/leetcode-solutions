/*************************************************************************************************
 *
 * 6. Zigzag Conversion
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
 * (you may want to display this pattern in a fixed font for better legibility)
 *     P   A   H   N
 *     A P L S I I G
 *     Y   I   R
 * And then read line by line: "PAHNAPLSIIGYIR" Write the code that will take a string and make
 * this conversion given a number of rows.
 *
 * Runtime: 86.91%, memory usage: 49.38%.
 *
 ************************************************************************************************/

#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::string convert(const std::string &s, const int nrows) const
    {
        if (nrows == 1) return s;
        std::vector<std::string> rows(nrows);
        size_t i = 0;
        for (size_t j = 0; j < s.size(); ++j) {
            rows.at(i).push_back(s.at(j));
            i = advanceRow(i, j, nrows);
        }
        std::string solution;
        for (const auto &r : rows) solution += r;
        return solution;
    }
private:
    int advanceRow(const int i, const int j, const int nrows) const
    {
        if (j % (2 * nrows - 2) >= nrows - 1) return i - 1;
        return i + 1;
    }
};

void test(std::string s, int nrows)
{
    static const Solution instance;
    std::cout << s << " -> " << instance.convert(s, nrows) << std::endl;
}

int main(void)
{
    test("PAYPALISHIRING", 3);
    test("PAYPALISHIRING", 4);
    test("PAYPALISHIRING", 2);
    test("PAYPALISHIRING", 1);
    return 0;
}
