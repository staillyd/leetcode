from typing import List


class Solution:

    def moveZeroes(self, nums: List[int]) -> None:
        '''快慢指针'''
        j = 0
        for i in range(len(nums)):
            if nums[i] != 0:
                nums[j] = nums[i]
                j += 1

        for i in range(j, len(nums)):
            nums[i] = 0


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    solution.moveZeroes(arr)
    print(arr)
