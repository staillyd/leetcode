class Solution:

    def canJump(self, nums: List[int]) -> bool:
        max_cover = 0
        i = 0
        while i <= max_cover:  #当前位置能达到的最大位置
            max_cover = max(max_cover, i + nums[i])
            if max_cover >= len(nums) - 1:  #如果能到达最大位置
                return True
            i += 1
        return False
