#include <string>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode()                                : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x)                           : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l),       right(r)       {}
    static TreeNode* fromList(const std::string& l);
private:
    static TreeNode* parseList(const std::vector<std::string>& V, const size_t i);
};
