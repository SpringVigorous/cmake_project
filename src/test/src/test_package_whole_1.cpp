#include <iostream>
#include <vector>
#include "test/test.h"

using namespace std;


//d[i]=max(d[i], d[i-w[j]]+v[j]))
class PackingWhole {
public:
    PackingWhole(int maxWeight, const vector<int>& values, const vector<int>& weights, bool is_whole = true)
        : maxWeight_(maxWeight), values_(values), weights_(weights), dp(maxWeight + 1, 0), is_whole_(is_whole) {
        calulate();
    }
    void calulate()
    {
        if (is_whole_)
        {
            for (int i = 0; i < values_.size(); ++i) {
                auto cur_weight = weights_[i];
                auto cur_val = values_[i];
                //顺序，每样物品可以多次放入
                for (int j = cur_weight; j <= maxWeight_; ++j) {
                    auto val = dp[j - cur_weight] + cur_val;
                    if (dp[j] < val)
                    {
                        dp[j] = val;
                    }
                }
            }
        }
        else
        {
            for (int i = 0; i < values_.size(); ++i) {
                auto cur_weight = weights_[i];
                auto cur_val = values_[i];
                //逆序，原因是 每样物品只能用一次（否则，对于单个物品，可能重复计算）
                for (int j = maxWeight_; j >= cur_weight; --j) {
                    auto val = dp[j - cur_weight] + cur_val;
                    if (dp[j] < val)
                    {
                        dp[j] = val;
                    }
                }
            }
        }
    }

    int maxValue()const {

        return dp[maxWeight_];
    }
    void print() const
    {
        cout << "数组如下：\n";
        for (size_t i = 0; i < dp.size(); ++i)
            cout << i << "," << dp[i] << endl;
    }
    vector<int> selectedItems() const {
        vector<int> result;
        auto it = std::find_if(dp.rbegin(), dp.rend(), [this](int val)
            { return val != maxValue(); });
        if (it == dp.rend())
            return result;
        int weight = std::distance(dp.begin(), it.base());
        for (int i = values_.size(); i > 0; /*--i*/)
        {
            if (weight == 0)
                break;
            int index = weight - weights_[i - 1];


            bool is_decrease = !is_whole_;
            if (index > -1 && dp[weight] == dp[index] + values_[i - 1])
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

private:
    int maxWeight_;
    vector<int> values_;
    vector<int> weights_;
    vector<int> dp;

    //true：完全背包问题  false:0-1背包问题
    bool is_whole_{ false };
};

void test_package_whole_1() {
    int maxWeight = 59;
    vector<int> values = { 60,30, 80, 120, 150 };

    vector<int> weights = { 10,5,  15, 20, 30 };

    PackingWhole packaging(maxWeight, values, weights,false);
    cout << "最大价值: " << packaging.maxValue() << endl;
    vector<int> selectedItems = packaging.selectedItems();
    cout << "选取的物品: ";
    for (int item : selectedItems) {
        cout << item << " ";
    }
    cout << endl;
    packaging.print();


}
