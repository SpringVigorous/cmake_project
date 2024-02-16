#include "test/test.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <xutility>


using namespace std;
//已整理到test_package_whole_1.cpp, 本文可以废弃掉
class Packaging_0_1
{
public:
    Packaging_0_1(int maxWeight, const vector<int> &values, const vector<int> &weights)
        : maxWeight_(maxWeight), values_(values), weights_(weights), dp(maxWeight + 1, 0)
    {
        calulate();
    }
    void calulate()
    {
        for (int i = 0; i < values_.size(); ++i)
        {
            for (int j = maxWeight_; j >= weights_[i]; --j)
            {
                auto val = dp[j - weights_[i]] + values_[i];
                if (dp[j] <val)
                {
                    dp[j] = val;
                }

            }
        }
    }

    int maxValue() const
    {
        return dp[maxWeight_];
    }

    vector<int> selectedItems() const
    {
        vector<int> result;
        auto it = std::find_if(dp.rbegin(), dp.rend(), [this](int val)
                               { return val != maxValue(); });
        if (it == dp.rend())
            return result;
        int weight = std::distance(dp.begin(), it.base());
        for (int i = values_.size(); i > 0; --i)
        {
            if (weight == 0)
                break;
            int index = weight - weights_[i - 1];
            if (index > -1 && dp[weight] == dp[index] + values_[i - 1])
            {
                result.push_back(i - 1);
                weight -= weights_[i - 1];
            }
        }
        reverse(result.begin(), result.end());
        return result;
    }

    void print() const
    {
        cout << "数组如下：\n";
        for (size_t i = 0; i < dp.size(); ++i)
            cout << i << "," << dp[i] << endl;
    }

private:
    int maxWeight_;
    vector<int> values_;
    vector<int> weights_;
    vector<int> dp;
    int max_value{};
};

void test_package_0_1()
{
    int maxWeight = 59;
    vector<int> values = { 60,30, 80, 120, 150 };

    vector<int> weights = { 10,5,  15, 20, 30 };

    Packaging_0_1 packaging(maxWeight, values, weights);
    cout << "\n最大价值: " << packaging.maxValue() << endl;
    vector<int> selectedItems = packaging.selectedItems();
    cout << "选取的物品: ";
    for (int item : selectedItems)
    {
        cout << item << " ";
    }
    cout << endl;
    packaging.print();
    cout << endl;
}