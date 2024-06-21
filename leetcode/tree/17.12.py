# Definition for a binary tree node.
class TreeNode:

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:

    def convertBiNode(self, root: TreeNode) -> TreeNode:
        '''中序遍历:头节点、上一节点指针'''

        def dfs(root):
            if root is None:
                return
            dfs(root.left)
            if self.head is None:
                self.head = root  #第一次调用的地方是头节点
            else:
                self.pre.right = root
            root.left = None
            self.pre = root
            dfs(root.right)

        self.head = None
        self.pre = None
        dfs(root)
        return self.head

    def convertBiNode(self, root: TreeNode) -> TreeNode:
        if root is None:
            return None

        l = self.convertBiNode(root.left)
        r = self.convertBiNode(root.right)

        ret = l
        while l and l.right:
            l = l.right

        if l:
            l.right = root
        else:
            ret = root
        root.left = None
        root.right = r
        return ret
