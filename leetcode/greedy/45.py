from typing import List


class Solution:

    def jump(self, nums: List[int]) -> int:
        max_cover = 0
        i = 0
        cnt = 0
        last_max_cover = 0
        while i <= max_cover and i <= len(nums) - 2:
            max_cover = max(max_cover, i + nums[i])
            if i == last_max_cover:  #上一次起跳的最大范围
                cnt += 1
                last_max_cover = max_cover
            i += 1
        return cnt


if __name__ == '__main__':
    solution = Solution()
    print(solution.jump([1, 2, 3, 1, 1, 4]))
