#include <bitset>
#include <iostream>
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
    vector<int> res;

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
        return res;
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
                if (u < v) res = {u,v};
                else       res = {v,u};
                return;
            }
            if (finished) return;
        }
    }
};

int main(void)
{
    // vector<vector<int>> test_case { {1,2}, {1,3}, {2,3} };
    vector<vector<int>> test_case { {1,2}, {2,3}, {3,4}, {1,4}, {1,5} };

    cout << Solution().redundant_connection(test_case) << endl;
    return 0;
}
