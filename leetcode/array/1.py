from typing import List


class Solution:

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        '''字典存储'''
        num_idx = {}
        for i, num in enumerate(nums):
            find_num = target - num
            if find_num in num_idx:
                return [num_idx[find_num], i]
            num_idx[num] = i


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    target = int(input().strip())
    solution = Solution()
    print(solution.twoSum(arr, target))
