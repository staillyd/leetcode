# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def insertionSortList(self, head: ListNode) -> ListNode:
        '''插入排序
        
        @Note:
            画图!!!
        '''
        ret = ListNode(0, head)
        last_sorted = head
        cur = head.next
        while cur:
            if last_sorted.val <= cur.val:
                cur = cur.next
                last_sorted = last_sorted.next
                continue

            find = ret.next
            last_find = ret
            while find.val <= cur.val:
                find = find.next
                last_find = last_find.next

            last_sorted.next = cur.next
            cur.next = find
            last_find.next = cur
            cur = last_sorted.next
        return ret.next
