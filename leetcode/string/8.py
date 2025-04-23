class Solution:

    def myAtoi(self, s: str) -> int:
        '''字符串转换整数 (atoi)'''
        if len(s) == 0:  #特例
            return 0
        ret = 0
        i = 0
        while s[i] == ' ':  #去' '
            i += 1
            if i == len(s):  #特例
                return 0
        pos_neg = -1 if s[i] == '-' else 1  #正负号
        if s[i] in ['-', '+']:  #如果是正负号往右走!!!
            i += 1
        near_overflow_data = 2**31 // 10
        while i < len(s):
            if not s[i].isdigit():
                return pos_neg * ret

            int_char = int(s[i])
            # 溢出判断
            if ret > near_overflow_data or (ret == near_overflow_data and int_char > 7):  #数字部分超过2147483647那么是边界值
                return 2**31 - 1 if pos_neg > 0 else -2**31  #-2147483648~2147483647

            ret = 10 * ret + int_char
            i += 1
        return ret * pos_neg


if __name__ == '__main__':
    string = input().strip()
    solution = Solution()
    print(solution.myAtoi(string))
