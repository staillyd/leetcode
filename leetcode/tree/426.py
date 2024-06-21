# Definition for a Node.
class Node:

    def __init__(self, val, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def treeToDoublyList(self, root: 'Node') -> 'Node':

        def dfs(root):
            '''中序'''
            if root is None:
                return None

            dfs(root.left)
            if self.head is None:
                self.head = root  #头节点
            else:
                self.pre.right, root.left = root, self.pre
            self.pre = root  #上一节点
            dfs(root.right)

        self.pre = None
        self.head = None
        dfs(root)
        if self.head:
            self.head.left, self.pre.right = self.pre, self.head
        return self.head
