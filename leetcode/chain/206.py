# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def reverseList(self, head: ListNode) -> ListNode:
        '''反转链表'''
        ret = None
        while head:
            tmp = head.next
            head.next = ret
            ret = head
            head = tmp
        return ret
