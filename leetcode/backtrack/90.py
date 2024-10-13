class Solution:

    def subsetsWithDup(self, nums: List[int]) -> List[List[int]]:

        def back_track(nums, i_start):
            for i in range(i_start, len(nums)):
                if i > i_start and nums[i] == nums[i - 1]:  #剪枝
                    continue

                path.append(nums[i])
                ret.append(path.copy())
                back_track(nums, i + 1)
                path.pop()

        nums = sorted(nums)
        ret = [[]]
        path = []
        back_track(nums, 0)
        return ret
