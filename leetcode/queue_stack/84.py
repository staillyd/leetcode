from typing import List


class Solution:

    def largestRectangleArea(self, heights: List[int]) -> int:
        s = []  #存索引
        max_area = 0
        for i in range(len(heights)):
            while s and heights[s[-1]] > heights[i]:  #满足条件则弹出,直到不满足条件
                cur = s.pop()
                l = s[-1] + 1 if len(s) != 0 else 0
                max_area = max(max_area, heights[cur] * (i - 1 - l + 1))
            s.append(i)
        while s:  #当栈里仍然存在数据时
            cur = s.pop()
            l = s[-1] + 1 if len(s) != 0 else 0
            max_area = max(max_area, heights[cur] * (len(heights) - 1 - l + 1))
        return max_area

    def largestRectangleArea_all(self, heights: List[int]) -> int:
        max_area = 0
        for i in range(len(heights)):
            l, r = i, i
            while r < len(heights) and heights[r] >= heights[i]:  #往右找>当前元素的右边界
                r += 1
            while l >= 0 and heights[l] >= heights[i]:  #往左找>当前元素的左边界
                l -= 1
            max_area = max(max_area, heights[i] * (r - 1 - (l + 1) + 1))
        return max_area


if __name__ == '__main__':
    solution = Solution()
    solution.largestRectangleArea([2, 1, 5, 6, 2, 3])
