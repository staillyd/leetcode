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