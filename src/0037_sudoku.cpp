/*************************************************************************************************
 *
 * 37. Sudoku Solver
 * Runtime: 97.91%, memory usage: 91.25%
 *
 ************************************************************************************************/

#include <bitset>
#include <cctype>
#include <climits>
#include <cstdint>
#include <iostream>
#include <vector>
#include "util.h"

class Solution {
public:
    bool solveSudoku(std::vector<std::vector<char>>& board)
    {
        for (const auto& row : board) {
            for (const char& c : row) {
                if (!isdigit(c)) ++freeCells;
            }
        }
        solve__r(board);
        return freeCells == 0;
    }

private:
    int freeCells = 0;
    struct Cell { int row, col; };

    void solve__r(std::vector<std::vector<char>>& board)
    {
        if (freeCells == 0) return;

        Cell next = nextCell(board);
        std::bitset<10> candidates = computeCandidates(board, next);

        for (int n = 1; n <= 9; ++n) {
            if (!candidates.test(n)) continue;
            board[next.row][next.col] = n + 48;
            --freeCells;
            solve__r(board);
            if (freeCells == 0) return;
            board[next.row][next.col] = '.';
            ++freeCells;
        }
    }

    Cell nextCell(const std::vector<std::vector<char>>& board)
    {
        int min = INT_MAX;
        Cell cell;
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (isdigit(board[row][col])) continue;
                std::bitset<10> candidates = computeCandidates(board, {row, col});
                int count = 0;
                for (int i = 1; i <= 9; ++i) {
                    if (candidates.test(i)) ++count;
                }
                if (count < min) {
                    min = count;
                    cell = {row, col};
                }
            }
        }
        return cell;
    }

    std::bitset<10>
    computeCandidates(const std::vector<std::vector<char>>& board, const Cell& next)
    {
        std::bitset<10> candidates;
        candidates.set();
        for (int col = 0; col < 9; ++col) {
            char c = board[next.row][col];
            if (isdigit(c)) candidates.reset(c - 48);
        }
        for (int row = 0; row < 9; ++row) {
            char c = board[row][next.col];
            if (isdigit(c)) candidates.reset(c - 48);
        }
        for (int row = (next.row/3) * 3; row < (next.row/3 + 1) * 3; ++row) {
            for (int col = (next.col/3) * 3; col < (next.col/3 + 1) * 3; ++col) {
                char c = board[row][col];
                if (isdigit(c)) candidates.reset(c - 48);
            }
        }

        return candidates;
    }
};

template<typename T>
void print_matrix(std::ostream& os, std::vector<std::vector<T>> const& M)
{
    for (const std::vector<T>& row : M) {
        for (const T& x : row) os << x << ' ';
        os << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, const std::vector<char>& V)
{
    os << '[';
    if (V.size() > 0) {
        for (auto it = V.cbegin(); it != V.cend() - 1; ++it) os << *it << ',';
        os << V.back();
    }
    return os << ']';
}

void test(std::vector<std::vector<char>> board)
{
    static Solution instance;
    print_matrix(std::cout, board);
    std::cout << "solution:" << std::endl;
    if (!instance.solveSudoku(board)) std::cout << "not possible" << std::endl;
    else print_matrix(std::cout, board);
}

int main()
{
    test({{'5','3','.','.','7','.','.','.','.'},
          {'6','.','.','1','9','5','.','.','.'},
          {'.','9','8','.','.','.','.','6','.'},
          {'8','.','.','.','6','.','.','.','3'},
          {'4','.','.','8','.','3','.','.','1'},
          {'7','.','.','.','2','.','.','.','6'},
          {'.','6','.','.','.','.','2','8','.'},
          {'.','.','.','4','1','9','.','.','5'},
          {'.','.','.','.','8','.','.','7','9'}});
    return 0;
}
