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

## [最小栈](155.py)
- [Link](https://leetcode-cn.com/problems/min-stack/)
- 设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
  - push(x) —— 将元素 x 推入栈中。
  - pop() —— 删除栈顶的元素。
  - top() —— 获取栈顶元素。
  - getMin() —— 检索栈中的最小元素。
- 用一个辅助栈，辅助栈栈顶存栈当前的最小值，当栈pop时，辅助栈也pop;当栈append的时候,辅助栈append当前最小值

| min       | 6   | 6   | 4   | 3   |
| --------- | --- | --- | --- | --- |
| stack     | 6   | 7   | 4   | 3   |
| min_stack | 6   | 6   | 4   | 3   |

## [最大队列](59.py)
- [Link](https://leetcode-cn.com/problems/dui-lie-de-zui-da-zhi-lcof/)
- 请定义一个队列并实现函数 max_value 得到队列里的最大值，要求函数max_value、push_back 和 pop_front 的均摊时间复杂度都是O(1)。
- 若队列为空，pop_front 和 max_value 需要返回 -1

| max       | 7   | 7   | 4   | 3   |
| --------- | --- | --- | --- | --- |
| queue     | 6   | 7   | 4   | 3   |


- 添加一个辅助队列  [7,4,3]
- 当插入时,如果插入元素>=辅助队首元素,那么将辅助队首移除,直到队首为插入元素
- 当出队时,如果出队元素<辅助队首,只出队,如果出队元素=辅助队首元素,出队并出辅助队

## [用栈实现队列](232.py)
- [Link](https://leetcode-cn.com/problems/implement-queue-using-stacks/)
- 请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）
1. push:往stack1中添加元素
2. **move:当stack2为空时,将stack1的所有元素移到stack2中**
3. pop:**调用move**,stack2进行pop
4. peek:**调用move**,stack2最后一位

## [用队列实现栈](225.py)
- [Link](https://leetcode-cn.com/problems/implement-stack-using-queues/)
- 请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）
1. 使用一个队列即可
2. push:正常push,然后将之前的元素都pop再push,相当于将push之前的元素都挪到后面
   ```python
    def push(self, x: int) -> None:
        self.q.append(x)
        n = len(self.q)
        for i in range(1, n):
            self.q.append(self.q.pop(0))
   ```
3. pop、peek:与正常的一致

## [逆波兰表达式](150.py)
- [Link](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)
- 根据 逆波兰表示法，求表达式的值
- 遍历数组，遇到数字则压入栈中，遇到运算符号，则从栈中弹出右、左操作数，运算过后，将结果压入栈中。遍历结束后，返回栈中的唯一元素。

## [最近的请求次数](933.py)
- [Link](https://leetcode-cn.com/problems/number-of-recent-calls/)
- int ping(int t) 在时间 t 添加一个新请求，其中 t 表示以毫秒为单位的某个时间，并返回过去 3000 毫秒内发生的所有请求数（包括新请求）。确切地说，返回在 [t-3000, t] 内发生的请求数。
```python
def ping(self, t: int) -> int:
    self.q.append(t)
    while self.q[0] < t - 3000:
        self.q.popleft()
    return len(self.q)
```

## [每日温度](739.py)
- [Link](https://leetcode-cn.com/problems/daily-temperatures/)
- 请根据每日 气温 列表 temperatures ，请计算在每一天需要等几天才会有更高的温度。如果气温在这之后都不会升高，请在该位置用 0 来代替。
```python
def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
    '''栈递减,类似滑动窗口,满足条件弹出,不然往里加'''
    ret=[0 for _ in range(len(temperatures))]
    s=[]
    for j in range(len(temperatures)):
        while s and temperatures[j]>temperatures[s[-1]]:#满足条件弹出,直到不满足
            i=s.pop()
            ret[i]=j-i
        s.append(j)
    return ret
```