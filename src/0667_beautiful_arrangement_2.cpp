/*************************************************************************************************
 *
 * 667. Beautiful Arrangement II
 *
 * Given two integers n and k, you need to construct a list which contains n different positive
 * ranging from 1 to n and obeys the following requirement:
 * Suppose this list is [a1,a2,a3,...,an], then the list [|a1-a2|,|a2-a3|,...,|an-1 - an|] has
 * exactly k distinct integers.
 *
 * Produce k distinct steps from k+1 successive integers by "zig-zagging" through them, pad the
 * solution with the rest of the integers in order. O(n).
 *
 ************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> constructArray(const int n, const int k) const
    {
        vector<int> solution(n - k - 1);
        iota(solution.begin(), solution.end(), 1);

        int i = n - k;
        int j = n;
        while (i <= j) {
            solution.push_back(i++);
            if (solution.back() == j) break;
            solution.push_back(j--);
        }
        return solution;
    }
};

int main(int argc, char *argv[])
{
    if (argc < 3) { cout << "USAGE: arr <n> <k>"; return -1; }

    const int n = stoi(argv[1]);
    const int k = stoi(argv[2]);
    cout << Solution().constructArray(n, k) << endl;

    return 0;
}
