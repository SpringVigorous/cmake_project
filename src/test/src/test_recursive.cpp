// vivo2020届春季校园招聘在线编程考试_现给定任意正整数 n，请寻找并输出最小的正整数 m（m>9），使得 m 的各位（个位、十位、百位 ... ...）之乘积等于n，若不存在则输出 -1
// https://blog.csdn.net/baihehaitangyijiu/article/details/105604561

#include <vector>
#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>
#include "test/test.h"
#include <sstream>
#include <xutility>
#include <deque>
using namespace std;
int greate_ten_num(int dest_val)
{
    if (dest_val < 10)
    {
        dest_val += 10;
    }
    return dest_val;
};
int to_greate_ten_num(const deque<int>& val)
{
    int dest_val = 0;
    int count = val.size();
    for (size_t i = 0; i < count; ++i)
        dest_val += val[i] * std::pow(10, count - i - 1);
    return greate_ten_num(dest_val);
};
bool solve_imp(deque<int>& stream, int cap)
{
    std::vector<int> vals{ 9, 8, 7, 6, 5, 4, 3, 2 };
    for (auto val : vals)
    {
        if (cap % val != 0)
        {
            continue;
        }
        do
        {
            cap /= val;
            stream.push_front(val);
        } while (cap % val == 0);
    }
    return cap == 1;
}
int solve(int cap)
{
    if (cap < 0)
        return -1;
    else if (cap < 9)
        return greate_ten_num(cap);
    deque<int> dest_vec;
    if (!solve_imp(dest_vec, cap))
        return -1;
    return to_greate_ten_num(dest_vec);
}
void test_recursive()
{
    for (int i = -2; i < 1200; ++i)
    {
        cout << i << ":" << solve(i) << endl;
    }
}
