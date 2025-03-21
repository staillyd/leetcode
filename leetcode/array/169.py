from typing import List


class Solution:

    def majorityElement(self, nums: List[int]) -> int:
        '''查找数组中的多数元素,多数元素:出现次数>n/2的元素.
        
        @Note:
            对拼消耗,最差所有人都联合起来对付你
        '''
        major = None
        cnt = 0
        for num in nums:
            if cnt == 0:
                major = num
                cnt = 1
            else:
                cnt += 1 if major == num else -1
        return major


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    solution = Solution()
    print(solution.majorityElement(arr))
