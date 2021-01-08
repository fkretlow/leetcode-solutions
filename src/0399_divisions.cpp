#include <iostream>
#include <forward_list>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations,
                                vector<double>& values,
                                vector<vector<string>>& queries)
    {
        // populate adjacency lists
        for (unsigned i = 0; i < equations.size(); ++i) {
            vector<string>& e = equations[i];
            double& v = values[i];
            G[e[0]].push_front({ e[1], v });
            G[e[1]].push_front({ e[0], 1.0 / v });
        }

        vector<double> result;
        for (const auto& q : queries) {
            if (G.find(q[0]) == G.cend() || G.find(q[1]) == G.cend())
                result.push_back(-1.0);
            else if (q[0] == q[1])
                result.push_back(1.0);
            else
                result.push_back(bfs(q[0], q[1]));
        }

        return result;
    }

private:
    double bfs(const string& from, const string& to) {
        queue<string> Q;
        unordered_map<string, bool> discovered;
        unordered_map<string, double> solutions;

        Q.push(from);
        solutions[from] = 1.0;

        while (!Q.empty()) {
            const string v = Q.front(); Q.pop();
            for (const pair<string, double>& e : G[v]) {
                if (!discovered[e.first]) {
                    if (e.first == to) return solutions[v] * e.second;
                    discovered[e.first] = true;
                    solutions[e.first] = solutions[v] * e.second;
                    Q.push(e.first);
                }
            }
        }

        return -1.0;
    }

    unordered_map<string, forward_list<pair<string, double>>> G;
};


int main(void)
{
    // vector<vector<string>> equations { {"a","b"},{"b","c"} };
    // vector<double> values { 2.0, 3.0 };
    // vector<vector<string>> queries { {"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"} };
    // vector<double> expected { 6.0, .5, -1.0, 1.0, -1.0 };

    // vector<vector<string>> equations { {"a","b"},{"b","c"},{"bc","cd"} };
    // vector<double> values { 1.5, 2.5, 5.0 };
    // vector<vector<string>> queries { {"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"} };
    // vector<double> expected { 3.75, 0.4, 5.0, 0.2 };

    // vector<vector<string>> equations { {"a","b"} };
    // vector<double> values { 0.5 };
    // vector<vector<string>> queries { {"a","b"},{"b","a"},{"a","c"},{"x","y"} };
    // vector<double> expected { 0.5, 2.0, -1.0, -1.0 };

    vector<vector<string>> equations { {"a","b"},{"e","f"},{"b","e"} };
    vector<double> values { 3.4, 1.4, 2.3 };
    vector<vector<string>> queries { {"b","a"},{"a","f"},{"f","f"},{"e","e"},{"c","c"},{"a","c"},{"f","e"} };
    vector<double> expected { 0.29412, 10.94800, 1.00000, 1.00000, -1.00000, -1.00000, 0.71429 };

    Solution instance;
    vector<double> result = instance.calcEquation(equations, values, queries);

    for (const double& v : result) cout << v << ' ';
    cout << endl;

    return 0;
}
