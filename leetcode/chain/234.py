# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def reverse(self, head: ListNode) -> ListNode:
        ret = None
        while head:
            tmp = head.next
            head.next = ret
            ret = head
            head = tmp
        return ret

    def isPalindrome(self, head: ListNode) -> bool:
        '''快慢指针求中间,反转右半,进行顺序判断'''
        slow, fast = head, head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        m = slow.next
        slow.next = None

        m = self.reverse(m)
        while head and m:
            if head.val != m.val:
                return False
            head = head.next
            m = m.next
        return True
