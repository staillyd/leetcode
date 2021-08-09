# 动态规划
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
