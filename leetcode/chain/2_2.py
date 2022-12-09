# Definition for singly-linked list.
class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:

    def kthToLast(self, head: ListNode, k: int) -> int:
        '''返回倒数第 k 个节点
        
        @Note:
            p,q都指向head,p先走k步,然后pq都往前走,直到p为None
            快慢指针
        '''
        p, q = head, head
        for i in range(k):
            p = p.next
        while p is not None:
            p = p.next
            q = q.next
        return q.val
