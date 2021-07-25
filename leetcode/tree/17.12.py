# Definition for a binary tree node.
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def convertBiNode(self, root: TreeNode) -> TreeNode:
        if root is None:
            return None
        
        l=self.convertBiNode(root.left)
        r=self.convertBiNode(root.right)

        ret=l
        while l and l.right:
            l=l.right
        
        if l:
            l.right=root
        else:
            ret=root
        root.left=None
        root.right=r
        return ret