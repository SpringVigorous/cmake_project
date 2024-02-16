#include <iostream>
#include <vector>
#include <algorithm>
#include "test/test.h"
#include <string>
#include <sstream>
#include <format>

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

void test_package_0_1_2()
{
    int maxWeight = 59;
    vector<int> values = { 60,30, 80, 120, 150 };

    vector<int> weights = { 10,5,  15, 20, 30 };

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
