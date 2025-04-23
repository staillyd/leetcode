from typing import List


class Solution:

    def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
        dp = [[0 for _ in range(len(obstacleGrid[0]) + 1)] for _ in range(len(obstacleGrid) + 1)]
        for i in range(1, len(dp)):
            if obstacleGrid[i - 1][0] == 0:
                dp[i][1] = 1
            else:
                break
        for i in range(1, len(dp[0])):
            if obstacleGrid[0][i - 1] == 0:
                dp[1][i] = 1
            else:
                break

        for i in range(2, len(dp)):
            for j in range(2, len(dp[0])):
                if obstacleGrid[i - 1][j - 1] == 1:
                    dp[i][j] = 0
                else:
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1]
        return dp[-1][-1]


if __name__ == '__main__':
    solution = Solution()
    solution.uniquePathsWithObstacles([[1, 0]])
