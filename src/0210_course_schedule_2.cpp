/*************************************************************************************************
 *
 * 210. Course Schedule II
 *
 * There are a total of n courses you have to take labelled from 0 to n - 1.
 * Some courses may have prerequisites, for example, if prerequisites[i] = [ai, bi] this means you
 * must take the course bi before the course ai.
 * Given the total number of courses numCourses and a list of the prerequisite pairs, return the
 * ordering of courses you should take to finish all courses.
 * If there are many valid answers, return any of them. If it is impossible to finish all courses,
 * return an empty array.
 *
 * Same approach as in Course Schedule I, except we generate a topological ordering.
 *
 ************************************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
    {
        // reset state
        state.clear();
        adj.clear();
        sorted.clear();
        for (int i = 0; i < numCourses; ++i) {
            state.push_back(undiscovered);
            adj.push_back(vector<int>());
        }

        // populate adjacency list
        for (const auto& e : prerequisites) adj[e[0]].push_back(e[1]);

        // perform dfs to generate a topological ordering
        for (int v = 0; v < numCourses; ++v) {
            if (state[v] == undiscovered && dfs(v) == false) return {};
        }

        return sorted;
    }
private:
    bool dfs(int v) {
        state[v] = discovered;
        for (const int& w : adj[v]) {
            if (state[w] == discovered)                      return false;
            if (state[w] == undiscovered && dfs(w) == false) return false;
        }
        state[v] = processed;
        sorted.push_back(v);
        return true;
    }

    enum dfs_state : uint8_t { undiscovered, discovered, processed };
    vector<dfs_state> state;
    vector<vector<int>> adj;
    vector<int> sorted;
};

ostream& operator<<(ostream& os, vector<int> v)
{
    os << '[';
    if (v.size() > 0) {
        for (auto it = v.cbegin(); it < v.cend() - 1; ++it) os << *it << ',';
        os << *(v.cend() - 1);
    }
    return os << ']';
}

ostream& operator<<(ostream& os, vector<vector<int>> v)
{
    os << '[';
    if (v.size() > 0) {
        for (auto it = v.cbegin(); it < v.cend() - 1; ++it) os << *it << ',';
        os << *(v.cend() - 1);
    }
    return os << ']';
}

int main(void) {
    vector<int> N;
    vector<vector<vector<int>>> prerequisites;
    vector<vector<int>> expected;

    N.push_back(2);
    prerequisites.push_back({{1,0}});
    expected.push_back({0,1});

    N.push_back(4);
    prerequisites.push_back({{1,0},{2,0},{3,1},{3,2}});
    expected.push_back({0,2,1,3});

    N.push_back(1);
    prerequisites.push_back({});
    expected.push_back({0});

    Solution instance;
    for (size_t i = 0; i < N.size(); ++i) {
        cout << "\nTest case " << i+1 << '\n'
             << "N=" << N[i] << ", prerequisites=" << prerequisites[i] << endl;

        vector<int> res = instance.findOrder(N[i], prerequisites[i]);
        cout << "result=" << res << ": ";
        if (res != expected[i]) {
            cout << "Error: expected " << expected[i] << endl;
        }
        else {
            cout << "Ok" << endl;
        }
    }
    return 0;
}
