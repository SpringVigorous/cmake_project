def min_coins(coins, amount):
    dp = [float('inf')] * (amount + 1)
    dp[0] = 0
    # 记录到达当前金额的上一步选择
    prev_coin = [-1] * (amount + 1)

    for i in range(1, amount + 1):
        for coin in coins:
            if i >= coin and dp[i - coin] + 1 < dp[i]:
                dp[i] = dp[i - coin] + 1
                prev_coin[i] = coin

    # 如果无法凑成目标金额，返回 -1 和空列表
    if dp[amount] == float('inf'):
        return -1, []
    
    print(amount, dp, prev_coin)
    
    # 构建硬币选择方案
    selected_coins = []
    while amount > 0:
        val=prev_coin[amount]
        selected_coins.append(val)
        amount -= val
    
    return dp[-1], selected_coins[::-1]  # 反转列表，使硬币按添加顺序排列

# 示例
coins = [1, 5,10,100]

for i in range(1,11):
    print(f"amount:{i},Minimum number of coins required:", min_coins(coins, i))