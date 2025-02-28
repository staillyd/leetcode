from typing import List


class Solution:

    def threeSumClosest(self, nums: List[int], target: int) -> int:
        '''最接近的三数和
        
        @Note:
            排序->三指针,固定一个,双边遍历. 添加一个绝对差值判断
        '''
        lens = len(nums)
        nums = sorted(nums)
        diff = 10000
        ret = None
        for i in range(lens):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            l = i + 1
            r = lens - 1
            while l < r:
                sum = nums[i] + nums[l] + nums[r]
                if abs(sum - target) < diff:
                    diff = abs(sum - target)
                    ret = sum
                if sum == target:
                    return sum
                elif sum > target:
                    r -= 1
                elif sum < target:
                    l += 1
        return ret


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    target = int(input().strip())
    solution = Solution()
    print(solution.threeSumClosest(arr, target))
