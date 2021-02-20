/*************************************************************************************************
 *
 * 79. Word Search
 * Given a matrix of characters and a word, find if the word can be constructed by adjacent cells
 * in the matrix. No cell may be used more than once.
 *
 * Runtime: 97.17%, Memory Usage: 86.40%
 *
 ************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    bool exist(const std::vector<std::vector<char>>& _board, const std::string& _word)
    {
        word = &_word;
        board = &_board;
        m = board->at(0).size();
        n = board->size();
        used.clear();
        used.insert(used.begin(), n, std::vector<bool>(m, false));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (search_r(i, j, 0)) return true;
            }
        }
        return false;
    }
private:
    bool search_r(const int i, const int j, const int k)
    {
        if (used[i][j] || (*board)[i][j] != (*word)[k])                 return false;
        if (static_cast<std::string::size_type>(k) == word->size()-1)   return true;

        used[i][j] = true;
        if (i-1 >= 0 && search_r(i-1, j, k+1)) return true;
        if (i+1 < n  && search_r(i+1, j, k+1)) return true;
        if (j-1 >= 0 && search_r(i, j-1, k+1)) return true;
        if (j+1 < m  && search_r(i, j+1, k+1)) return true;

        used[i][j] = false;
        return false;
    }
    const std::vector<std::vector<char>>* board;
    std::vector<std::vector<bool>> used;
    int m, n;
    const std::string* word;
};

template<typename T>
void print_matrix(std::ostream& os, std::vector<std::vector<T>> const& M)
{
    for (const std::vector<T>& row : M) {
        for (const T& x : row) os << x << ' ';
        os << std::endl;
    }
}

void test(std::vector<std::vector<char>> board, std::string word)
{
    static Solution instance;
    std::cout << "Board:" << std::endl;
    print_matrix(std::cout, board);
    std::cout << "Word: " << word << std::endl;
    std::cout << std::boolalpha << instance.exist(board, word) << std::endl;
}

int main(int argc, char **argv)
{
    test({ {'A'} }, "A");
    test({ {'A','B','C','D'}, {'E','F','G','H'}, {'I','J','K','L'} }, argv[1]);
    return 0;
}
