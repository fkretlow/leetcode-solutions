#include <iostream>
#include <queue>
#include <vector>

class Node {
    public:
        int val;
        vector<Node*> neighbors;

        Node() : val(0), neighbors({}) {};
        Node(int _val) : val(_val), neighbors({}) {};
        Node(int _val, vector<Node*> _neighbors) : val(_val), neighbors(_neighbors) {};
};

Node* clone_graph(Node* node)
{
    vector<Node*> clone;
    clone.push_back(nullptr);
    clone.push_back(new Node());
    vector<bool> discovered(2, false);

    queue<Node*> Q;
    Q.push(node);
    discovered[node->val] = true;

    while (Q.size() > 0) {
        Node* u = Q.front(); Q.pop();

        clone[u->val]->val = u->val;

        for (const Node* v : u->neighbors) {
            if (static_cast<vector<bool>::size_type>(v->val) >= discovered.size()) {
                for (auto i = discovered.size(); i <= v->val; ++i) {
                    discovered.push_back(false);
                    clone.push_back(new Node());
                }
            }

            clone[u->val]->neighbors.push_back(clone[v->val]);

            if (discovered[v->val] == false) {
                discovered[v->val] = true;
                Q.push(v);
            }
        }
    }

    return clone[1];
}
