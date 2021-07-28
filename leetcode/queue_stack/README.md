# 栈和队列
## [有效的括号](20.py)
- [Link](https://leetcode-cn.com/problems/valid-parentheses/)
- 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
- 用栈存左括号,当出现右括号时弹出(如果此时为空则False),最后栈不为空为False
```python
def isValid(self, s: str) -> bool:
    stack=[]
    for this_s in s:
        if this_s=='[':
            stack.append(this_s)
        elif this_s=='{':
            stack.append(this_s)
        elif this_s=='(':
            stack.append(this_s)
        else:
            if len(stack)==0:#注意
                return False
            pop=stack.pop()
            if this_s==']' and pop!='[':
                return False
            if this_s=='}' and pop!='{':
                return False
            if this_s==')' and pop!='(':
                return False
    if len(stack)!=0:#注意
        return False
    return True
```