class Solution:

    def combinationSum(self, candidates: List[int],
                       target: int) -> List[List[int]]:
        ret = []
        path = []

        def back_track(nums, i_start, sum_):
            for i in range(i_start, len(nums)):
                if sum_ + nums[i] > target:  #剪枝
                    continue

                sum_ += nums[i]
                path.append(nums[i])
                if sum_ == target:  #如果满足条件,则append
                    ret.append(path.copy())

                back_track(nums, i, sum_)
                sum_ -= nums[i]  #回退状态
                path.pop()

        back_track(candidates, 0, 0)
        return ret
