#include "test/test.h"
#include <iostream>
#include <vector>
#include <format>

class QueenN {
public:
    using TempType = std::vector<int>;
private:
    TempType board; // 用于存储皇后的列位置

    std::vector<TempType> results;


    // 辅助函数：检查当前位置放置皇后是否冲突
    bool isSafe(int row, int col) {
        for (int i = 0; i < row; ++i) {
            if (board[i] == col || // 列冲突
                abs(board[i] - col) == abs(row - i)) { // 对角线冲突
                return false;
            }
        }
        return true;
    }

    // 使用深度优先搜索放置皇后
    bool solveNQueensHelper(int row) {
        if (row == board.size()) {
            results.emplace_back(board);
            return true;
        }

        for (int col = 0; col < board.size(); ++col) {
            if (isSafe(row, col)) {
                board[row] = col;
                if (solveNQueensHelper(row + 1)) {
                    board[row] = -1; // 清除当前行的尝试
                    //return true;
                }
                // 如果当前位置无法放置皇后，则回溯
                //board[row] = -1; // 清除当前行的尝试
            }
        }
        return !results.empty(); // 当前行没有找到合适的位置放置皇后
    }



    // 打印当前的解决方案
    void printSolution(size_t index, const TempType& board)const {
        std::cout << std::format("第{}个解决方案：\n", index);
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board.size(); ++j) {
                if (j == board[i]) {
                    std::cout << "1";
                }
                else {
                    std::cout << "0";
                }
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    void print()const
    {
        size_t i = 0;
        for (const auto& board : results)
        {
            printSolution(++i, board);
        }
    }
    void print_count()const
    {
        std::cout << std::format("{}皇后问题，总共有{}个解决方案：\n\n", board.size(), results.size());
    }

public:
    // 构造函数初始化棋盘大小
    QueenN(int size) : board(size, -1) {}

    // 解决N皇后问题
    void solveNQueens() {
        if (!solveNQueensHelper(0)) {
            std::cout << std::format("No solution exists for {} Queens problem.\n", board.size());
        }

        print_count();

        print();

    }
};

void test_queens_n() {
    using namespace std;
    int N;
    cout << "Enter the number of queens: ";
    cin >> N;

    QueenN queenSolver(N);
    queenSolver.solveNQueens();

}