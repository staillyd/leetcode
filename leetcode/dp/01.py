from typing import List


class Solution:

    def bag_01(self, w: List[int], v: List[int], max_w: int) -> int:
        dp = [[0 for _ in range(max_w + 1)] for _ in range(len(w))]
        for i in range(w[0], max_w + 1):
            dp[0][i] = v[0]

        for i in range(1, len(w)):
            for j in range(max_w + 1):
                if w[i] > j:
                    dp[i][j] = dp[i - 1][j]
                else:
                    dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i]] + v[i])
        return dp[-1][-1]


if __name__ == '__main__':
    solution = Solution()
    print(solution.bag_01([1, 4, 3], [15, 30, 20], 4))
