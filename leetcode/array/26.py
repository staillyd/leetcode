from typing import List


class Solution:

    def removeDuplicates(self, nums: List[int]) -> int:
        '''快慢指针'''
        j = 1  #慢指针
        for i in range(1, len(nums)):  #快指针
            if nums[i] != nums[j - 1]:
                nums[j] = nums[i]
                j += 1
        return j

    def removeDuplicates_del(self, nums: List[int]) -> int:
        cnt = 0  #重复个数
        len_ = len(nums)
        for i in range(1, len_):
            replace_i = i - cnt  #replace_i:不重复时需要替换的位置
            if nums[i] != nums[replace_i - 1]:  #i:当前元素
                nums[replace_i] = nums[i]
            else:
                cnt += 1
        return len_ - cnt


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    print(solution.removeDuplicates(arr))
    print(arr)
