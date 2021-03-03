/*************************************************************************************************
 *
 * 98. Validate BST
 * Given the root of a binary tree, determine if it is a valid binary search tree.
 *
 * Runtime: 77.78%, memory usage: 49.33%
 *
 ************************************************************************************************/

#include "tree.h"

class Solution {
public:
    bool isValidBST(TreeNode* root) {
        int min, max;
        return validate__r(root, min, max);
    }
private:
    bool validate__r(TreeNode* n, int& min, int& max)
    {
        if (!n) return true;
        int minl, maxl, minr, maxr;
        if (n->left) {
            if (!validate__r(n->left, minl, maxl)) return false;
            if (maxl >= n->val) return false;
            min = minl;
        } else {
            min = n->val;
        }

        if (n->right) {
            if (!validate__r(n->right, minr, maxr)) return false;
            if (minr <= n->val) return false;
            max = maxr;
        } else {
            max = n->val;
        }

        return true;
    }
};
