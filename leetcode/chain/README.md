# 链表
## [两数相加](2.py)
- [Link](https://leetcode-cn.com/problems/add-two-numbers/)
- 给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。
- 请你将两个数相加，并以相同形式返回一个表示和的链表。
- 你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
```python
def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
    '''两数相加'''
    ret=ListNode()
    last=ret#上一节点
    add=0#进位
    while l1 or l2 or add!=0:#在l1 l2 都为None并且进位(add)为0时退出, add不为0应对999+9999这种情况
        sum=(0 if l1 is None else l1.val)+(0 if l2 is None else l2.val)+add
        add,sum=divmod(sum,10)#整除与余数

        last.next=ListNode(sum)
        last=last.next#挪位

        l1=None if l1 is None else l1.next#挪位
        l2=None if l2 is None else l2.next#挪位
    return ret.next#舍弃初始的节点
```
