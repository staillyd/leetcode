from typing import List


class Solution:

    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        direct = 0
        output_arr = []
        sx, sy, ex, ey = 0, 0, len(matrix) - 1, len(matrix[0]) - 1
        while sx <= ex and sy <= ey:
            if direct == 0:
                output_arr.extend(matrix[sx][sy:ey + 1])
                sx += 1
                direct = 1
            elif direct == 1:
                for x in range(sx, ex + 1):
                    output_arr.append(matrix[x][ey])
                ey -= 1
                direct = 2
            elif direct == 2:
                for y in range(sy, ey + 1)[::-1]:
                    output_arr.append(matrix[ex][y])
                ex -= 1
                direct = 3
            elif direct == 3:
                for x in range(sx, ex + 1)[::-1]:
                    output_arr.append(matrix[x][sy])
                sy += 1
                direct = 0
        return output_arr


if __name__ == '__main__':
    m, n = [int(x) for x in input().strip().split(' ')]
    matrix = []
    for i in range(m):
        matrix.append([int(x) for x in input().strip().split(' ')])
    solution = Solution()
    matrix = solution.spiralOrder(matrix)
    print(matrix)
