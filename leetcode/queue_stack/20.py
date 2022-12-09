class Solution:

    def isValid(self, s: str) -> bool:
        stack = []
        for this_s in s:
            if this_s == '[':
                stack.append(this_s)
            elif this_s == '{':
                stack.append(this_s)
            elif this_s == '(':
                stack.append(this_s)
            else:
                if len(stack) == 0:  #注意
                    return False
                pop = stack.pop()
                if this_s == ']' and pop != '[':
                    return False
                if this_s == '}' and pop != '{':
                    return False
                if this_s == ')' and pop != '(':
                    return False
        if len(stack) != 0:  #注意
            return False
        return True
