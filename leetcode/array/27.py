from typing import List


class Solution:

    def removeElement(self, nums: List[int], val: int) -> int:
        '''快慢指针,遍历一次,不管后面的元素'''
        slow = 0
        for fast in range(len(nums)):
            if nums[fast] != val:
                nums[slow] = nums[fast]
                slow += 1
        return slow

    def removeElement_modify(self, nums: List[int], val: int) -> int:
        '''首尾指针'''
        l = 0
        r = len(nums) - 1
        while l <= r:  #和快排不同处
            if nums[l] == val:  #避免重复赋值
                nums[l] = nums[r]
                r = r - 1
            else:
                l += 1
        return l

    def removeElement_del(self, nums: List[int], val: int) -> int:
        '''快排方式,双指针,元素不变'''
        if len(nums) == 0:
            return 0
        l = 0
        r = len(nums) - 1
        this_num = nums[0]
        while l < r:
            while l < r and nums[r] == val:
                r -= 1
            if l < r:
                nums[l] = nums[r]
                l += 1
            while l < r and nums[l] != val:
                l += 1
            if l < r:
                nums[r] = nums[l]
                r -= 1
            if l >= r:
                break
        nums[l] = this_num
        if this_num == val:
            return l
        else:
            return l + 1


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    val = int(input().strip())
    solution = Solution()
    print(solution.removeElement(arr, val))
    print(arr)
