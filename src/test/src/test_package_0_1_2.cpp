#include <iostream>
#include <vector>
#include <algorithm>
#include "test/test.h"
#include <string>
#include <sstream>
#include <format>


#include <functional>
#include <numeric>

using namespace std;

class Packaging
{
public:
    Packaging(int maxWeight, const vector<int>& values, const vector<int>& weights, bool is_whole = true)
        : maxWeight_(maxWeight), values_(values), weights_(weights), dp(values.size() + 1, vector<int>(maxWeight + 1, 0)), is_whole_(is_whole) {
        calulate();
    }

public:
    void calulate()
    {
        for (int i = 1; i <= values_.size(); ++i)
        {
            auto cur_weight = weights_[i - 1];
            auto cur_val = values_[i - 1];

            for (int j = 1; j <= maxWeight_; ++j)
            {
                auto pre_val = dp[i - 1][j];
                if (j >= cur_weight)
                {
                    int direct = is_whole_ ? 0 : 1;//完全背包是当前行，0-1背包是上一行
                    dp[i][j] = max(pre_val, dp[i - direct][j - cur_weight] + cur_val);
                }
                else
                {
                    dp[i][j] = pre_val;
                }
            }
        }
    }
    int maxValue()
    {

        return dp[values_.size()][maxWeight_];
    }

    vector<int> selectedItems() const
    {
        vector<int> result;
        int weight = maxWeight_;

        for (int i = values_.size(); i > 0; /*--i*/)
        {
            bool is_decrease = !is_whole_;
            if (dp[i][weight] != dp[i - 1][weight])
            {
                result.push_back(i - 1);
                weight -= weights_[i - 1];
            }
            else if (!is_decrease)
            {
                is_decrease = true;
            }

            if (is_decrease)
                --i;
        }

        reverse(result.begin(), result.end());
        return result;
    }

    void print() const
    {
        std::stringstream stream;
        stream << "二维数组如下：\n";

        auto print_val = [&stream](auto val)
            {
                stream << val << ",";
            };

        print_val(0);
        for (size_t i = 0; i < maxWeight_ + 1; ++i)
        {
            print_val(i);
        }
        stream << "\n";

        for (size_t i = 0; i < dp.size(); ++i)
        {
            const auto& item = dp[i];
            if (i == 0)
            {
                print_val(i);
            }
            else
            {
                stream << std::format("{}:({}-{}),", i, weights_[i - 1], values_[i - 1]);
            }

            for (auto val : item)
            {
                print_val(val);
            }
            stream << "\n";
        }
        cout << stream.str();
    }

private:
    int maxWeight_;
    vector<int> values_;
    vector<int> weights_;
    vector<vector<int, allocator<int>>> dp;


    //true：完全背包问题  false:0-1背包问题
    bool is_whole_{ false };

};



int zero_one_knapsack(int capacity, std::vector<int> &w, std::vector<int> &v) {
    int n = w.size();
    std::vector<std::vector<int>> dp(n, std::vector<int>(capacity + 1, -1));

    function<int(int, int)> dfs = [&](int i, int c) {
        if (i < 0)
            return 0;
        if (dp[i][c] != -1)
            return dp[i][c];
        if (c < w[i])
            return dfs(i - 1, c);
        return dp[i][c] = max(dfs(i - 1, c), dfs(i - 1, c - w[i]) + v[i]);
    };
    auto val= dfs(n - 1, capacity);
    return val;
}

class Solution {
public:
    static int findTargetSumWays(std::vector<int>& nums, int target) {
        // 计算总和并调整目标值
        target += std::accumulate(nums.begin(), nums.end(), 0);
        if (target < 0 || target % 2) return 0;
        target /= 2;

        // 初始化 dp 数组，大小为 target + 1，因为下标范围从 0 到 target
        std::vector<int> dp(target + 1, 0);
        dp[0] = 1;

        for (int num : nums) {
            // 更新 dp 数组，注意这里是从 target 开始遍历到 num（含）
            for (int k = target; k >= num; --k) {
                dp[k] += dp[k - num];
            }
        }
        return dp[target];
    }
};
class Solution1 {
public:
    static int findTargetSumWays(vector<int>& nums, int target) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        target += sum;
        if (target < 0 || target % 2 == 1) return 0;
        target /= 2;

        int n = nums.size();
        vector<vector<int>> f(n + 1, vector<int>(target + 1, 0));
        f[0][0] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= target; ++j) {
                if (j < nums[i]) f[i + 1][j] = f[i][j];
                else f[i + 1][j] = f[i][j] + f[i][j - nums[i]];
            }
        }

        cout << "\n数组如下：\n";
        for (const auto& items:f)
        {
            for (auto val : items)
                cout << val << ",";
            cout<< endl;
        }
        cout << endl;

        return f[n][target];
    }
};
class Solution2 {
public:
   static int coinChange(vector<int> &coins, int amount) {
       int n = coins.size();
       vector<vector<int>> cache(n ,vector<int>(amount + 1,-1)); // -1 表示没用访问过
        function<int(int, int)> dfs = [&](int i, int c) -> int {
            if (i < 0) return c == 0 ? 0 : INT_MAX / 2; // 除 2 是防止下面 + 1 溢出
            int &res = cache[i][c];
            if (res != -1) return res;
            if (c < coins[i]) return res = dfs(i - 1, c);
            return res = min(dfs(i - 1, c), dfs(i, c - coins[i]) + 1);
        };
        int ans = dfs(n - 1, amount);
        return ans < INT_MAX / 2 ? ans : -1;
    }
};


void test_package_0_1_2()
{
vector<int>coins{1,5,10,50,100,200,500,1000};
    cout << "金额754:" << Solution2::coinChange(coins, 754) << endl;

    int maxWeight = 59;
    vector<int> values = { 60,30, 80, 120, 150 };

    vector<int> weights = { 10,5,  15, 20, 30 };


    cout << "承重60:" << Solution::findTargetSumWays(weights, 60) << endl;
    cout<<"承重60:"<<Solution1::findTargetSumWays(weights,60)<<endl;


    cout<<"比对结果:"<<zero_one_knapsack(maxWeight, weights, values)<<endl;
    Packaging packaging(maxWeight, values, weights,false);
    cout << "\n最大价值: " << packaging.maxValue() << endl;
    packaging.print();
    vector<int> selectedItems = packaging.selectedItems();
    cout << "选取的物品:";
    for (int item : selectedItems)
    {
        cout << item << " ";
    }
    cout << "\n\n";
}
