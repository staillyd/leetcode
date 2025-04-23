from typing import List


class Solution:

    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        '''a+b+c+d=target的不重复解
        
        @Note:
            排序,四指针,固定两个,剩余两个双边遍历
        '''
        ret = []
        lens = len(nums)
        if lens < 4:
            return []
        nums = sorted(nums)
        for i in range(lens):  #当前循环获取当前值下所有合适解
            # if nums[i]>target:#与target=0不同
            #     break
            if i > 0 and nums[i] == nums[i - 1]:  #注意边界
                continue
            for j in range(i + 1, lens):  #当前循环获取当前值下所有合适解
                if j > i + 1 and nums[j] == nums[j - 1]:
                    continue
                l = j + 1
                r = lens - 1
                while l < r:
                    sum = nums[i] + nums[j] + nums[l] + nums[r]
                    if sum == target:
                        ret.append([nums[i], nums[j], nums[l], nums[r]])
                        while l < r and nums[l + 1] == nums[l]:  #下一值与当前值相等(去重)
                            l += 1
                        l + 1
                        while l < r and nums[r - 1] == nums[r]:
                            r -= 1
                        r -= 1
                    elif sum > target:
                        r -= 1
                    else:
                        l += 1
        return ret


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    target = int(input().strip())
    solution = Solution()
    print(solution.fourSum(arr, target))
