class Solution:

    def minCostClimbingStairs(self, cost: List[int]) -> int:
        dp = [0 for _ in range(len(cost) + 2)]
        dp[1] = 0
        if len(cost) == 1:
            return dp[1]
        dp[2] = 0
        for i in range(3, len(cost) + 2):
            dp[i] = min(dp[i - 1] + cost[i - 2], dp[i - 2] + cost[i - 3])
        return dp[len(cost) + 1]
