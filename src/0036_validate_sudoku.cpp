/*************************************************************************************************
 *
 * 36. Valid Sudoku
 * Determine if a 9 x 9 Sudoku board is valid. Only the filld cells need to be validated.
 * Runtime: 87.88%, memory usage: 82.78%
 *
 ************************************************************************************************/

#include <bitset>
#include <cctype>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<char>> Sudoku;

template<typename T>
void print_matrix(std::ostream& os, std::vector<std::vector<T>> const& M)
{
    for (const std::vector<T>& row : M) {
        for (const T& x : row) os << x << ' ';
        os << std::endl;
    }
}

class Solution {
public:
    bool operator()(Sudoku const& board) const { return isValidSudoku(board); }
    bool isValidSudoku(Sudoku const& board) const
    {
        std::bitset<9> quadrants[9];
        std::bitset<9> rows[9];
        std::bitset<9> columns[9];

        for (short i = 0; i < 9; ++i) {
            for (short j = 0; j < 9; ++j) {
                if (!isdigit(board[i][j])) continue;
                short n = board[i][j] - 49;
                short k = (i/3) * 3 + (j/3);
                if (quadrants[k].test(n) || rows[i].test(n) || columns[j].test(n)) return false;
                quadrants[k].set(n);
                rows[i].set(n);
                columns[j].set(n);
            }
        }

        return true;
    }
};


void test(const Sudoku board)
{
    static const Solution validate;
    bool res = validate(board);
    print_matrix(std::cout, board);
    std::cout << std::boolalpha << res << std::endl;
}


int main()
{
    test({{'5','3','.','.','7','.','.','.','.'}
         ,{'6','.','.','1','9','5','.','.','.'}
         ,{'.','9','8','.','.','.','.','6','.'}
         ,{'8','.','.','.','6','.','.','.','3'}
         ,{'4','.','.','8','.','3','.','.','1'}
         ,{'7','.','.','.','2','.','.','.','6'}
         ,{'.','6','.','.','.','.','2','8','.'}
         ,{'.','.','.','4','1','9','.','.','5'}
         ,{'.','.','.','.','8','.','.','7','9'}});
    return 0;
}
