/*************************************************************************************************
 *
 * 138. Copy List with Random Pointer
 * You are given a linked list where each node contains an additional random pointer which could
 * point to any other node in the list, or null. Construct a deep copy of the list.
 * Lazy solution where we construct a mapping between old and new nodes in a first pass and set
 * pointers in the second pass. Even lazier: Parsing test cases would be a pain, so no tests here.
 * Submission accepted with runtime: 38.97%, memory usage: 51.30%
 *
 ************************************************************************************************/

#include <map>

class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int x) : val(x), next(nullptr), random(nullptr) {}
};

class Solution {
public:
    Node* copyRandomList(Node* head)
    {
        std::map<Node*, Node*> mapping;

        for (Node* cur = head; cur; cur = cur->next) {
            Node* n = new Node(cur->val);
            mapping[cur] = n;
        }

        for (Node* cur = head; cur; cur = cur->next) {
            Node* n = mapping[cur];
            n->next = mapping[cur->next];
            if (cur->random) n->random = mapping[cur->random];
        }

        return mapping[head];
    }
};
