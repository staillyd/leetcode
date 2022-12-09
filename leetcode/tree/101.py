# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def isSymmetric(self, root: TreeNode) -> bool:
        '''非递归,从root开始,把比较顺序写下,然后考虑如何用队列或栈实现这个顺序'''
        if root is None:
            return True
        s = [root.left, root.right]
        while s:
            node1 = s.pop()
            node2 = s.pop()
            if node1 is None and node2 is None:
                pass
            elif (node1 and node2 is None) or (node2 and node1 is None):
                return False
            else:
                if node1.val != node2.val:
                    return False
                s.append(node1.left)
                s.append(node2.right)
                s.append(node1.right)
                s.append(node2.left)
        return True

    def is_symmetric(self, left: TreeNode, right: TreeNode) -> bool:
        '''左树是否镜像于右树'''
        if left is None and right is None:
            return True

        if left is not None and right is not None and left.val ==right.val and \
            self.is_symmetric(left.left,right.right) and self.is_symmetric(left.right,right.left):
            return True

        return False

    def isSymmetric_1(self, root: TreeNode) -> bool:
        '''递归'''
        if root is None:
            return True
        return self.is_symmetric(root.left, root.right)
