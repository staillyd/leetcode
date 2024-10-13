from typing import List


class Solution:

    def findPeakElement(self, nums: List[int]) -> int:
        '''返回索引,寻找无重复元素中的极大值'''
        l, r = 0, len(nums) - 1
        while l < r:  #注意条件
            m = (l + r) // 2
            if nums[m] > nums[m + 1]:
                r = m
            else:
                l = m + 1
        return l


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(',')]
    solution = Solution()
    print(arr[solution.findPeakElement(arr)])
