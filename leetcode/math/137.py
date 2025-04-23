class Solution:

    def singleNumber(self, nums: List[int]) -> int:
        count = [0] * 32  #各 二进制位 出现的次数
        for num in nums:
            for i in range(32):
                count[i] += num & 1
                num >>= 1

        ret = 0
        for i in range(32):
            ret <<= 1  #注意先左移
            ret |= count[31 - i] % 3
        return ret if count[31] % 3 == 0 else ~(ret ^ 0xffffffff
                                               )  #python位数高,如果出现的是负数,那么需要先对0~32位取反,在对当前数进行取反(符号位及从末尾开始到第一个非0数)
