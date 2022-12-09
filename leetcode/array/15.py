from typing import List


class Solution:

    def threeSum(self, nums: List[int]) -> List[List[int]]:
        '''a+b+c=0的不重复解
        
        @Note:
            排序,三指针,固定一个,剩余两个双边遍历
        '''
        ret = []
        lens = len(nums)
        if lens < 3:  #特殊情况
            return []
        nums = sorted(nums)  #排序
        for i in range(lens):
            a = nums[i]
            if a > 0:  #a>0,往后没解了
                break
            if i > 0 and a == nums[i - 1]:  #去除重复解
                continue
            l = i + 1
            r = lens - 1
            while l < r:
                b, c = nums[l], nums[r]
                sum = a + b + c
                if sum == 0:
                    ret.append([a, b, c])
                    while l < r and nums[l + 1] == nums[l]:  #下一个元素等于当前元素(去重)
                        l += 1
                    l += 1
                    while l < r and nums[r - 1] == nums[r]:  #下一个元素等于当前元素(去重)
                        r -= 1
                    r -= 1
                elif sum < 0:
                    l += 1
                elif sum > 0:
                    r -= 1
        return ret


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    print(solution.threeSum(arr))
