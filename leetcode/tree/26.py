# Definition for a binary tree node.
class TreeNode:

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:

    def is_contain(self, A: TreeNode, B: TreeNode) -> bool:
        '''B是否为A根节点相同的子树'''
        if B is None:  #特别注意
            return True
        if A and B and A.val==B.val and\
            self.is_contain(A.left,B.left) and self.is_contain(A.right,B.right):
            return True
        return False

    def isSubStructure(self, A: TreeNode, B: TreeNode) -> bool:
        if B is None:  #None不是任何树的子树
            return False
        return self.is_contain(A, B) or (A is not None and
                                         (self.isSubStructure(A.left, B) or self.isSubStructure(A.right, B)))
