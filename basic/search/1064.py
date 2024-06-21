from typing import List


class Solution:

    def fixedPoint(self, arr: List[int]) -> int:
        '''寻找满足 arr[i] == i 的最小索引 i'''
        l, r = 0, len(arr) - 1
        while l < r:
            m = (l + r) // 2
            if arr[m] < m:
                l = m + 1
            elif arr[m] == m:
                r = m  #要找最小索引
            else:
                r = m - 1
        if arr[l] != l:
            return -1
        else:
            return l


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(',')]
    solution = Solution()
    print(solution.fixedPoint(arr))
