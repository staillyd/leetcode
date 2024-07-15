from typing import List


class Solution:

    def rotate(self, nums: List[int], k: int) -> None:
        k = k % len(nums)
        if k == 0:
            return
        nums[:] = nums[::-1]
        nums[:k] = nums[:k][::-1]
        nums[k:] = nums[k:][::-1]


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    k = int(input().strip())
    solution = Solution()
    solution.rotate(arr, k)
    print(arr)
