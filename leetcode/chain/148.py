# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def merge2List(self, l1: ListNode, l2: ListNode) -> ListNode:
        ret = ListNode()
        last = ret
        while l1 and l2:
            if l1.val <= l2.val:
                last.next = l1
                l1 = l1.next
            else:
                last.next = l2
                l2 = l2.next
            last = last.next
        last.next = l1 if l2 is None else l2
        return ret.next

    def sortList(self, head: ListNode) -> ListNode:
        if head is None or head.next is None:
            return head

        # 快慢指针求中间位置
        slow = head
        fast = head.next  #!!!很关键
        while fast is not None and fast.next is not None:
            slow = slow.next
            fast = fast.next.next
        m = slow.next
        slow.next = None  #关键

        l1 = self.sortList(head)
        l2 = self.sortList(m)
        return self.merge2List(l1, l2)
