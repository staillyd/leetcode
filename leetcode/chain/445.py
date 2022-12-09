# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def addTwoNumbers(self, l1: ListNode, l2: ListNode) -> ListNode:
        '''两数之和II,高位指向低位'''
        reverse_l1 = []  #stack
        while l1 is not None:
            reverse_l1.append(l1.val)
            l1 = l1.next

        reverse_l2 = []  #stack
        while l2 is not None:
            reverse_l2.append(l2.val)
            l2 = l2.next

        last = None
        add = 0
        while len(reverse_l1) != 0 or len(reverse_l2) != 0 or add != 0:
            sum=(0 if len(reverse_l1)==0 else reverse_l1.pop()) + \
                (0 if len(reverse_l2)==0 else reverse_l2.pop()) + add# stack进行顺序翻转

            add, sum = divmod(sum, 10)

            ret = ListNode(sum, last)
            last = ret
        return ret
