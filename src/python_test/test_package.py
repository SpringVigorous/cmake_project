# dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i])
def zero_one_knapsack(weights, values, capacity):
    n = len(weights)
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(1, capacity + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1])
            else:
                dp[i][w] = dp[i - 1][w]

    # 返回最后一行最后一列的值，即最大价值
    # dp_str=[str(i) for i in dp]
    with open("one_knapsack_dp.txt", "w") as f:
        f.write("\n".join(["\t".join(map(str, i)) for i in dp]))
    return dp[-1][-1]


#d[i]=max(d[i],d[i-w[j]]+v[j])
def unbounded_knapsack(weights, values, capacity):
    n = len(weights)
    dp = [0 for _ in range(capacity + 1)]

    for i in range(n):
        for w in range(weights[i], capacity + 1):
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i])
    with open("unbounded_knapsack.txt", "w") as f:
        f.write("\t".join(map(str, dp)) )
    
    result=dp[-1]
    all_capacity=capacity
    min_wight=min(weights)
    sel_list=[]
    while(capacity>=min_wight):
        success=False
        for i in range(n):
            cur_val=values[i]
            cur_wight=weights[i]
            if cur_wight>capacity:
                break
            if result-cur_val==dp[capacity-cur_wight]:
                sel_list.append(cur_wight)
                capacity-=cur_wight
                result-=cur_val
                success=True
                continue
        if not success:
            break
    # 返回最后一列的值，即最大价值
    return dp[-1],sel_list,sum(sel_list),f"all:{all_capacity},rest:{capacity}"

#d[i][j]=max(d[i][j],d[i-w[j]]+v[j])
def complete_knapsack(weight, value, capacity):
    n = len(weight)
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]

    # 动态规划填充dp数组
    for i in range(1, n + 1):
        for j in range(capacity + 1):
            dp[i][j] = dp[i - 1][j]
            if weight[i - 1] <= j:
                dp[i][j] = max(dp[i][j], dp[i][j - weight[i - 1]] + value[i - 1])

    # 输出dp数组
    for row in dp:
        print('\t'.join(map(str, row)))
        
    with open("complete_knapsack.txt", "w") as f:
        f.write( "\n".join( ["\t".join(map(str, i)) for i in dp] ))
        
    


weights = [2, 3, 4,6,7,9]
values = [15,22,31,16,52,68]

for i in range(31, 32):
    capacity = i



    # print("Maximum value:", zero_one_knapsack(weights, values, capacity))
    print("Maximum value:", unbounded_knapsack(weights, values, capacity))
    # print("Maximum value:", complete_knapsack(weights, values, capacity))
