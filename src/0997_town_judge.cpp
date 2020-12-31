#include <iostream>
#include <vector>

using namespace std;

int find_judge(int N, vector<vector<int>> trust)
{
    vector<vector<int>> deg(N, vector<int>(2)); // first: out-degree, second: in-degree
    for (const auto &e : trust) {
        ++deg[e[0]-1][0];
        ++deg[e[1]-1][1];
    }

    for (int v = 0; v < N; ++v) {
        if (deg[v][0] == 0 && deg[v][1] == N-1) return v + 1;
    }
    return -1;
}

int main(void)
{
    vector<int> N;
    vector<vector<vector<int>>> trust;
    vector<int> expected;

    N.push_back(2);
    trust.push_back({{1,2}});
    expected.push_back(2);

    N.push_back(3);
    trust.push_back({{1,3}, {2,3}});
    expected.push_back(3);

    N.push_back(3);
    trust.push_back({{1,3},{2,3},{3,1}});
    expected.push_back(-1);

    N.push_back(3);
    trust.push_back({{1,2}, {2,3}});
    expected.push_back(-1);

    N.push_back(4);
    trust.push_back({{1,3},{1,4},{2,3},{2,4},{4,3}});
    expected.push_back(3);

    int res;
    for (int i = 0; i < N.size(); ++i) {
        res = find_judge(N[i], trust[i]);
        if (res != expected[i]) {
            cout << "Error: example " << i+1 << ": "
                 << "result=" << res << ", expected=" << expected[i] << endl;
        }
    }
}
