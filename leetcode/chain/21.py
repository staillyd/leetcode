# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def mergeTwoLists(self, l1: ListNode, l2: ListNode) -> ListNode:
        '''合并两个有序链表'''
        ret = ListNode()
        last = ret
        while l1 is not None and l2 is not None:
            if l1.val <= l2.val:
                last.next = l1
                l1 = l1.next  #挪位
            else:
                last.next = l2
                l2 = l2.next  #挪位
            last = last.next
        last.next = l1 if l1 is not None else l2  #剩余长度
        return ret.next
