/*************************************************************************************************
 *
 * 526. Beautiful Arrangements
 *
 * Suppose you have n integers labeled 1 through n. A permutation of those n integers perm
 * (1-indexed) is considered a beautiful arrangement if for every i (1 <= i <= n), the following
 * is true: i | perm[i] OR perm[i] | i.
 * Given an integer n, return the number of the beautiful arrangements that you can construct.
 *
 ************************************************************************************************/

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Solution {
    vector<vector<int>> candidates;
    vector<bool> used;
    int count;
    int N;

public:
    int count_arrangements(const int n)
    {
        candidates.clear();
        used.clear();
        used.insert(used.begin(), n, false);
        count = 0;
        N = n;

        for (int i = 1; i <= n; ++i) {
            candidates.push_back({ 1 });
            for (int x = 2; x <= n; ++x) {
                if (x % i == 0 || i % x == 0) candidates.back().push_back(x);
            }
        }

        solve_recursively(0);
        return count;
    }

private:
    void solve_recursively(const int i)
    {
        if (i == N) { ++count; return; }
        for (const auto& x : candidates[i]) {
            if (used[x] == false) {
                used[x] = true;
                solve_recursively(i + 1);
                used[x] = false;
            }
        }
    }
};


int main(int argc, char *argv[])
{
    if (argc < 2) cout << "USAGE: arr <n>" << endl;

    int n = stoi(argv[1]);
    cout << Solution().count_arrangements(n) << endl;

    return 0;
}
