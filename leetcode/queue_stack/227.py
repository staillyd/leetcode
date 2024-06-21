class Solution:

    def calculate(self, s: str) -> int:
        pre_sign = '+'
        stack = []
        num = 0
        for i, this_c in enumerate(s):
            if this_c.isdigit():
                num = 10 * num + int(this_c)
            if (not this_c.isdigit() and this_c != ' '
               ) or i == len(s) - 1:  #注意最后一个数字也要进行运算,注意空格忽略不是最后一位的空格
                if pre_sign == '+':
                    stack.append(num)
                elif pre_sign == '-':
                    stack.append(-num)
                elif pre_sign == '*':
                    stack.append(stack.pop() * num)
                elif pre_sign == '/':
                    stack.append(int(stack.pop() /
                                     num))  #注意不能用//,//为向下取整,如果前面为负数-3//2=-2

                pre_sign = this_c
                num = 0
        ret = 0  #对栈内剩余结果计算结果
        while stack:
            ret += stack.pop()
        return ret


if __name__ == '__main__':
    solution = Solution()
    print(solution.calculate('3/2 '))
