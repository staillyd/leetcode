from typing import List


class Solution:

    def searchRange(self, nums: List[int], target: int) -> List[int]:
        '''在排序数组中查找元素的第一个和最后一个位置'''
        first, last = -1, -1
        # 找第一个
        l, r = 0, len(nums) - 1
        while l <= r:
            m = (l + r) // 2
            if nums[m] < target:
                l = m + 1
            elif nums[m] > target:
                r = m - 1
            else:
                if m == 0 or nums[m - 1] != target:
                    first = m
                    break
                r = m - 1

        if first == -1:
            return [-1, -1]
        # 找最后一个
        l, r = first, len(nums) - 1
        while l <= r:
            m = (l + r) // 2
            if nums[m] < target:
                l = m + 1
            elif nums[m] > target:
                r = m - 1
            else:
                if m == len(nums) - 1 or nums[m + 1] != target:
                    last = m
                    break
                l = m + 1
        return [first, last]


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    target = int(input().strip())
    solution = Solution()
    print(solution.searchRange(arr, target))
