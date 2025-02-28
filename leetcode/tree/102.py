# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def levelOrder(self, root: TreeNode) -> List[List[int]]:
        '''队列'''
        if root is None:
            return []
        q = [root]
        ret = []
        while q:
            size = len(q)  #当前层的个数!!!
            t = []
            for _ in range(size):
                node = q.pop(0)
                t.append(node.val)

                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            ret.append(t)
        return ret
