from typing import List


class Solution:

    def solveSudoku(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """

        def valid(row, col, c):
            # 行判断
            for i in range(9):
                if board[row][i] == c:
                    return False

            # 列判断
            for i in range(9):
                if board[i][col] == c:
                    return False

            # 9格
            s_i, s_j = row // 3 * 3, col // 3 * 3
            for i in range(s_i, s_i + 3):
                for j in range(s_j, s_j + 3):
                    if board[i][j] == c:
                        return False

            return True

        def back_track():
            for i in range(len(board)):
                for j in range(len(board[0])):
                    if board[i][j] != '.':  #存在数字
                        continue
                    for c in ['1', '2', '3', '4', '5', '6', '7', '8',
                              '9']:  #(i, j) 这个位置放c是否合适
                        if not valid(i, j, c):  #剪枝
                            continue
                        board[i][j] = c  # 放置c
                        if back_track():
                            return True
                        board[i][j] = '.'
                    return False
            return True

        back_track()


if __name__ == '__main__':
    solution = Solution()
    solution.solveSudoku([["5", "3", ".", ".", "7", ".", ".", ".", "."],
                          ["6", ".", ".", "1", "9", "5", ".", ".", "."],
                          [".", "9", "8", ".", ".", ".", ".", "6", "."],
                          ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
                          ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
                          ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
                          [".", "6", ".", ".", ".", ".", "2", "8", "."],
                          [".", ".", ".", "4", "1", "9", ".", ".", "5"],
                          [".", ".", ".", ".", "8", ".", ".", "7", "9"]])
