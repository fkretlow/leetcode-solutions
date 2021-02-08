/*************************************************************************************************
 *
 * 208. Trie
 * Implement a trie with insert, search and startsWith methods.
 *
 * Faster than 80.27%, less memory than 97.5% of C++ submissions.
 *
 ************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie {
public:
    Trie() { graph.push_back({ false, {} }); }
    void insert(string word);
    bool search(string word);
    bool startsWith(string prefix);
private:
    struct Edge {
        size_t vertex;
        char label;
    };
    struct Vertex {
        bool end;
        vector<Edge> adjacent;
    };
    vector<Vertex> graph;
};

void Trie::insert(string word)
{
    size_t cur = 0;
    bool found;
    for (const char &c : word) {
        found = false;
        for (const Edge &e : graph[cur].adjacent) {
            if (e.label == c) {
                found = true;
                cur = e.vertex;
                break;
            }
        }
        if (!found) {
            graph.push_back({ false, {} });
            graph[cur].adjacent.push_back({ graph.size()-1, c });
            cur = graph.size()-1;
        }
    }
    graph[cur].end = true;
}

bool Trie::search(string word)
{
    size_t cur = 0;
    bool found;
    for (const char &c : word) {
        found = false;
        for (const Edge &e : graph[cur].adjacent) {
            if (e.label == c) {
                found = true;
                cur = e.vertex;
                break;
            }
        }
        if (!found) return false;
    }
    return graph[cur].end;
}

bool Trie::startsWith(string prefix)
{
    size_t cur = 0;
    bool found;
    for (const char &c : prefix) {
        found = false;
        for (const Edge &e : graph[cur].adjacent) {
            if (e.label == c) {
                found = true;
                cur = e.vertex;
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}


int main(void)
{
    cout << boolalpha;

    Trie trie;
    trie.insert("apple");
    cout << "search \"apple\": " << trie.search("apple")   << endl;
    cout << "search \"app\": "   << trie.search("app")     << endl;
    cout << "prefix \"app\": "   << trie.startsWith("app") << endl;
    trie.insert("app");
    cout << "search \"app\": "   << trie.search("app")     << endl;

    return 0;
}
