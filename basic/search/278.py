# The isBadVersion API is already defined for you.
# @param version, an integer
# @return an integer
# def isBadVersion(version):


class Solution:

    def firstBadVersion(self, n):
        """
        :type n: int
        :rtype: int
        """
        l, r = 1, n
        while l < r:
            m = (l + r) // 2
            ret = isBadVersion(m)
            if ret:
                r = m
            else:
                l = m + 1
        return l
