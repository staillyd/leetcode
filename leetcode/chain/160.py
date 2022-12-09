# Definition for singly-linked list.
class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:

    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        '''判断链表是否相交
        
        @Note:
            a1->a2->...None->b1->b2->...None
            b1->b2->...None->a1->a2->...None
            这样的总长一样,且末尾都为None.注意要有None!!
        '''
        cur_A = headA
        cur_B = headB
        while cur_A or cur_B:
            if cur_A == cur_B:
                return cur_B
            cur_A = cur_A.next if cur_A else headB
            cur_B = cur_B.next if cur_B else headA
        return None
