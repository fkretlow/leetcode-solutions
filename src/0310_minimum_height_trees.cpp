#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<int> mht(int n, vector<vector<int>> edges)
{
    if (n == 1) return { 0 };
    if (n == 2) return { 0, 1 };

    vector<vector<int>> adj(n);
    vector<int> deg(n, 0);

    for (const auto &e : edges) {
        adj[e[0]].push_back(e[1]);
        adj[e[1]].push_back(e[0]);
        ++deg[e[0]];
        ++deg[e[1]];
    }

    queue<int> leaves;
    for (int v = 0; v < n; ++v) {
        if (deg[v] <= 1) {
            leaves.push(v);
        }
    }

    do {
        size_t nleaves = leaves.size();
        for (size_t i = 0; i < nleaves; ++i) {
            const int l = leaves.front(); leaves.pop();
            for (const int &v : adj[l]) {
                if (--deg[v] == 1) leaves.push(v);
            }
        }
    } while (leaves.size() > 2);

    vector<int> roots;
    while (leaves.size()) {
        roots.push_back(leaves.front());
        leaves.pop();
    }
    return roots;
}

int main(void)
{
    // int n = 4;
    // vector<vector<int>> edges { {1,0}, {1,2}, {1,3} };
    // int n = 6;
    // vector<vector<int>> edges { {3,0}, {3,1}, {3,2}, {3,4}, {5,4} };
    // int n = 1;
    // vector<vector<int>> edges;
    // int n = 2;
    // vector<vector<int>> edges { {0,1} };
    int n = 3;
    vector<vector<int>> edges { {0,1}, {0,2} };
    vector<int> ts = mht(n, edges);
    for (const auto r : ts) cout << r << ' ';
    cout << endl;

    return 0;
}
