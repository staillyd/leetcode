from copy import deepcopy
from typing import List


class Solution:

    def solveNQueens(self, n: int) -> List[List[str]]:
        chessboard = [['.' for _ in range(n)] for _ in range(n)]
        ret = []

        def valid(row, col):
            '''当前位置是否可以放'''
            # 同一列
            for i in range(row):
                if chessboard[i][col] == 'Q':
                    return False

            # 左斜边
            for i in range(row):
                if row - 1 - i < 0 or col - 1 - i < 0:
                    break
                if chessboard[row - 1 - i][col - 1 - i] == 'Q':
                    return False

            # 右斜边
            for i in range(row):
                if row - 1 - i < 0 or col + 1 + i == n:
                    break
                if chessboard[row - 1 - i][col + 1 + i] == 'Q':
                    return False
            return True

        def back_track(row):
            if row == n:  #遍历完所有行之后
                out = [''.join(c) for c in chessboard]
                ret.append(out)
                return
            for i in range(n):
                if valid(row, i):
                    chessboard[row][i] = 'Q'
                    back_track(row + 1)
                    chessboard[row][i] = '.'

        back_track(0)
        return ret


if __name__ == '__main__':
    solution = Solution()
    solution.solveNQueens(4)
