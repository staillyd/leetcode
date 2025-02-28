class Solution:

    def subsets(self, nums: List[int]) -> List[List[int]]:
        path = []
        ret = [[]]

        def back_track(nums, i_start):
            for i in range(i_start, len(nums)):
                path.append(nums[i])
                ret.append(path.copy())
                back_track(nums, i + 1)
                path.pop()

        back_track(nums, 0)
        return ret
