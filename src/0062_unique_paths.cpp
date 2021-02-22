/*************************************************************************************************
 *
 * 62. Unique Paths
 * A robot is located at the top-left corner of a m x n grid (where m is the number of rows). The
 * robot can only move either down or right at any point in time. The robot is trying to reach the
 * bottom-right corner of the grid. How many possible unique paths are there?
 *
 * This is a simple application of binomial coefficients: There are m-1 moves down and n-1 moves
 * to the right in total, and we look for the number of permutations of the string containing
 * those moves. Generate a static Pascal's triangle (collapsed into a single vector) and query
 * 'm-1 + n-1 choose m-1', expanding the triangle as needed.
 *
 * Runtime: "100%", memory usage: 59.15%
 *
 ************************************************************************************************/

#include <iostream>
#include <vector>

class PascalTriangle {
public:
    unsigned get(const unsigned n, const unsigned k)
    {
        grow(n);
        return m_data[get_index(n, k)];
    }
private:
    unsigned m_max = 0;
    std::vector<unsigned> m_data = { 1 };
    unsigned get_index(const unsigned n, const unsigned k)
    {
        return n * (n + 1) / 2 + k;
    }
    void grow(const unsigned to_n)
    {
        if (to_n <= m_max) return;
        for (unsigned n = m_max + 1; n <= to_n; ++n) {
            m_data.push_back(1);
            for (unsigned k = 1; k < n; ++k) {
                unsigned i = get_index(n-1, k-1);
                m_data.push_back(m_data[i] + m_data[i+1]);
            }
            m_data.push_back(1);
        }
        m_max = to_n;
    }
};

class Solution {
public:
    unsigned uniquePaths(const unsigned m, const unsigned n)
    {
        return m_trg.get(m + n - 2, m - 1);
    }
private:
    static PascalTriangle m_trg;
};

PascalTriangle Solution::m_trg;

void test(const unsigned m, const unsigned n)
{
    static Solution instance;
    unsigned res = instance.uniquePaths(m, n);
    std::cout << m << " x " << n << " --> " << res << std::endl;
}

int main()
{
    test(3, 7); // 28
    test(3, 2); // 3
    test(7, 3); // 28
    test(3, 3); // 6
    test(1,1); // 1
    test(2,2); // 2
}
