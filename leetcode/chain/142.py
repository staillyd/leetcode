# Definition for singly-linked list.
class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:

    def detectCycle(self, head: ListNode) -> ListNode:
        slow, fast = head, head
        cycle = False
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

            if slow == fast:
                cycle = True
                break

        if not cycle:
            return None

        p = head
        while p != slow:
            p = p.next
            slow = slow.next
        return slow
