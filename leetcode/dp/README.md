# 动态规划
- 后面的操作依赖前面的操作
- 求以下问题时, 考虑动态规划
  - 总共多少种方式, 且不用列举所有方式, 只是问数量
  - 所有方式中最长、最短的一种

## [最长公共子序列](1143.py)
- [Link](https://leetcode-cn.com/problems/longest-common-subsequence/)
- 给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
- 一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
- 例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。

- 设$dp[i][j]$: text1[:i]与text2[:j]的最长公共子序列
- $ dp[i][j]=\left\{\begin{aligned}
                &dp[i-1][j-1]+1 & text1[i-1]=text2[j-1]\\
                &max(dp[i-1][j],dp[i][j-1]) & text1[i-1] \neq text2[j-1]
            \end{aligned}\right.$

```python
def longestCommonSubsequence(self, text1: str, text2: str) -> int:
    # dp[i][j]: text1[:i]与text2[:j]的最长公共子序列
    dp=[[0 for _ in range(len(text2)+1)] for _ in range(len(text1)+1)]
    
    for i in range(1,len(text1)+1):
        for j in range(1,len(text2)+1):
            if text1[i-1]==text2[j-1]:
                dp[i][j]=dp[i-1][j-1]+1
            else:
                dp[i][j]=max(dp[i-1][j],dp[i][j-1])
    return dp[len(text1)][len(text2)]
```

## [不同路径](62.py)
- [Link](https://leetcode-cn.com/problems/unique-paths/)
- 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
- 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。
- 问总共有多少条不同的路径？
- ![](imgs/robot_maze.png)
- m=3,n=7
1. 穷举遍历
```python
def uniquePaths_dfs(self, m: int, n: int) -> int:
    def dfs(i,j):
        if i>m-1 or j>n-1:
            return
        
        if i==m-1 and j==n-1:
            self.ret+=1
        dfs(i+1,j)
        dfs(i,j+1)
    self.ret=0
    dfs(0,0)
    return self.ret
```
2. dp
- 设$dp[i][j]$为到达 i, j 最多路径
$\begin{aligned}
    dp[i][j]&=dp[i-1][j]+dp[i][j-1]\\
    dp[1][j]&=1\\
    dp[i][1]&=1
\end{aligned}$
```python
def uniquePaths(self, m: int, n: int) -> int:
    dp=[[1 for _ in range(n+1)] for _ in range(m+1)]
    for i in range(2,m+1):
        for j in range(2,n+1):
            dp[i][j]=dp[i-1][j]+dp[i][j-1]

    return dp[m][n]
```

## [不同路径 II](63.py)
- [Link](https://leetcode-cn.com/problems/unique-paths-ii/)
- 一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。
- 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
- 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
- 设$dp[i][j]$为到达 i, j 最多路径
$\begin{aligned}
    dp[i][j]&=dp[i-1][j]+dp[i][j-1]\\
    dp[1][j]&=1;直到到出现障碍，障碍后的dp[1][j]=0\\
    dp[i][1]&=1;直到到出现障碍，障碍后的dp[i][1]=0
\end{aligned}$
- 有障碍的地方$dp[i][j]=0$
```python
def uniquePathsWithObstacles(self, obstacleGrid: List[List[int]]) -> int:
    dp=[[0 for _ in range(len(obstacleGrid[0])+1)] for _ in range(len(obstacleGrid)+1)]
    for i in range(1,len(dp)):
        if obstacleGrid[i-1][0]==0:
            dp[i][1]=1
        else:
            break
    for i in range(1,len(dp[0])):
        if obstacleGrid[0][i-1]==0:
            dp[1][i]=1
        else:
            break
    
    for i in range(2,len(dp)):
        for j in range(2,len(dp[0])):
            if obstacleGrid[i-1][j-1]==1:
                dp[i][j]=0
            else:
                dp[i][j]=dp[i-1][j]+dp[i][j-1]
    return dp[-1][-1]
```


## [爬楼梯](70.py)
- [Link](https://leetcode-cn.com/problems/climbing-stairs/)
- 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
- 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
- 注意：给定 n 是一个正整数。
- $dp[i]$:爬到第i阶总共的方法
- $dp[i]=dp[i-1]+dp[i-2]$
- $dp[1]=1,dp[2]=2$
```python
def climbStairs(self, n: int) -> int:
    dp=[0 for _ in range(n+1)]
    dp[1]=1
    if n<=1:
        return dp[1]
    dp[2]=2
    for i in range(3,n+1):
        dp[i]=dp[i-1]+dp[i-2]
    return dp[n]
```

## [使用最小花费爬楼梯](746.py)
- [Link](https://leetcode-cn.com/problems/min-cost-climbing-stairs/)
- 数组的每个下标作为一个阶梯，第 i 个阶梯对应着一个非负数的体力花费值 cost[i]（下标从 0 开始）。
- 每当你爬上一个阶梯你都要花费对应的体力值，一旦支付了相应的体力值，你就可以选择向上爬一个阶梯或者爬两个阶梯。
- 请你找出达到楼层顶部的最低花费。在开始时，你可以选择从下标为 0 或 1 的元素作为初始阶梯。
- $dp[i]$:到达第i层的最低花费
- $dp[i]=min(dp[i-1]+cost[i-2],dp[i-2]+cost[i-3])$:注意下标!!
- $dp[1]=0,dp[2]=0$
```python
def minCostClimbingStairs(self, cost: List[int]) -> int:
    dp=[0 for _ in range(len(cost)+2)]
    dp[1]=0
    if len(cost)==1:
        return dp[1]
    dp[2]=0
    for i in range(3,len(cost)+2):
        dp[i]=min(dp[i-1]+cost[i-2],dp[i-2]+cost[i-3])
    return dp[len(cost)+1]#n+1层才算楼梯顶
```

## 01背包
- 有N件物品和一个最多能被重量为W 的背包。第i件物品的重量是weight[i]，得到的价值是value[i] 。每件物品只能用一次，求解将哪些物品装入背包里物品价值总和最大。
- 暴力求解:回溯
  - 每一件物品两个状态，取或者不取，回溯法搜索出所有情况，时间复杂度O(2^n)，这里的n表示物品数量。
- dp思想
  - $dp[i][j]$:从下标0开始到i的物品中，放入到容量为j的背包可以得到的最大价值
  - ![](imgs/01背包.png)
  - w[i]>j时，背包放不下了$dp[i][j]=dp[i-1][j]$
  - $dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i])$
    - $dp[i-1][j]$:不放
    - $dp[i-1][j-w[i]]+v[i]$:放
```python
def bag_01(self, w: List[int],v:List[int],max_w:int) -> int:
    dp=[[0 for _ in range(max_w+1)] for _ in range(len(w))]
    for i in range(w[0],max_w+1):
        dp[0][i]=v[0]
    
    for i in range(1,len(w)):
        for j in range(max_w+1):
            if w[i]>j:
                dp[i][j]=dp[i-1][j]
            else:
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-w[i]]+v[i])
    return dp[-1][-1]
```

## 骑士在棋盘上的概率
- [Link](https://leetcode.cn/problems/knight-probability-in-chessboard/description/)
- $dp[step][i][j]$: 骑士从棋盘(i,j)出发, 走step步仍然在棋盘的概率
- 当骑士不在棋盘上时, $dp[step][i][i]=0$; 当点(i,j)在棋盘上且step=0时, $dp[step][i][j]=1$
- 其他情况, $dp[step][i][j]=\frac{1}{8}\underset{di, dj}{\sum} dp[step-1][i+di][j+dj]$
  - di,dj: 总共8种走法

```python
def knightProbability(self, n: int, k: int, row: int, column: int) -> float:
    dp = [[[0] * n for _ in range(n)] for _ in range(k + 1)]
    for step in range(k + 1):
        for i in range(n):
            for j in range(n):
                if step == 0:
                    dp[step][i][j] = 1
                else:
                    for di, dj in ((-2, -1), (-2, 1), (2, -1), (2, 1), (-1, -2), (-1, 2), (1, -2), (1, 2)):
                        ni, nj = i + di, j + dj
                        if 0 <= ni < n and 0 <= nj < n:
                            dp[step][i][j] += dp[step - 1][ni][nj] / 8
    return dp[k][row][column]
```

## [完全平方数](279.cpp)
- [Link](http://leetcode.cn/problems/perfect-squares/description/?envType=study-plan-v2&envId=top-100-liked)
- 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量。完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
- dp[i]: 最少需要多少个数的平方 来表示 整数i
- dp[0]=0
- $dp[i]=1+\underset{j=1}{\overset{\sqrt{i}}{\min}} dp[i-j^2]$

| idx | 0   | 1   | 2   | 3   | 4   | 5   |
| --- | --- | --- | --- | --- | --- | --- |
| dp  | 0   | 1   | 2   | 3   | 1   | 2   |

- 取之前平方数 余下的数 n - j\*j, j\*j最小个数已知
- dp[4], 比较dp[4-1=3], dp[4-2*2=0]
- dp[5], 比较dp[5-1=4], dp[5-2*2=1]

```cpp
int numSquares(int n) {
    std::vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        int minn = i;
        for (int j = 1; j * j <= i; ++j) {
            minn = std::min(minn, dp[i - j * j]); // 也可以在这+1
        }
        dp[i] = minn + 1;// 也可以去掉这里的+1
    }
    return dp[n];
}
```

## [整钱兑换](322.cpp)
- [Link](http://leetcode.cn/problems/coin-change/description/)
- 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。 你可以认为每种硬币的数量是无限的。
- dp[i]: 组成金额 i 所需最少的硬币数量
- $dp[i] = min(dp[i-c_1], dp[i-c_2], \cdots) + 1$

```cpp
int coinChange(std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; ++i) {// 注意<=
        for (auto c : coins) {
            if (c <= i) {  // 当前单位面值需要<=需要计算的面值
                dp[i] = std::min(dp[i - c] + 1, dp[i]);
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}
```