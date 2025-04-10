# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        '''两数之和'''
        ret = ListNode()
        last = ret  #上一节点
        add = 0  #进位
        while l1 or l2 or add != 0:  #在l1 l2 都为None并且进位(add)为0时退出, add不为0应对999+9999这种情况
            sum = (0 if l1 is None else l1.val) + (0 if l2 is None else l2.val) + add
            add, sum = divmod(sum, 10)  #整除与余数

            last.next = ListNode(sum)
            last = last.next  #挪位

            l1 = None if l1 is None else l1.next  #挪位
            l2 = None if l2 is None else l2.next  #挪位
        return ret.next  #舍弃初始的节点
