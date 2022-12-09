from typing import List


class Solution:

    def findMin(self, nums: List[int]) -> int:
        '''寻找旋转排序数组中的最小值
        
        @Note:
            若 nums[m] > nums[r]，说明最小值在 m 的右边；若 nums[m] < nums[r]，说明最小值在 m 的左边（包括 m）；若相等，无法判断，直接将 r 减 1。循环比较。
            m与r比较,返回l(l为查找索引)
        '''
        l, r = 0, len(nums) - 1
        while l < r:
            m = (l + r) // 2
            if nums[m] > nums[r]:
                l = m + 1
            elif nums[m] < nums[r]:
                r = m
            else:
                r -= 1  #为应对3、3、1、3情况
        return nums[l]


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    print(solution.findMin(arr))
