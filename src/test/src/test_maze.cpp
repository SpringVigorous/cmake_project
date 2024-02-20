#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include "test/test.h"
#include <string>
#include <sstream>
#include <stack>

using namespace std;

 int MAX_X = 100;
 int MAX_Y = 100;
const int INF = numeric_limits<int>::max();

vector<vector<int>> maze;
int startX, startY;
int endX, endY;

int bfs() {
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(MAX_X, vector<bool>(MAX_Y, false));
    vector<vector<int>> dist(MAX_X, vector<int>(MAX_Y, INF));

    q.push({startX, startY});
    visited[startX][startY] = true;
    dist[startX][startY] = 0;

    int dx[] = {0,1,0,-1};
    int dy[] = {-1,0,1,0};
    cout << "bfs：算法\n";

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == endX && y == endY) {
            print(dist);

            return dist[x][y];
        }

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < MAX_X && newY >= 0 && newY < MAX_Y && !visited[newX][newY] && maze[newX][newY] == 1) {
                q.push({newX, newY});
                visited[newX][newY] = true;
                dist[newX][newY] = dist[x][y] + 1;
            }
        }
    }

    return -1;
}
int dfs() {
    stack<pair<int, int>> q;
    vector<vector<bool>> visited(MAX_X, vector<bool>(MAX_Y, false));
    vector<vector<int>> dist(MAX_X, vector<int>(MAX_Y, INF));

    q.push({ startX, startY });
    visited[startX][startY] = true;
    dist[startX][startY] = 0;

    int dx[] = { -1, 0, 1, 0 };
    int dy[] = { 0, 1, 0, -1 };
    cout << "bfs：算法\n";

    while (!q.empty()) {
        auto [x, y] = q.top();
        q.pop();

        if (x == endX && y == endY) {
            print(dist);

            return dist[x][y];
        }

        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < MAX_X && newY >= 0 && newY < MAX_Y && !visited[newX][newY] && maze[newX][newY] == 1) {
                q.push({ newX, newY });
                visited[newX][newY] = true;
                dist[newX][newY] = dist[x][y] + 1;
            }
        }
    }

    return -1;
}

void test_maze(){

    string test_str = R"(
        22 22 6 1 20 20
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 1 1 1 0 0 1 1 1 1 1 1 1 1 1 0 1 0 0 1 0 0
0 1 0 1 0 0 0 0 0 1 0 0 0 1 0 0 1 0 0 1 0 0
0 1 0 1 0 0 0 0 0 1 0 0 0 1 0 0 1 1 1 1 0 0
0 1 1 1 1 1 1 0 0 1 1 1 1 1 0 0 1 0 0 0 0 0
0 1 0 0 0 0 1 0 0 1 0 0 0 1 1 1 1 1 1 1 1 0
0 1 1 0 1 1 1 1 1 1 0 0 0 1 0 0 1 0 0 0 1 0
0 0 0 0 1 0 1 0 0 0 0 0 0 1 0 0 1 0 0 0 1 0
0 1 0 0 1 0 1 0 1 1 1 1 1 1 0 0 1 1 1 1 1 0
0 1 1 1 1 1 1 0 0 0 0 0 0 1 0 0 1 0 1 0 1 0
0 1 0 1 0 0 1 1 1 1 1 1 1 1 0 0 1 0 1 0 1 0
0 0 0 1 0 0 1 0 0 0 0 0 0 1 0 0 1 0 1 0 1 0
0 1 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 0 1 1 1 1 0
0 1 0 0 0 0 1 0 1 0 1 0 1 0 1 0 0 0 1 0 1 0
0 1 0 1 1 1 1 0 1 0 1 0 1 0 1 1 1 0 1 0 1 0
0 1 0 1 0 0 1 0 1 0 1 0 1 0 0 0 1 0 1 0 1 0
0 1 0 1 0 0 0 0 1 0 1 0 1 0 0 0 1 0 1 0 1 0
0 1 0 1 1 1 1 1 1 0 1 0 1 0 0 0 1 0 1 1 1 0
0 1 0 0 0 1 0 0 0 0 0 0 1 0 0 0 1 0 1 0 1 0
0 1 1 1 1 1 1 1 1 1 0 1 1 1 1 1 1 1 1 0 1 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
        )";

    stringstream test_stream(test_str);

    test_stream >> MAX_X>>MAX_Y>> startX >> startY >> endX >> endY;
    maze.resize(MAX_X, vector<int>(MAX_Y, 0));

    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            char c;
            test_stream >> c;
            maze[i][j] = c == '1' ? 1 : 0;
        }
    }
    cout << "原始矩阵：\n";
    print(maze);
    cout << "原始矩阵显示完毕\n";


    int result = bfs();
    if (result == -1) {
        cout << "No path found." << endl;
    } else {
        cout << "Shortest path length: " << result << endl;
    }

    result = dfs();
    if (result == -1) {
        cout << "No path found." << endl;
    }
    else {
        cout << "Shortest path length: " << result << endl;
    }


}
