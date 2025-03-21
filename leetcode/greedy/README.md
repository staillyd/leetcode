# 贪心算法
- 以局部最优推出整体最优，而且想不到反例，那么就试一试贪心

## [分发饼干](455.py)
- [Link](https://leetcode-cn.com/problems/assign-cookies/)
- 假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
- 对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。
```python
def findContentChildren(self, g: List[int], s: List[int]) -> int:
    g=sorted(g)
    s=sorted(s)
    i,j=len(g)-1,len(s)-1
    cnt=0
    while i>=0 and j>=0:
        while i>=0 and g[i]>s[j]:
            i-=1
        if i>=0 and j>=0:
            cnt+=1
            i-=1
            j-=1
    return cnt
```

## [跳跃游戏](55.py)
- [Link](https://leetcode-cn.com/problems/jump-game/)
- 给定一个非负整数数组，你最初位于数组的第一个位置。
- 数组中的每个元素代表你在该位置可以跳跃的最大长度。
- 判断你是否能够到达最后一个位置。
- 示例 1: 输入: [2,3,1,1,4] 输出: true 解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。
- 示例 2: 输入: [3,2,1,0,4] 输出: false 解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。
- 贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），整体最优解：最后得到整体最大覆盖范围，看是否能到终点。
```python
def canJump(self, nums: List[int]) -> bool:
    max_cover=0
    i=0
    while i<=max_cover:#当前位置能达到的最大位置
        max_cover=max(max_cover,i+nums[i])
        if max_cover>=len(nums)-1:#如果能到达最大位置
            return True
        i+=1
    return False
```

## [跳跃游戏 II](45.py)
- [Link](https://leetcode-cn.com/problems/jump-game-ii/)
- 给你一个非负整数数组 nums ，你最初位于数组的第一个位置。
- 数组中的每个元素代表你在该位置可以跳跃的最大长度。
- 你的目标是使用最少的跳跃次数到达数组的最后一个位置。
- 假设你总是可以到达数组的最后一个位置。

```python
def jump(self, nums: List[int]) -> int:
    max_cover=0
    i=0
    cnt=0
    last_max_cover=0
    while i<=max_cover and i<=len(nums)-2:
        max_cover=max(max_cover,i+nums[i])
        if i==last_max_cover:#上一次起跳的最大范围
            cnt+=1
            last_max_cover=max_cover
        i+=1
    return cnt
```