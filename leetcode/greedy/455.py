class Solution:

    def findContentChildren(self, g: List[int], s: List[int]) -> int:
        g = sorted(g)
        s = sorted(s)
        i, j = len(g) - 1, len(s) - 1
        cnt = 0
        while i >= 0 and j >= 0:
            while i >= 0 and g[i] > s[j]:
                i -= 1
            if i >= 0 and j >= 0:
                cnt += 1
                i -= 1
                j -= 1
        return cnt
