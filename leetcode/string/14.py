from typing import List


class Solution:

    def longestCommonPrefix(self, strs: List[str]) -> str:
        '''最长公共前缀
        
        @Note:
            纵向比较
        '''
        if len(strs) == 0:
            return ''
        for j in range(len(strs[0])):
            for i in range(1, len(strs)):
                if len(strs[i]) < j + 1 or strs[i][j] != strs[0][j]:
                    return strs[0][:j]
        return strs[0]  #注意这,如果前面条件都满足,那么返回strs[0]


if __name__ == '__main__':
    string = input().strip()
    solution = Solution()
    print(solution.longestCommonPrefix(string))
