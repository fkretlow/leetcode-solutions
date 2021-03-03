/*************************************************************************************************
 *
 * 501. Find Mode in BST
 * Find all the mode(s) (the most frequently occurred element) in a given BST.
 *
 * Runtime: 59.29%, memory usage: 36.27%
 *
 ************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "tree.h"
#include "util.h"

class Solution {
public:
    std::vector<int> findMode(TreeNode* root)
    {
        count__r(root);
        std::vector<int> solution;
        for (const auto& p : counter) {
            std::cout << p.first << ':' << p.second << std::endl;
            if (p.second == maxCount) solution.push_back(p.first);
        }
        return solution;
    }
private:
    std::map<int, int> counter;
    int maxCount = 0;
    void count__r(TreeNode* n)
    {
        if (!n) return;
        ++counter[n->val];
        if (counter[n->val] > maxCount) ++maxCount;
        count__r(n->left);
        count__r(n->right);
    }
};

void test(const std::string&& s)
{
    static Solution instance;
    TreeNode* T = TreeNode::fromList(s);
    std::vector<int> solution = instance.findMode(T);
    std::cout << s << " -> " << solution << std::endl;
}

int main()
{
    test("[1,nil,2,nil,nil,2]");
    return 0;
}
