#include <iostream>
#include <queue>
#include <vector>
#include <limits>
#include "test/test.h"
#include <string>
#include <sstream>
#include <stack>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <functional>




using namespace std;
const int default_dist = -1;



bool has_visit(int val)
{
    return val != default_dist;
}


template<class T>
class maze_container_interface
{
public:
    virtual const T& top()const = 0;
    virtual void pop() = 0;
    virtual void push(T&& _Val) = 0;
    virtual void push(const T& _Val) = 0;
    virtual  bool empty() const = 0;
};




template<class T>
class maze_container_stack :public maze_container_interface<T>
{
public:
    using container_type = std::stack<T>;
public:
    const T& top()const override {
        return container.top();
    }
    void pop() override {
        container.pop();
    }
    void push(T&& _Val)
        override {
        container.push(std::forward<T>(_Val));
    }
    void push(const T& _Val) override {
        container.push(_Val);
    }
    bool empty() const override {
        return container.empty();
    }
private:
    container_type container;
};


template<class T>
class maze_container_queue :public maze_container_interface<T>
{
public:
    using container_type = std::queue<T>;
public:
    const T& top()const override {
        return container.front();
    }
    void pop() override {
        container.pop();
    }
    void push(T&& _Val)
        override {
        container.push(std::forward<T>(_Val));
    }
    void push(const T& _Val) override {
        container.push(_Val);
    }
    bool empty() const override {
        return container.empty();
    }
private:
    container_type container;
};
using result_pair_type = pair<int, int>;
using maze_container_ptr = std::shared_ptr<maze_container_interface<result_pair_type>>;


class MazeDirect
{
public:
    using func_type= std::function<void(int, int)>;
    using limit_func_type = std::function<bool(int, int)>;
    using break_func_type = std::function<bool(int, int)>;

public:
    static void solve(int cur_x, int cur_y, func_type func, limit_func_type limit_func, break_func_type break_func)
    {
        for (auto& [dx,dy]: directs)
        {
            int newX = cur_x + dx;
            int newY = cur_y + dy;
            if (limit_func && !limit_func(newX, newY))
                continue;
            if (func)
                func(newX, newY);
            if (break_func(newX, newY))
                break;
        }
    }



private : 
    inline static vector<result_pair_type> directs{{0,-1},{1,0 },{0,1},{-1,0}};
};

void show_route(const vector<vector<int>>& dists, int startX, int startY, int endX, int endY)
{
    int cur_x = endX;
    int cur_y = endY;
    int cur_value = dists[cur_x][cur_y];

    vector<pair<int, int>> route;
    route.resize(cur_value + 1);
    route[cur_value] = (make_pair(cur_x, cur_y));

    int dx[] = { 0, 1, 0, -1 };
    int dy[] = { -1, 0, 1, 0 };

    while (!(cur_x == startX && cur_y == startY)) {
        for (int i = 0; i < 4; ++i) {
            int newX = cur_x + dx[i];
            int newY = cur_y + dy[i];
            if (newX < 0 || newY < 0)
                continue;
            if (cur_value == dists[newX][newY] + 1) {
                cur_x = newX;
                cur_y = newY;
                cur_value = dists[cur_x][cur_y];
                route[cur_value] = (make_pair(cur_x, cur_y));

                break;
            }
        }
    }
    cout << "可用路径如下：" << endl;
    print(route);
}



class MazeRoute
{
public:
    MazeRoute(maze_container_ptr _container) {
        Reset(_container);
    };
    int Cal(const vector<vector<int>>& maze, int startX, int startY, int endX, int endY) {
        if (maze.empty() || !container)
            return -1;
        size_t MAX_X = maze.size();
        size_t MAX_Y = maze.front().size();
        dist.assign(MAX_X, vector<int>(MAX_Y, default_dist));
        container->push({ startX, startY });

        dist[startX][startY] = 0;

        int dx[] = { 0,1,0,-1 };
        int dy[] = { -1,0,1,0 };

        while (!container->empty()) {
            auto [x, y] = container->top();
            container->pop();

            if (x == endX && y == endY) {
                print(dist);
                show_route(dist, startX, startY, endX, endY);
                return dist[x][y];
            }

            for (int i = 0; i < 4; ++i) {
                int newX = x + dx[i];
                int newY = y + dy[i];

                if (newX >= 0 && newX < MAX_X && newY >= 0 && newY < MAX_Y && !has_visit(dist[newX][newY]) && maze[newX][newY] == 1) {
                    container->push({ newX, newY });
                    dist[newX][newY] = dist[x][y] + 1;
                }
            }
        }
        cout << "算法-失败\n";
        print(dist);
        return -1;
    }
    void Reset(maze_container_ptr _container) {
        container = _container;
        dist.clear();
    }
private:
    maze_container_ptr container;
    vector<vector<int>> dist;
};






bool get_org_maze(vector<vector<int>>& maze, int& startX, int& startY, int& endX, int& endY)
{
    std::filesystem::path current_dir = std::filesystem::current_path() / "maze.txt";
    // 打开文件
    std::ifstream file(current_dir);
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return false;
    }

    // 读取文件内容到 stringstream
    std::stringstream buffer;
    buffer << file.rdbuf();

    // 关闭文件
    file.close();

    int MAX_X = -1;
    int MAX_Y = -1;

    buffer >> MAX_X >> MAX_Y >> startX >> startY >> endX >> endY;
    maze.resize(MAX_X, vector<int>(MAX_Y, 0));

    for (int i = 0; i < MAX_X; ++i) {
        for (int j = 0; j < MAX_Y; ++j) {
            buffer >> maze[i][j];
        }
    }
    cout << "原始矩阵：\n";
    print(maze);
    cout << "原始矩阵显示完毕\n";

    return true;
}


void test_maze() {
    vector<vector<int>> maze;
    int startX = -1;
    int startY = -1;
    int endX = -1;
    int endY = -1;
    if (!get_org_maze(maze, startX, startY, endX, endY))
        return;

    cout << "广度优先" << endl;
    auto queue_maze = std::make_shared < maze_container_queue<result_pair_type>>();
    MazeRoute maze_route(queue_maze);
    int result = maze_route.Cal(maze, startX, startY, endX, endY);

    cout << "深度优先" << endl;
    auto stack_maze = std::make_shared< maze_container_stack<result_pair_type>>();
    maze_route.Reset(stack_maze);
    result = maze_route.Cal(maze, startX, startY, endX, endY);

}
