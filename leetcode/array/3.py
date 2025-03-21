from typing import List


class Solution:

    def findRepeatNumber(self, nums: List[int]) -> int:
        '''原地交换'''
        for i, num in enumerate(nums):
            while i != num:  #当前位索引!=当前位
                if num == nums[num]:  #如果已经归位(nums[num])
                    return num
                nums[i], nums[num] = nums[num], nums[i]  #归位(nums[num])
                num = nums[i]
        return -1

    def findRepeatNumber_del(self, nums: List[int]) -> int:
        '''内存占用高'''
        dic = {}
        for i in nums:
            if i not in dic:
                dic[i] = True
            else:
                return i
        return -1


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    print(solution.findRepeatNumber(arr))
    print(arr)
