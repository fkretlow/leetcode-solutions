/*************************************************************************************************
 *
 * 207. Course Schedule
 *
 * There are a total of numCourses courses you have to take, labeled from 0 to numCourses-1.
 * Some courses may have prerequisites, for example to take course 0 you have to first take course
 * 1, which is expressed as a pair: [0,1]
 * Given the total number of courses and a list of prerequisite pairs, is it possible for you to
 * finish all courses?
 *
 * This is a simple check for circles in a directed graph. We perform a dfs and bail out as soon
 * as we encounter a back edge. Otherwise we're okay.
 *
 ************************************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include "util.h"

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites)
    {
        // reset state
        state.clear();
        adj.clear();
        for (int i = 0; i < numCourses; ++i) {
            state.push_back(undiscovered);
            adj.push_back(vector<int>());
        }

        // populate adjacency list
        for (const auto& e : prerequisites) adj[e[0]].push_back(e[1]);

        // perform dfs to check for circles
        for (int v = 0; v < numCourses; ++v) {
            if (state[v] == undiscovered && dfs(v) == false) return false;
        }
        return true;
    }
private:
    bool dfs(int v) {
        state[v] = discovered;
        for (const int& w : adj[v]) {
            if (state[w] == discovered)                      return false;
            if (state[w] == undiscovered && dfs(w) == false) return false;
        }
        state[v] = processed;
        return true;
    }

    enum dfs_state : uint8_t { undiscovered, discovered, processed };
    vector<dfs_state> state;
    vector<vector<int>> adj;
};

typedef std::vector<std::vector<int>> edge_list;

int main(void) {
    vector<string> test_cases = {
        "1\n[]\ntrue",
        "2\n/[1,0]]\ntrue",
        "2\n[[1,0],[0,1]]\nfalse",
        "5\n[[0,1],[1,2],[2,0],[3,4]]\nfalse",
        "5\n[[0,1],[1,2],[2,3],[3,4]]\ntrue",
    };

    Solution instance;
    int N;
    std::shared_ptr<edge_list> prerequisites;
    bool expected;

    for (size_t i = 0; i < test_cases.size(); ++i) {
        cout << "Test case " << i+1 << endl;

        try {
            stringstream is { test_cases[i] };
            is >> N;
            prerequisites = parse_matrix(is);
            expected = parse_bool(is);
        } catch (std::runtime_error e) {
            cerr << "failed to parse test case (" << e.what() << ')' << endl;
            cerr << endl;
        }

        cout << "N=" << N
            << ", prerequisites=" << *prerequisites
            << ", expected=" << boolalpha << expected
            << flush;

        bool res = instance.canFinish(N, *prerequisites);
        cout << ", result=" << res << endl;
        if (res != expected)    cout << "Error: expected " << expected << endl;
        else                    cout << "Ok" << endl;
        cout << endl;
    }
    return 0;
}
