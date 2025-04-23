# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def inorderTraversal(self, root: TreeNode) -> List[int]:
        '''中序遍历,左根右   []   [左根] -> [右]'''
        if root is None:
            return []

        ret = []
        s = []
        while root or s:  #注意和前序后序不同
            if root:
                s.append(root)
                root = root.left
            else:
                root = s.pop()
                ret.append(root.val)
                root = root.right
        return ret

    def inorderTraversal_1(self, root: TreeNode) -> List[int]:
        if root is None:
            return []

        l = self.inorderTraversal(root.left)
        r = self.inorderTraversal(root.right)

        ret = []
        ret.extend(l)
        ret.append(root.val)
        ret.extend(r)
        return ret
