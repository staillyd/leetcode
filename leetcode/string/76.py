from typing import List


class Solution:

    def minWindow(self, s: str, t: str) -> str:
        '''最小覆盖子串
        
        @Note:
            滑动窗口,t存在重复字符的情况
        '''
        need_cnt = {}  #滑动窗口中t字符还需要的个数
        for t_char in t:
            if t_char not in need_cnt:
                need_cnt[t_char] = 0
            need_cnt[t_char] += 1
        l, r = 0, 0
        min_len = len(s)
        ret = ''
        all_need_cnt = len(t)  #仍需要的个数才能满足条件
        for r in range(len(s)):
            if s[r] in need_cnt:
                if need_cnt[s[r]] > 0:
                    all_need_cnt -= 1
                need_cnt[s[r]] -= 1

            while all_need_cnt == 0:  #当满足条件时
                if r - l + 1 <= min_len:
                    min_len = r - l + 1
                    ret = s[l:r + 1]

                if s[l] in need_cnt:
                    need_cnt[s[l]] += 1
                    if need_cnt[s[l]] > 0:
                        all_need_cnt += 1
                l += 1
        return ret


if __name__ == '__main__':
    string = input()
    find = input()
    solution = Solution()
    print(solution.minWindow(string, find))
