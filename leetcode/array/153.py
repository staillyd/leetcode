from typing import List


class Solution:

    def findMin(self, nums: List[int]) -> int:
        '''寻找旋转排序数组中的最小值
        
        @Note:
            二分,若 nums[m] > nums[r]，说明最小值在 m 的右边，否则说明最小值在 m 的左边（包括 m）
            m与r比较,返回l(l为查找索引)
        '''
        l, r = 0, len(nums) - 1
        while l < r:
            m = (l + r) // 2
            if nums[m] > nums[r]:
                l = m + 1
            else:
                r = m  #不能是m-1,  3、1、2情况下出错
        return nums[l]


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    print(solution.findMin(arr))
