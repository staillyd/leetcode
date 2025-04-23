# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def swapPairs(self, head: ListNode) -> ListNode:
        '''两两交换链表中的节点
        
        @Note:
            新增虚拟节点
        '''
        ret = ListNode()
        ret.next = head
        last = ret
        while head is not None:
            tmp = head.next
            if tmp is not None:
                head.next = tmp.next
                tmp.next = head
                last.next = tmp
                last = head  # 挪位
                head = head.next  #挪位
            else:
                break
        return ret.next
