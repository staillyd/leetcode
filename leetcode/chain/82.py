# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def deleteDuplicates(self, head: ListNode) -> ListNode:
        '''删除排序链表中的重复元素 II'''
        ret = ListNode()
        last = ret
        while head is not None:
            flag = False  #当前位置是否删除了相同节点
            while head.next is not None and head.val == head.next.val:  #删除相同的节点
                head.next = head.next.next
                flag = True
            if flag:
                head = head.next
                last.next = head
            else:
                last.next = head
                last = last.next  #挪位，只有此处进行last的挪位
                head = head.next
        return ret.next
