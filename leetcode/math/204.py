class Solution:

    def countPrimes(self, n: int) -> int:
        cnt = 0
        flag = [0 for _ in range(n)]
        for num in range(2, n):
            if flag[i] == 0:
                cnt += 1
                for i in range(num * num, n, num):
                    flag[i] = 1
        return cnt
