# 字符串
## [无重复字符的最长子串](3.py)
- [Link](https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/)
- 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度
- 滑动窗口法!!!  重点在于滑动的流程,这个流程需要思考
- 定义num_count字典:保存字符出现次数,保证出现次数都<=1,
```python
def lengthOfLongestSubstring(self, s: str) -> int:
    '''无重复字符的最长子串
    
    @Note:
        滑动窗口法,进入这个队列（窗口）为 abc 满足题目要求，当再进入 a，队列变成了 abca，这时候不满足要求.将最左侧的元素移除
        字典:保存字符出现次数,保证出现次数都<=1,
    '''
    num_count={}#滑动窗口中各字符出现的个数
    l,r=0,0
    max_len=0
    for r in range(len(s)):
        if s[r] not in num_count:#累计次数
            num_count[s[r]]=0
        num_count[s[r]]+=1

        while num_count[s[r]]>1:#当出现重复的时候,从左往右去除不满足条件的值
            num_count[s[l]]-=1
            l+=1
        max_len=max(max_len,r-l+1)#当前满足条件的长
    return max_len
```
```python
def lengthOfLongestSubstring_2(self, s: str) -> int:
    '''无重复字符的最长子串
    
    @Note:
        最直观的求取每位的不重复子串长,然后求最大值,三重循环太长,去除一些重复取值情况
    '''
    lens=[len(s)-i for i in range(len(s))]#初始值为子串最大值
    for i in range(len(s)):
        start_j=1 if i==0 else i-1+lens[i-1]#去除一些重复取值情况
        for j in range(start_j,len(s)):
            if s[j] in s[i:j]:
                lens[i]=j-i
                break
            else:
                lens[i]=j-i+1
    return 0 if len(s)==0 else max(lens)
```
```python
def lengthOfLongestSubstring_3(self, s: str) -> int:
    '''无重复字符的最长子串
    
    @Note:
        最直观的求取每位的不重复子串长,然后求最大值,三重循环太长
    '''
    lens=[len(s)-i for i in range(len(s))]#初始值为子串最大值
    for i in range(len(s)):
        for j in range(i+1,len(s)):
            if s[j] in s[i:j]:
                lens[i]=j-i
                break
            else:
                lens[i]=j-i+1
    return 0 if len(s)==0 else max(lens)
```

## [最小覆盖子串](76.py)
- [Link](https://leetcode-cn.com/problems/minimum-window-substring/)
- 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 ""
- 定义变量need_cnt:滑动窗口中t字符还需要的个数;all_need_cnt:满足条件仍需要的个数(为了避免遍历need_cnt是否都为0);
- 当满足条件时，滑动窗口往外扔，进行下一次迭代
```python
def minWindow(self, s: str, t: str) -> str:
    '''最小覆盖子串
    
    @Note:
        滑动窗口,t存在重复字符的情况
    '''
    need_cnt={}#滑动窗口中t字符还需要的个数
    for t_char in t:
        if t_char not in need_cnt:
            need_cnt[t_char]=0
        need_cnt[t_char]+=1
    l,r=0,0
    min_len=len(s)
    ret=''
    all_need_cnt=len(t)#仍需要的个数才能满足条件
    for r in range(len(s)):
        if s[r] in need_cnt:
            if need_cnt[s[r]]>0:
                all_need_cnt-=1
            need_cnt[s[r]]-=1
        
        while all_need_cnt==0:#当满足条件时
            if r-l+1<=min_len:
                min_len=r-l+1
                ret=s[l:r+1]

            if s[l] in need_cnt:
                need_cnt[s[l]]+=1
                if need_cnt[s[l]]>0:
                    all_need_cnt+=1
            l+=1
    return ret
```

## [至多包含两个不同字符的最长子串](159.py)
- [Link](https://leetcode-cn.com/problems/longest-substring-with-at-most-two-distinct-characters/)
- 给定一个字符串 s ，找出 至多 包含两个不同字符的最长子串 t 
```python
def lengthOfLongestSubstringTwoDistinct(self, s: str) -> str:
    '''至多包含两个不同字符的最长子串'''
    char_count={}#滑动窗口中字符出现的次数
    l,r=0,0
    max_len=0
    ret=''
    for r in range(len(s)):
        if s[r] not in char_count:
            char_count[s[r]]=0
        char_count[s[r]]+=1

        while len(char_count)>2:#如果不满足条件
            char_count[s[l]]-=1
            if char_count[s[l]]==0:
                char_count.pop(s[l])
            l+=1

        if r-l+1>max_len:
            max_len=r-l+1
            ret=s[l:r+1]
    return ret
```