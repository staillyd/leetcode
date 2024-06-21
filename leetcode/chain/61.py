# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:

    def rotateRight(self, head: ListNode, k: int) -> ListNode:
        cur = head  #取余
        n = 0
        while cur:
            cur = cur.next
            n += 1
        if n == 1 or n == 0:
            return head  #特判
        k = k % n
        if k == 0:
            return head  #特判

        # 快位置
        ret = ListNode(0, head)
        last_fast = ret
        fast = head
        while k != 0:
            k -= 1
            fast = fast.next
            last_fast = last_fast.next

        # 快慢位置同时跑
        last_find = ret
        find = head
        while fast:
            last_fast = last_fast.next
            fast = fast.next

            find = find.next
            last_find = last_find.next
        # 拼接
        last_fast.next = head
        last_find.next = None
        head = find
        return head


if __name__ == '__main__':
    l = ListNode(5)
    l = ListNode(4, l)
    l = ListNode(3, l)
    l = ListNode(2, l)
    l = ListNode(1, l)
    k = 2
    solution = Solution()
    solution.rotateRight(l, 2)
