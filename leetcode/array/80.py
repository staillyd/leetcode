from typing import List


class Solution:

    def removeDuplicates(self, nums: List[int]) -> int:
        '''快慢指针'''
        j = 2
        for i in range(2, len(nums)):
            if nums[i] != nums[j - 2]:
                nums[j] = nums[i]
                j += 1
        return j

    def removeDuplicates_del(self, nums: List[int]) -> int:
        cnt = 0  #超过两次的个数
        this_num_cnt = 1  #当前数字出现的次数
        len_ = len(nums)
        for i in range(1, len_):
            replace_i = i - cnt
            if nums[i] != nums[replace_i - 1]:
                nums[replace_i] = nums[i]
                this_num_cnt = 1
            else:
                this_num_cnt += 1
                if this_num_cnt <= 2:
                    nums[replace_i] = nums[i]
                else:
                    cnt += 1
        return len_ - cnt


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    print(solution.removeDuplicates(arr))
    print(arr)
