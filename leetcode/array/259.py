from typing import List


class Solution:

    def threeSumSmaller(self, nums: List[int], target: int) -> int:
        '''较小的三数和
        
        @Note:
            排序->三指针,固定一个,双边遍历
        '''
        count = 0
        lens = len(nums)
        nums = sorted(nums)
        for i in range(lens):
            l = i + 1
            r = lens - 1
            while l < r:  #当前i下的所有满足条件的个数
                if nums[i] + nums[l] + nums[r] >= target:
                    r -= 1
                else:
                    count += r - l
                    l += 1  #双边遍历
        return count


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    target = int(input().strip())
    solution = Solution()
    print(solution.threeSumSmaller(arr, target))
