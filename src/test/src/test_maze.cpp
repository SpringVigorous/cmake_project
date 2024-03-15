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

template <class T>
class maze_container_interface
{
public:
    virtual const T& top() const = 0;
    virtual void pop() = 0;
    virtual void push(T&& _Val) = 0;
    virtual void push(const T& _Val) = 0;
    virtual bool empty() const = 0;
};

template <class T>
class maze_container_stack : public maze_container_interface<T>
{
public:
    using container_type = std::stack<T>;

public:
    const T& top() const override
    {
        return container.top();
    }
    void pop() override
    {
        container.pop();
    }
    void push(T&& _Val) override
    {
        container.push(std::forward<T>(_Val));
    }
    void push(const T& _Val) override
    {
        container.push(_Val);
    }
    bool empty() const override
    {
        return container.empty();
    }

private:
    container_type container;
};

template <class T>
class maze_container_queue : public maze_container_interface<T>
{
public:
    using container_type = std::queue<T>;

public:
    const T& top() const override
    {
        return container.front();
    }
    void pop() override
    {
        container.pop();
    }
    void push(T&& _Val)
        override
    {
        container.push(std::forward<T>(_Val));
    }
    void push(const T& _Val) override
    {
        container.push(_Val);
    }
    bool empty() const override
    {
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
    using body_func_type = std::function<void(int, int)>;
    using limit_func_type = std::function<bool(int, int)>;

public:
    static void loop(int cur_x, int cur_y, body_func_type body_func, limit_func_type limit_func, limit_func_type break_func)
    {
        for (const auto& [dx, dy] : directs)
        {
            int newX = cur_x + dx;
            int newY = cur_y + dy;
            if (limit_func && !limit_func(newX, newY))
                continue;
            if (body_func)
                body_func(newX, newY);
            if (break_func && break_func(newX, newY))
                break;
        }
    }

private:
    inline static vector<result_pair_type> directs{ {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
};
bool check_index_valid(int x, int y, int count_x, int count_y)
{
    return x >= 0 && x < count_x && y >= 0 && y < count_y;
}
void show_route(const vector<vector<int>>& dists, int startX, int startY, int endX, int endY)
{
    if (dists.empty())
        return;
    size_t count_x = dists.size();
    size_t count_y = dists.front().size();
    auto check_index = [=](int x, int y)
        {
            return check_index_valid(x, y, count_x, count_y);
        };
    if (!check_index(startX, startY) || !check_index(endX, endY))
        return;

    int cur_x = -1, cur_y = -1, cur_value = -1;

    vector<pair<int, int>> route;
    route.resize(dists[endX][endY] + 1);

    auto set_data = [&](int x, int y)
        {
            cur_x = x;
            cur_y = y;
            cur_value = dists[cur_x][cur_y];
            route[cur_value] = make_pair(cur_x, cur_y);
        };
    set_data(endX, endY);
    while (cur_x != startX || cur_y != startY)
    {

        MazeDirect::loop(cur_x, cur_y, nullptr, check_index, [&](int x, int y)
            {
                if (dists[x][y] == cur_value - 1)
                {
                    set_data(x, y);
                    return true;
                }
                return false;
            });
    }
    cout << std::format("可用路径共【{}】步，详情如下：", route.size()) << endl;
    print(route);
}

class MazeRoute
{
public:
    MazeRoute(maze_container_ptr _container)
    {
        Reset(_container);
    };
    int Cal(const vector<vector<int>>& maze, int startX, int startY, int endX, int endY)
    {
        if (maze.empty() || !container)
            return -1;
        size_t count_x = maze.size();
        size_t count_y = maze.front().size();
        dist.assign(count_x, vector<int>(count_y, default_dist));
        container->push({ startX, startY });

        dist[startX][startY] = 0;

        while (!container->empty())
        {
            auto [x, y] = container->top();
            container->pop();

            if (x == endX && y == endY)
            {
                print(dist);
                show_route(dist, startX, startY, endX, endY);
                return dist[x][y];
            }

            MazeDirect::loop(
                x, y,
                [&](int newX, int newY)
                {
                    container->push({ newX, newY });
                    dist[newX][newY] = dist[x][y] + 1; },
                [&](int newX, int newY)
                { return check_index_valid(newX, newY, count_x, count_y) && !has_visit(dist[newX][newY]) && maze[newX][newY] == 1; },
                nullptr);
        }
        cout << "算法-失败\n";
        print(dist);
        return -1;
    }
    void Reset(maze_container_ptr _container)
    {
        container = _container;
        dist.clear();
    }

private:
    maze_container_ptr container;
    vector<vector<int>> dist;
};

bool get_org_maze(vector<vector<int>>& maze, int& startX, int& startY, int& endX, int& endY)
{
    //count_x 、 count_y 、 startX 、 startY 、 endX 、 endY;
    std::filesystem::path current_dir = std::filesystem::current_path() / "maze.txt";
    // 打开文件
    std::ifstream file(current_dir);
    if (!file.is_open())
    {
        std::cerr << "无法打开文件" << std::endl;
        return false;
    }

    // 读取文件内容到 stringstream
    std::stringstream buffer;
    buffer << file.rdbuf();

    // 关闭文件
    file.close();

    int count_x = -1;
    int count_y = -1;

    buffer >> count_x >> count_y >> startX >> startY >> endX >> endY;
    maze.resize(count_x, vector<int>(count_y, 0));

    for (int i = 0; i < count_x; ++i)
    {
        for (int j = 0; j < count_y; ++j)
        {
            buffer >> maze[i][j];
        }
    }
    cout << std::format("原始矩阵({},{})-({},{})：\n",startX,startY,endX,endY);
    print(maze);
    cout << "原始矩阵显示完毕\n";

    return true;
}

void test_maze()
{
    vector<vector<int>> maze;
    int startX = -1;
    int startY = -1;
    int endX = -1;
    int endY = -1;
    if (!get_org_maze(maze, startX, startY, endX, endY))
        return;

    cout << "广度优先" << endl;
    auto queue_maze = std::make_shared<maze_container_queue<result_pair_type>>();
    MazeRoute maze_route(queue_maze);
    int result = maze_route.Cal(maze, startX, startY, endX, endY);

    cout << "深度优先" << endl;
    auto stack_maze = std::make_shared<maze_container_stack<result_pair_type>>();
    maze_route.Reset(stack_maze);
    result = maze_route.Cal(maze, startX, startY, endX, endY);
}
