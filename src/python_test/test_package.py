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


class TreeNode:
    def __init__(self, val=0, children=None):
        self.val = val
        self.children = children if children is not None else []
    def append(self,  child):
        self.children.append(child)      
    def __str__(self) -> str:
        print(find_paths(self))
    
    def print_tree(self, prefix='', is_last=True):
        if self is not None:
            # 打印当前节点的值
            end_char = '\n'
            if self.children:
                # 如果有子节点，则打印当前节点并添加连接线
                end_char = ''
                if is_last:
                    print(prefix + "└── " + str(self.val), end=end_char)
                    prefix += "    "
                else:
                    print(prefix + "├── " + str(self.val), end=end_char)
                    prefix += "|   "
            else:
                # 如果没有子节点，则直接打印当前节点
                print(prefix + "└── " + str(self.val), end=end_char)
                prefix += "    "

            # 递归打印每个子节点
            for i, child in enumerate(self.children):
                child.print_tree(prefix, i == len(self.children) - 1)
    
#深度遍历，返回所有从根节点到叶子节点的路径
def find_paths(root:TreeNode):
    def dfs(node, current_path, all_paths):
        if not node.children:
            # 当前节点是叶子节点
            all_paths.append(current_path + [node.val])
        else:
            # 当前节点不是叶子节点
            for child in node.children:
                dfs(child, current_path + [node.val], all_paths)

    all_paths = []
    if root:
        dfs(root, [], all_paths)
    
    #去重
    from collections import Counter    
    counter = Counter(tuple( sorted(sublist[1:])) for sublist in all_paths)
    return [list(sublist) for sublist in counter]
        
    # return all_paths


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
    
    #遍历查找所有可能的组合
    def dfs(node:TreeNode, capacity, val)->bool:
            
            while(capacity>=min_wight):
                success = False
                for i in range(n):
                    cur_val=values[i]
                    cur_wight=weights[i]
                    
                    rest_capacity=capacity-cur_wight
                    rest_val=val-cur_val
                    if rest_capacity<0:
                        continue
                    if rest_val==dp[rest_capacity]:
                        cur_node=TreeNode(i)
                        node.append(cur_node)
                        if dfs(cur_node,rest_capacity,rest_val):
                            success=True
                            continue
                if not success:
                    return False
                    break
                
    root=TreeNode(-1)          
    dfs(root,all_capacity,result)
    # root.print_tree()
    result_list = find_paths(root)
    
    
    
    # print("去重后，索引列表","\n".join(["\t".join( map(str, item)) for item in result_list]) )
    print("去重后，重量列表")
    print("\n".join(["\t".join( map( lambda i: str(weights[i]), item)) for item in result_list]) )
    print("\n".join(["\t".join( map( lambda i: str(values[i]), item)) for item in result_list]) )
    
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
#二维数组实现完全背包问题
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
# values = [15,22,31,16,52,68]
values=[15,22,30,45,52,66]
for i in range(31, 32):
    capacity = i



    # print("Maximum value:", zero_one_knapsack(weights, values, capacity))
    print("Maximum value:", unbounded_knapsack(weights, values, capacity))
    # print("Maximum value:", complete_knapsack(weights, values, capacity))
