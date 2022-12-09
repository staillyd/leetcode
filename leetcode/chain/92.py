# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def reverse(self, head: ListNode) -> ListNode:
        '''反转链表'''
        ret = None
        while head:
            tmp = head.next
            head.next = ret
            ret = head
            head = tmp
        return ret

    def reverseBetween(self, head: ListNode, left: int, right: int) -> ListNode:
        ret = ListNode(0, head)
        i = 0
        last = ret
        start, end = None, None
        while head:  #画图!!!
            i += 1
            if i < left:
                last = last.next
            if i == left:
                start = head
            if i == right:
                end = head.next
                head.next = None
                break
            head = head.next

        l = self.reverse(start)
        last.next = l
        start.next = end

        return ret.next
