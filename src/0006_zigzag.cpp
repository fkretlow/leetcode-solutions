#include <iostream>
#include <vector>
#include <string>

class Solution {
public:
    std::string convert(const std::string &s, const int nrows) const
    {
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
    return 0;
}
