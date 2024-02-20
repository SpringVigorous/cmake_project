def zero_one_knapsack(capacity: int, w: List[int],v: List[int])-> int:
    n = len(w)

    @cache
    def dfs(i, c):
        if i < 0:
            return 0
        if c< w[i]:
            return dfs(i-1,c)
        return max(dfs(i-1,c),dfs(i-1,c-w[i])+ v[i])
    return dfs(n-1,capacity)



