from typing import List


class Solution:

    def mySqrt(self, x: int) -> int:
        '''求平方根'''
        l, r = 0, x
        ret = -1
        while l <= r:
            m = (l + r) // 2
            this_product = m * m
            if this_product < x:
                ret = m  #向下取整
                l = m + 1
            elif this_product > x:
                r = m - 1
            else:
                return m
        return ret


if __name__ == '__main__':
    target = int(input().strip())
    solution = Solution()
    print(solution.mySqrt(target))
