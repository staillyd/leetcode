# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def reverse(self, head: ListNode) -> None:
        ret = None
        while head:
            tmp = head.next
            head.next = ret
            ret = head
            head = tmp
        return ret  #返回自身

    def reorderList(self, head: ListNode) -> None:
        l = head

        slow, fast = head, head.next  #右半部分比左半部分更短，快慢指针求中间位置
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        m = slow.next
        slow.next = None

        m = self.reverse(m)
        while l and m:
            l_tmp = l.next
            m_tmp = m.next

            l.next = m
            m.next = l_tmp

            l = l_tmp
            m = m_tmp
