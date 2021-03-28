/*************************************************************************************************
 *
 * 211. Design Add and Search Words Data Structure
 *
 * Design a data structure that supports adding new words and finding if a string matches any
 * previously added string. Queries can contain '.' which match any letter.
 *
 * A trie-based solution with some additional logic for the wildcard during the search.
 * Runtime: 59.07%, memory usage: 92.56%.
 *
 ************************************************************************************************/

#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>


class WordDictionary {
public:
    WordDictionary() : trie('\0') {}
    void addWord(const std::string &w)
    {
        TrieNode *n = &trie;
        for (auto it = w.cbegin(); it != w.cend(); ++it) {
            bool isTerminal = (it == w.cend() - 1);
            bool exists = false;
            for (const std::shared_ptr<TrieNode> &nn : n->next) {
                if (nn->letter == *it) {
                    exists = true;
                    n = nn.get();
                    n->terminal = n->terminal || isTerminal;
                    break;
                }
            }
            if (!exists) {
                n->next.emplace_back(std::make_shared<TrieNode>(*it, isTerminal));
                n = n->next.back().get();
            }
        }
    }

    bool search(const std::string &w)
    {
        TrieNode *n = &trie;
        return search__r(w, w.cbegin(), n);
    }

private:
    struct TrieNode {
        char letter;
        bool terminal;
        std::vector<std::shared_ptr<TrieNode>> next;
        TrieNode(const char c) : letter(c), terminal(false) {}
        TrieNode(const char c, bool t) : letter(c), terminal(t) {}
    };

    TrieNode trie;
    bool search__r(const std::string &w,
                   std::string::const_iterator it,
                   const TrieNode *n)
    {
        if (it == w.cend()) {
            return n->terminal;
        } else if (*it == '.') {
            for (const std::shared_ptr<TrieNode> &nn : n->next) {
                if (search__r(w, it+1, nn.get())) return true;
            }
        } else {
            for (const std::shared_ptr<TrieNode> &nn : n->next) {
                if (nn->letter == *it) {
                    return search__r(w, it+1, nn.get());
                }
            }
        }
        return false;
    }
};

int main()
{
    std::cout << std::boolalpha;

    WordDictionary dict;
    dict.addWord("at");
    dict.addWord("and");
    dict.addWord("an");
    dict.addWord("add");

    std::cout << "search a: " << dict.search("a") << "(false)" << std::endl;
    std::cout << "search at: " << dict.search("at") << "(true)" << std::endl;

    dict.addWord("bat");

    std::cout << "search .at: " << dict.search(".at") << "(true)" << std::endl;
    std::cout << "search an.: " << dict.search("an.") << "(true)" << std::endl;
    std::cout << "search bat: " << dict.search("bat") << "(true)" << std::endl;
    std::cout << "search a.d.: " << dict.search("a.d.") << "(false)" << std::endl;
    std::cout << "search b.: " << dict.search("b.") << "(false)" << std::endl;
    std::cout << "search a.d: " << dict.search("a.d") << "(true)" << std::endl;
    std::cout << "search .: " << dict.search(".") << "(false)" << std::endl;

    return 0;
}
