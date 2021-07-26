# 数学
## [只出现一次的数字](136.py)
- [Link](https://leetcode-cn.com/problems/single-number/)
- 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
- **a异或a=0;a异或0=a**
```python
def singleNumber(self, nums: List[int]) -> int:
    ret=0
    for num in nums:
        ret^=num
    return ret
```
