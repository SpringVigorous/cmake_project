#include "test/test.h"
#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <sstream>
#include <stack>
#include <fstream>
#include <filesystem>
#include <format>

using namespace std;

const int N = 80;
vector<vector<int>> maze(N, vector<int>(N, 0));
vector<pair<int, int>> dir = {{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

void dfs(int x, int y) {
    maze[x][y] = 1;

    for (auto d : dir) {
        int nx = x + d.first;
        int ny = y + d.second;

        if (nx >= 0 && nx < N && ny >= 0 && ny < N && maze[nx][ny] == 0) {
            dfs(nx, ny);
        }
    }
}

void test_create_maze()
{
    srand(time(0));
    int start_x, start_y;

    while (true) {
        start_x = rand() % N;
        start_y = rand() % N;
        if (maze[start_x][start_y] == 0) {
            break;
        }
    }

    dfs(start_x, start_y);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }

    std::filesystem::path current_dir = std::filesystem::current_path() / "maze.txt";
    // 打开文件
    std::ofstream file(current_dir, std::ios::out);
    if (!file.is_open())
    {
        std::cerr << "无法打开文件" << std::endl;
        return false;
    }
    //count_x 、 count_y 、 startX 、 startY 、 endX 、 endY;

    file<< std::format("{0} {1} {2} {3} {4}\n", N, N, start_x, start_y, N-1, N-1);
    //maze输出到file中
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file<<maze[i][j] << " ";
        }
        file<<endl;
    }
    // 关闭文件
    file.close();
}
