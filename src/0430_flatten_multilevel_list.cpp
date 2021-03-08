/*************************************************************************************************
 *
 * 430. Flatten a Multilevel Doubly Linked List
 * Merge all elements in a linked list that contains child lists into a single list.
 *
 * Simple recursive solution, accumulating the flat list from right to left.
 * Runtime: 86.76%, memory usage: 71.59%
 *
 * Parsing test cases is too awkward to bother, so no main in this one.
 *
 ************************************************************************************************/

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};

class Solution {
public:
    Node* flatten(Node* n, Node* acc=nullptr)
    {
        if (n == nullptr) return acc;
        if (n->next) {
            acc = flatten(n->next, acc);
        }
        if (n->child) {
            acc = flatten(n->child, acc);
            n->child = nullptr;
        }
        n->next = acc;
        if (acc) acc->prev = n;
        return n;
    }
};
