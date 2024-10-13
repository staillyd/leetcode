# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def oddEvenList(self, head: ListNode) -> ListNode:
        '''奇偶链表
        
        @Note:
            画图
        '''
        if head is None or head.next is None:
            return head
        odd = head
        even = head.next
        start_even = even
        last_odd = None
        while odd and even:
            odd.next = even.next
            last_odd = odd
            odd = odd.next

            even.next = odd.next if odd else None  #注意
            even = even.next
        if last_odd.next:  #奇数个
            last_odd = last_odd.next
        last_odd.next = start_even  #!!!注意
        return head


if __name__ == '__main__':
    l = ListNode(5)
    l = ListNode(4, l)
    l = ListNode(3, l)
    l = ListNode(2, l)
    l = ListNode(1, l)
    solution = Solution()
    solution.oddEvenList(l)
