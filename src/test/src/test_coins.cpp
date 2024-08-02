#include <vector>
#include <climits>

int minCoins(std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0; // base case
    
    for(int i = 1; i <= amount; ++i) {
        for(int j = 0; j < coins.size(); ++j) {
            if(coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                dp[i] = std::min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }
    
    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int main() {
    std::vector<int> coins = {1, 2, 5};
    int amount = 11;
    std::cout << "Minimum number of coins required: " << minCoins(coins, amount) << std::endl;
    return 0;
}
