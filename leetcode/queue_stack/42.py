from typing import List


class Solution:

    def trap(self, height: List[int]) -> int:
        '''使单调减栈,求出左右第一个大于当前元素的边界,如果存在左右边界,
        则填充左右边界中较小的'''
        s = []
        ret = 0
        for i, h in enumerate(height):
            while s and h > height[s[-1]]:
                pop_idx = s.pop()
                r = i - 1
                if len(s) == 0:
                    break
                l = s[-1] + 1
                dis = r - l + 1
                delt_height = min(h, height[l - 1]) - height[pop_idx]
                ret += delt_height * dis
            s.append(i)
        return ret

    def trap_all_2(self, height: List[int]) -> int:
        '''穷举,优化max步骤'''
        l_max = [0 for i in range(len(height))]
        this_max = 0
        for i in range(len(height)):
            if this_max < height[i]:
                this_max = height[i]
            l_max[i] = this_max

        r_max = [0 for i in range(len(height))]
        this_max = 0
        for i in range(len(height))[::-1]:
            if this_max < height[i]:
                this_max = height[i]
            r_max[i] = this_max

        sum = 0
        for i in range(len(height)):
            sum += min(l_max[i], r_max[i]) - height[i]
        return sum

    def trap_all(self, height: List[int]) -> int:
        '''对每个元素,找左右最大的元素,将当前值赋值为min(左大,右大)'''
        flow = [i for i in height]
        for i in range(len(height)):
            l_max = max(height[:i + 1])  #往左找最大值
            r_max = max(height[i:])  #往右找最大值
            flow[i] = min(l_max, r_max)
        sum = 0
        for i in range(len(height)):
            sum += flow[i] - height[i]
        return sum


if __name__ == '__main__':
    solution = Solution()
    # solution.trap([0,1,0,2,1,0,1,3,2,1,2,1])
    solution.trap([2, 1, 5, 5, 5, 6, 5, 6, 2, 3])
