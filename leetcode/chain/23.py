# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def merge2Lists(self, l1: ListNode, l2: ListNode) -> ListNode:
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
        last.next = l1 if l1 is not None else l2
        return ret.next

    def mergeKLists_all(self, lists: List[ListNode]) -> ListNode:
        '''合并K个有序链表'''
        if len(lists) == 0 or lists is None:
            return None
        for i in range(1, len(lists)):
            lists[i] = self.merge2Lists(lists[i - 1], lists[i])
        return lists[len(lists) - 1]

    def mergeKLists(self, lists: List[ListNode]) -> ListNode:
        '''合并K个有序链表
        
        @Note:
            归并排序
        '''
        if len(lists) == 0 or lists is None:
            return None
        return self.mergeKLists_sort(lists, 0, len(lists) - 1)

    def mergeKLists_sort(self, lists: List[ListNode], l, r) -> ListNode:
        if l == r:
            return lists[l]  #注意返回值,merge2Lists会更改原链表
        m = (l + r) // 2
        l1 = self.mergeKLists_sort(lists, l, m)
        l2 = self.mergeKLists_sort(lists, m + 1, r)
        return self.merge2Lists(l1, l2)
