/*************************************************************************************************
 *
 * 94. Binary Tree Inorder Traversal
 * Runtime: "100%", memory usage: 74.38%.
 *
 ************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include "tree.h"
#include "util.h"

class Solution {
public:
    std::vector<int> inorderTraversal(const TreeNode *const root) const
    {
        std::vector<int> ordered;
        traverse__r(root, ordered);
        return ordered;
    }
private:
    void traverse__r(const TreeNode *const n, std::vector<int> &V) const
    {
        if (!n) return;
        traverse__r(n->left, V);
        V.push_back(n->val);
        traverse__r(n->right, V);
    }
};


void test(const std::string &&s)
{
    static const Solution instance;
    TreeNode* root = TreeNode::fromList(s);
    std::vector<int> ordered = instance.inorderTraversal(root);
    std::cout << s << " -> " << ordered << std::endl;
}


int main()
{
    test("[1,null,2,null,null,3,null]");
    test("[1,2,null]");
    test("[1,null,2]");
    return 0;
}
