/*************************************************************************************************
 *
 * 114. Flatten Binary Tree to Linked List
 * Given the root of a binary tree, flatten the tree into a linked list in the same order as a
 * pre-order-traversal of the tree.
 *
 * The trick is not to traverse each partly generated list to append something on the right.
 * Prepend single values on the left instead. Simple recursive solution, runtime: 92.53%, memory
 * usage: 95.93%
 *
 ************************************************************************************************/

#include <iostream>
#include <string>
#include "tree.h"

class Solution {
public:
    TreeNode* flatten(TreeNode* n, TreeNode* acc=nullptr)
    {
        if (!n) return acc;
        acc = flatten(n->right, acc);
        acc = flatten(n->left, acc);
        n->left = nullptr;
        n->right = acc;
        return n;
    }
};


void test(const std::string&& l)
{
    static Solution instance;
    TreeNode* tree = TreeNode::fromList(l);
    instance.flatten(tree);
    TreeNode* n = tree;
    std::cout << l << " -> [";
    if (n) {
        while (n && n->right) {
            std::cout << n->val << ',';
            n = n->right;
        }
        std::cout << n->val;
    }
    std::cout << ']' << std::endl;
}

int main()
{
    test("[1,2,5,3,4,nil,6]");
    test("[0]");
    test("[]");
    return 0;
}
