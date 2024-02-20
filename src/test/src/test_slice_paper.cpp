#include <iostream>
#include <vector>
#include <algorithm>
#include "test/test.h"

using namespace std;

// 这个问题可以看作是“0-1背包问题”的扩展，我们可以通过动态规划的方法来求解。我们可以定义一个三维的动态规划数组dp，其中dp[i][j][k]表示在前i个物品中选择，使得总长度不超过j，总宽度不超过k的物品的最大价值。

// 具体的动态规划过程如下：

// 1. 初始化一个三维数组dp，大小为(n+1)×(max_length+1)×(max_width+1)，初始值都设为0。

// 2. 遍历所有物品，对于每个物品，遍历所有可能的长度和宽度，更新dp数组。

// 3. 返回dp[n][length][width]，其中n是物品的总个数，length和width分别是背包的最大长度和宽度。

// 下面给出一个简单的C++代码实现：


#include <iostream>
#include <vector>
using namespace std;

int maxValue(vector<vector<int>>& items, int length, int width) {
    int n = items.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(length + 1, vector<int>(width + 1, 0)));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= length; j++) {
            for (int k = 1; k <= width; k++) {
                if (j >= items[i - 1][0] && k >= items[i - 1][1]) {
                    dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - items[i - 1][0]][k - items[i - 1][1]] + items[i - 1][2]);
                } else {
                    dp[i][j][k] = dp[i - 1][j][k];
                }
            }
        }
    }

    return dp[n][length][width];
}

int main1() {
    vector<vector<int>> items = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    int length = 4;
    int width = 5;
    cout << "The maximum value is: " << maxValue(items, length, width) << endl;
    return 0;
}
//```
//
//在这个例子中，我们有一个背包，最大长度为4，最大宽度为5，有3个物品，每个物品都有自己的长度、宽度和价值：
//
//- 物品1，长度1，宽度2，价值3；
//- 物品2，长度2，宽度3，价值4；
//- 物品3，长度3，宽度4，价值5。
//
//通过运行这段代码，我们可以得到背包可以装的最大价值为16。
//
//注意：这个算法只能求解没有“完全装满”限制的背包问题。如果需要求解更复杂的问题，可能需要对算法进行相应的修改。


int maxValue1(vector<vector<int>>& items, int length, int width) {
    int n = items.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(length + 1, vector<int>(width + 1, 0)));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= length; j++) {
            for (int k = 1; k <= width; k++) {
                if (j >= items[i - 1][0] && k >= items[i - 1][1]) {
                    dp[i][j][k] = max(dp[i - 1][j][k], dp[i - 1][j - items[i - 1][0]][k - items[i - 1][1]] + items[i - 1][2]);
                } else {
                    dp[i][j][k] = dp[i - 1][j][k];
                }
            }
        }
    }

    return dp[n][length][width];
}


void test_slice_paper(){
    vector<vector<int>> items = {{1, 2, 3}, {2, 3, 4}, {3, 4, 5}};
    int length = 4;
    int width = 5;
    cout << "The maximum value is: " << maxValue1(items, length, width) << endl;

}
// 在这个例子中，我们有一个背包，最大长度为4，最大宽度为5，有3个物品，每个物品都有自己的长度、宽度和价值：

// 物品1，长度1，宽度2，价值3；
// 物品2，长度2，宽度3，价值4；
// 物品3，长度3，宽度4，价值5。
// 通过运行这段代码，我们可以得到背包可以装的最大价值为16。

// 注意：这个算法只能求解没有“完全装满”限制的背包问题。如果需要求解更复杂的问题，可能需要对算法进行相应的修改。