# Definition for singly-linked list.
class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:

    def hasCycle(self, head: ListNode) -> bool:
        '''快慢指针'''
        slow, fast = head, head  #注意这里和查找中间位置的初始值不同  查找中间位置的fast=head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True
        return False
