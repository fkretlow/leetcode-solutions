/*************************************************************************************************
 *
 * 48. Rotate Image
 * Rotate a quadratic matrix of integers in place.
 *
 * Runtime: 59.74%, Memory Usage: 55.25%
 *
 ************************************************************************************************/

#include <exception>
#include <iomanip>
#include <iostream>
#include <vector>

#include "util.h"

typedef std::vector<std::vector<int>> matrix;

void print_matrix(std::ostream& os, const matrix& M)
{
    int w = 1;
    for (const auto& row : M) {
        for (const auto& x : row) {
            if (x > 9) { w = 2; break; }
        }
    }

    os << std::right;

    for (const auto& row : M) {
        for (const auto& x : row) os << std::setw(w) << x << ' ';
        os << std::endl;
    }
}

class Solution {
public:
    void rotate(matrix& M) const
    {
        if (M.size() != M.at(0).size()) throw std::runtime_error("non-quadratic matrix");
        for (int min = 0, max = M.size()-1; min < max; ++min, --max) {
            for (int i = min; i < max; ++i) {
                std::swap(M[min][i], M[i][max]);
                std::swap(M[min][i], M[max][max-i+min]);
                std::swap(M[min][i], M[max-i+min][min]);
            }
        }
    }
};

void test(matrix M)
{
    static Solution instance;
    print_matrix(std::cout, M);
    std::cout << "->" << std::endl;
    instance.rotate(M);
    print_matrix(std::cout, M);
    std::cout << std::endl;
}

int main()
{
    test({ {1} });
    test({ {1,2,3}, {4,5,6}, {7,8,9} });
    test({ {1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16} });
    return 0;
}
