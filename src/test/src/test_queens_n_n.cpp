#include <test/test.h>

#include <iostream>
#include <vector>
#include <algorithm>
#include <format>

/**
 * @brief Check if a position on the board is valid for a queen.
 * 
 * @param board The board on which the queen is placed.
 * @param row The row number of the position.
 * @param col The column number of the position.
 * @return true if the position is valid, false otherwise.
 */
bool is_valid(const std::vector<std::vector<int>>& board, int row, int col) {
    for (int i = 0; i < row; ++i) {
        if (board[i][col] || board[row][i]) {
            return false;
        }
    }

    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j]) {
            return false;
        }
    }

    for (int i = row - 1, j = col + 1; i >= 0 && j < board.size(); --i, ++j) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

inline static int count = 0;

/**
 * @brief Recursive function to solve the N-Queens problem.
 * 
 * @param board The board on which the queens are placed.
 * @param row The current row number being considered.
 */
void solve_n_queens(std::vector<std::vector<int>>& board, int row) {
    if (row == board.size()) {
        std::cout << std::format("解决方案-[{}]:\n", ++count);
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[i].size(); ++j) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        return;
    }

    for (int col = 0; col < board[row].size(); ++col) {
        if (is_valid(board, row, col)) {
            board[row][col] = 1;
            solve_n_queens(board, row + 1);
            board[row][col] = 0;
        }
    }
}

using namespace std;

/**
 * @brief Test function for the N-Queens problem.
 */
void test_queens_n_n() {
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;

    std::vector<std::vector<int>> board(N, std::vector<int>(N, 0));
    solve_n_queens(board, 0);
}