# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def minDepth(self, root: TreeNode) -> int:
        if root is None:
            return 0
        if root.left is not None and root.right is None:  #较高一层的值
            return 1 + self.minDepth(root.left)
        if root.right is not None and root.left is None:
            return 1 + self.minDepth(root.right)
        return 1 + min(self.minDepth(root.left), self.minDepth(root.right))
