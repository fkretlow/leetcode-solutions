/*************************************************************************************************
 *
 * 684. Redundant Connection
 *
 * Given an undirected graph G as a list of edges E, return the edge in E whose addition to G
 * violates the tree-property of G. In other words: Identify the circle c in G and return the edge
 * in c that appears last in E.
 *
 * Simple DFS to find the circle, slightly complicated by the requirement to return the last edge
 * in E of the circle. Faster than 65%, less memory than 17% of C++ submissions. Use of data
 * structures could be streamlined at the cost of loss of clarity.
 *
 ************************************************************************************************/

#include <bitset>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& V)
{
    os << '[';
    if (!V.empty()) {
        for (typename vector<T>::size_type i = 0; i < V.size() - 1; ++i) {
            os << V[i] << ',';
        }
        os << V.back();
    }
    return os << ']';
}

class Solution {
    vector<vector<int>> adj;
    vector<bool> discovered;
    vector<int> parent;
    bool finished;
    set<vector<int>> circle;

public:
    vector<int> redundant_connection(vector<vector<int>>& edges)
    {
        adj.clear();
        for (const auto& e : edges) {
            if (adj.size() < e[1]+1) adj.insert(adj.end(), e[1]+1 - adj.size(), { });
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        discovered.clear();
        discovered.insert(discovered.end(), adj.size(), false);

        parent.clear();
        parent.insert(parent.end(), adj.size(), 0);

        dfs(1);

        for (auto it = edges.rbegin(); it != edges.rend(); ++it) {
            if (circle.find(*it) != circle.end()) return *it;
        }

        return {};
    }

private:
    void dfs(const int u) {
        for (const int& v : adj[u]) {
            if (!discovered[v]) {
                discovered[v] = true;
                parent[v] = u;
                dfs(v);
            }
            else if (discovered[v] && v != parent[u]) { // found a circle
                finished = true;
                for (int p = u, c = v; p != v; c = p, p = parent[p]) {
                    circle.insert({ c < p ? c : p, c < p ? p : c });
                }
                return;
            }
            if (finished) return;
        }
    }
};

int main(void)
{
    vector<vector<int>> test_case { {1,2}, {1,3}, {2,3} };
    // vector<vector<int>> test_case { {1,2}, {2,3}, {3,4}, {1,4}, {1,5} };

    cout << Solution().redundant_connection(test_case) << endl;
    return 0;
}
