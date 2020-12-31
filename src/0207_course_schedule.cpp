#include <iostream>
#include <stack>
#include <vector>

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

        for (int v = 0; v < numCourses; ++v) {
            if (state[v] == undiscovered) {
                if (dfs(v) == false) return false;
            }
        }
        return true;
    }
private:
    bool dfs(int v) {
        state[v] = discovered;
        for (const int& w : adj[v]) {
            if (state[w] == discovered) {
                // found a back edge: not a DAG
                return false;
            }
            if (state[w] == undiscovered) {
                if (dfs(w) == false) return false;
            }
        }
        state[v] = processed;
        return true;
    }

    enum dfs_state : unsigned char { undiscovered, discovered, processed };
    vector<dfs_state> state;
    vector<vector<int>> adj;
};

int main(void) {
    vector<int> N;
    vector<vector<vector<int>>> prerequisites;
    vector<bool> expected;

    N.push_back(1);
    prerequisites.push_back(vector<vector<int>>());
    expected.push_back(true);

    N.push_back(2);
    prerequisites.push_back({{1,0}});
    expected.push_back(true);

    N.push_back(2);
    prerequisites.push_back({{1,0},{0,1}});
    expected.push_back(false);

    N.push_back(4);
    prerequisites.push_back({{0,1}, {1,2}, {2,0}, {3,4}});
    expected.push_back(false);

    N.push_back(4);
    prerequisites.push_back({{0,1}, {1,2}, {2,3}, {3,4}});
    expected.push_back(true);

    Solution instance;
    for (size_t i = 0; i < N.size(); ++i) {
        cout << "\nTest case " << i+1 << '\n'
             << "N=" << N[i] << ", prerequisites=[";
        for (const auto& e : prerequisites[i]) cout << e[0] << "->" << e[1] << ' ';
        cout << ']' << endl;

        bool res = instance.canFinish(N[i], prerequisites[i]);
        cout << boolalpha << res << ": ";
        if (res != expected[i]) {
            cout << "Error: expected " << expected[i] << endl;
        }
        else {
            cout << "Ok" << endl;
        }
    }
    return 0;
}
