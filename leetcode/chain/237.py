# Definition for singly-linked list.
class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:

    def deleteNode(self, node):
        """删除传入的node节点"""
        node.val = node.next.val
        node.next = node.next.next
