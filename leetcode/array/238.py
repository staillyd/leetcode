from typing import List


class Solution:

    def productExceptSelf(self, nums: List[int]) -> List[int]:
        '''除自身以外数组的乘积
        '''
        res = [1]
        l, r = 1, 1
        lens = len(nums)
        for i in range(lens - 1):  #下三角0~n-2
            l *= nums[i]
            res.append(l)
        for j in range(lens - 1, 0, -1):  #上三角n-1~1
            r *= nums[j]
            res[j - 1] *= r
        return res


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    print(solution.productExceptSelf(arr))
