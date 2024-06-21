class Solution:

    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        s = []
        ret = [-1] * len(nums)
        for i in range(2 * len(nums)):
            real_i = i % len(nums)
            while s and nums[s[-1]] < nums[real_i]:
                pop_i = s.pop()
                ret[pop_i] = nums[real_i]
            s.append(real_i)
        return ret
