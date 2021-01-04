#include <iostream>
#include <queue>
#include <unordered_map>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class Solution {
    typedef unordered_map<string, priority_queue<string, vector<string>, greater<string>>> Graph;

public:
    vector<string> findItinerary(vector<vector<string>>& tickets)
    {
        Graph G;
        stack<string> res;
        vector<string> itn;

        for (const vector<string>& t : tickets) G[t[0]].push(t[1]);

        dfs(G, "JFK", res);

        while (!res.empty()) {
            itn.push_back(res.top()); res.pop();
        }
        return itn;
    }

private:
    void dfs(Graph& G, const string& from, stack<string>& res)
    {
        auto& Q = G[from];
        string next;
        while (!Q.empty()) {
            next = Q.top(); Q.pop();
            dfs(G, next, res);
        }
        res.push(from);
    }
};


int main(void)
{
    Solution instance;
    vector<vector<string>> tickets {
        { "JFK", "ABC" }, { "GHI", "DEF" }, { "DEF", "JFK" }, { "JFK", "GHI" }
        // { "MUC", "LHR" }, { "JFK", "MUC" }, { "SFO", "SJC" }, { "LHR", "SFO" }
        // { "JFK", "SFO" }, { "JFK", "ATL" }, { "SFO", "ATL" }, { "ATL", "JFK" }, { "ATL", "SFO" }
        // { "JFK", "ATL" }
        // {"EZE","AXA"},{"TIA","ANU"},{"ANU","JFK"},{"JFK","ANU"},{"ANU","EZE"},{"TIA","ANU"},{"AXA","TIA"},{"TIA","JFK"},{"ANU","TIA"},{"JFK","TIA"}
    };
    vector<string> itn = instance.findItinerary(tickets);
    for (const auto& v : itn) cout << v << ' ';
    cout << endl;
    return 0;
}
