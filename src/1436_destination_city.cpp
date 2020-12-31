#include <assert.h>
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef pair<string, string> Path;

string destination(vector<Path> &paths)
{
    set<string> to;
    for (const auto &p : paths) {
        to.insert(p.second);
    }
    for (const auto &p : paths) {
        set<string>::iterator pos = to.find(p.first);
        if (pos != to.end()) to.erase(pos);
    }
    assert(to.size() == 1);
    string dest = *(to.begin());
    return dest;
}

int main(void) {
    vector<Path> paths {
        { "London","New York" },{ "New York","Lima" },{ "Lima","Sao Paulo" }
    };
    const string dest = destination(paths);
    cout << dest << endl;
    return 0;
}
