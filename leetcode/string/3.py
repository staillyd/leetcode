from typing import List


class Solution:

    def lengthOfLongestSubstring(self, s: str) -> int:
        '''无重复字符的最长子串
        
        @Note:
            滑动窗口法,进入这个队列（窗口）为 abc 满足题目要求，当再进入 a，队列变成了 abca，这时候不满足要求.将最左侧的元素移除
            字典:保存字符出现次数,保证出现次数都<=1,
        '''
        num_count = {}  #滑动窗口中各字符出现的个数
        l, r = 0, 0
        max_len = 0
        for r in range(len(s)):
            if s[r] not in num_count:  #累计次数
                num_count[s[r]] = 0
            num_count[s[r]] += 1

            while num_count[s[r]] > 1:  #当出现重复的时候,从左往右去除不满足条件的值
                num_count[s[l]] -= 1
                l += 1
            max_len = max(max_len, r - l + 1)  #当前满足条件的长
        return max_len

    def lengthOfLongestSubstring_2(self, s: str) -> int:
        '''无重复字符的最长子串
        
        @Note:
            最直观的求取每位的不重复子串长,然后求最大值,三重循环太长,去除一些重复取值情况
        '''
        lens = [len(s) - i for i in range(len(s))]  #初始值为子串最大值
        for i in range(len(s)):
            start_j = 1 if i == 0 else i - 1 + lens[i - 1]  #去除一些重复取值情况
            for j in range(start_j, len(s)):
                if s[j] in s[i:j]:
                    lens[i] = j - i
                    break
                else:
                    lens[i] = j - i + 1
        return 0 if len(s) == 0 else max(lens)

    def lengthOfLongestSubstring_3(self, s: str) -> int:
        '''无重复字符的最长子串
        
        @Note:
            最直观的求取每位的不重复子串长,然后求最大值,三重循环太长
        '''
        lens = [len(s) - i for i in range(len(s))]  #初始值为子串最大值
        for i in range(len(s)):
            for j in range(i + 1, len(s)):
                if s[j] in s[i:j]:
                    lens[i] = j - i
                    break
                else:
                    lens[i] = j - i + 1
        return 0 if len(s) == 0 else max(lens)


if __name__ == '__main__':
    string = input().strip()
    solution = Solution()
    print(solution.lengthOfLongestSubstring(string))
