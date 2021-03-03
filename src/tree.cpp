#include <cctype>
#include <iostream>
#include <sstream>
#include "tree.h"
#include "util.h"

TreeNode* TreeNode::fromList(const std::string& s)
{
    std::vector<std::string> V;
    std::stringstream stream(s);

    stream.ignore(1, '[');
    char c;
    std::string buf;
    while (stream >> c) {
        if (!isalnum(c) && buf.size() > 0) {
            V.push_back(buf);
            buf.clear();
        }
        if (c == ']') break;
        if (c == ',') continue;
        buf.push_back(c);
    }

    return parseList(V, 0);
}

TreeNode* TreeNode::parseList(const std::vector<std::string>& V, const size_t i)
{
    if (i >= V.size()) return nullptr;
    const std::string& vs = V.at(i);
    if (vs == "null" || vs == "nil") return nullptr;
    int v = std::stoi(vs);
    TreeNode* n = new TreeNode(std::stoi(vs));
    n->left = parseList(V, 2*i + 1);
    n->right = parseList(V, 2*i + 2);
    return n;
}
