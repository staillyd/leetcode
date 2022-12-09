# Definition for singly-linked list.
class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:

    def reversePrint(self, head: ListNode) -> List[int]:
        '''从尾到头打印链表'''
        ret = []
        while head is not None:
            ret.append(head.val)
            head = head.next
        return ret[::-1]
