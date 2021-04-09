/*************************************************************************************************
 *
 * 785. Is Graph Bipartite?
 * Self-explanatory: two-coloring problem on an undirected, possibly unconnected graph.
 * connected.
 *
 * BFS. Runtime: 98.08%, memory usage: 43.63%. Could be significantly reduced (1/8) by using bits
 * instead of boolean values for state and color of the nodes. That's a hassle though.
 *
 ************************************************************************************************/

#include <iomanip>
#include <iostream>
#include <vector>
#include <queue>

#include "util.h"

class Solution {
public:
    bool isBipartite(const std::vector<std::vector<int>> &graph)
    {
        adj = &graph;
        discovered.clear();
        discovered.insert(discovered.begin(), graph.size(), false);
        color.clear();
        color.insert(color.begin(), graph.size(), false);

        for (size_t i = 0; i < graph.size(); ++i) {
            if (!discovered[i] && !bfs(i)) return false;
        }

        return true;
    }

private:
    const std::vector<std::vector<int>> *adj;
    std::vector<bool> discovered;
    std::vector<bool> color;

    bool bfs(int v)
    {
        std::queue<int> Q;
        Q.push(v);
        color[v] = true;
        discovered[v] = true;
        while (!Q.empty()) {
            v = Q.front();
            Q.pop();
            for (const auto &u : adj->at(v)) {
                if (!discovered[u]) {
                    Q.push(u);
                    discovered[u] = true;
                    color[u] = !color[v];
                } else {
                    if (color[u] == color[v]) return false;
                }
            }
        }
        return true;
    }
};

void test(std::vector<std::vector<int>> graph)
{
    static Solution instance;
    bool res = instance.isBipartite(graph);
    std::cout << graph << " -> " << res << std::endl;
}

int main()
{
    std::cout << sizeof(bool) << std::endl;

    std::cout << std::boolalpha;
    test({{1,2,3},{0,2},{0,1,3},{0,2}});
    test({{1,3},{0,2},{1,3},{0,2}});
    test({{}});
}
