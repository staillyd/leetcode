from typing import List


class Solution:

    def lengthOfLongestSubstringTwoDistinct(self, s: str) -> str:
        '''至多包含两个不同字符的最长子串'''
        char_count = {}  #滑动窗口中字符出现的次数
        l, r = 0, 0
        max_len = 0
        ret = ''
        for r in range(len(s)):
            if s[r] not in char_count:
                char_count[s[r]] = 0
            char_count[s[r]] += 1

            while len(char_count) > 2:  #如果不满足条件
                char_count[s[l]] -= 1
                if char_count[s[l]] == 0:
                    char_count.pop(s[l])
                l += 1

            if r - l + 1 > max_len:
                max_len = r - l + 1
                ret = s[l:r + 1]
        return ret


if __name__ == '__main__':
    string = input()
    solution = Solution()
    print(solution.lengthOfLongestSubstringTwoDistinct(string))
