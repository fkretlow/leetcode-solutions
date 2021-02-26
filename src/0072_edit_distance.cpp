/*************************************************************************************************
 *
 * 72. Edit Distance
 * Self-explanatory. Solution based on Skiena.
 *
 * Runtime: 85.92%, memory usage: 54.98%
 *
 ************************************************************************************************/

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    int minDistance(std::string const& from, std::string const& to) const
    {
        std::vector<std::vector<int>> D( to.size()+1, std::vector<int>(from.size()+1, 0));
        int opt[3];

        for (size_t i = 0; i <= to.size(); ++i)     D[i][0] = i;
        for (size_t j = 0; j <= from.size(); ++j)   D[0][j] = j;

        for (size_t i = 1; i <= to.size(); ++i) {
            for (size_t j = 1; j <= from.size(); ++j) {
                opt[MATCH] = D[i-1][j-1] + int(to[i-1] != from[j-1]);
                opt[DELETE] = D[i-1][j] + 1;
                opt[INSERT] = D[i][j-1] + 1;
                D[i][j] = min(opt, 3);
            }
        }
        return D.back().back();
    }
private:
    int min(const int* A, size_t n) const
    {
        int r = *A;
        while (--n) r = std::min(r, *(++A));
        return r;
    }
    enum { MATCH=0, DELETE=1, INSERT=2 };
};

void test(const std::string from, const std::string to)
{
    static const Solution instance;
    int d = instance.minDistance(from, to);
    std::cout << from << " -> " << to << ": " << d << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc > 1) {
        test(argv[1], argv[2]);
    }

    else {
        test("horse", "ros");
        test("", "a");
        test("a", "");
    }

    return 0;
}
