# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def removeElements(self, head: ListNode, val: int) -> ListNode:
        '''移除链表元素'''
        ret = ListNode()
        last = ret
        while head is not None:
            if head.val == val:  #满足删除条件
                head = head.next
                last.next = head  #指向
            else:
                last.next = head
                last = last.next  #挪位
                head = head.next
        return ret.next
