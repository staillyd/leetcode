# 数学
## [整数转罗马数字]
- [Link](https://leetcode-cn.com/problems/integer-to-roman/)
- 思路:num_roman,来了一个数从字典中剪去可能的最大数
```python
def intToRoman(self, num: int) -> str:
    nums = [(1000, 'M'), (900, 'CM'), (500, 'D'), (400, 'CD'), (100, 'C'), (90, 'XC'), (50, 'L'), (40, 'XL'), (10, 'X'), (9, 'IX'), (5, 'V'), (4, 'IV'), (1, 'I')]
    res = []
    for k, v in nums:
        while num >= k:
            num -= k
            res.append(v)
    return ''.join(res)
```

## [罗马数字转整数]
- [Link](https://leetcode-cn.com/problems/roman-to-integer/)
- 思路:roman_num,来了一个罗马数从字符中删去可能的最大数对应的字符
```python
def romanToInt(self, s: str) -> int:
    nums = {
        'M': 1000,
        'CM': 900,
        'D': 500,
        'CD': 400,
        'C': 100,
        'XC': 90,
        'L': 50,
        'XL': 40,
        'X': 10,
        'IX': 9,
        'V': 5,
        'IV': 4,
        'I': 1
    }
    i = res = 0
    while i < len(s):
        if i + 1 < len(s) and s[i:i + 2] in nums:
            res += nums[s[i: i + 2]]
            i += 2
        else:
            res += nums[s[i: i + 1]]
            i += 1
    return res
```

## [只出现一次的数字](136.py)
- [Link](https://leetcode-cn.com/problems/single-number/)
- 给定一个非空整数数组，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
- **a异或a=0;a异或0=a;a异或1=取反**
```python
def singleNumber(self, nums: List[int]) -> int:
    ret=0
    for num in nums:
        ret^=num
    return ret
```

## [只出现一次的数字 II](137.py)
- [Link](https://leetcode-cn.com/problems/single-number-ii/)
- 给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。
- 对于出现三次的数字，各 二进制位 出现的次数都是 3 的倍数。因此，统计所有数字的各二进制位中 1 的出现次数，并对 3 求余，结果则为只出现一次的数字
```python
def singleNumber(self, nums: List[int]) -> int:
    count=[0]*32#各 二进制位 出现的次数
    for num in nums:
        for i in range(32):
            count[i]+=num&1
            num>>=1
        
    ret=0
    for i in range(32):
        ret<<=1#注意先左移
        ret|=count[31-i]%3
    return ret if count[31]%3==0 else ~(ret^0xffffffff)#python位数高,如果出现的是负数,那么需要先对0~32位取反,在对当前数进行取反(符号位及从末尾开始到第一个非0数)
```