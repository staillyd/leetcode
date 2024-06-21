# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def levelOrderBottom(self, root: TreeNode) -> List[List[int]]:
        '''层次遍历的逆序'''
        if root is None:
            return []
        q = [root]
        ret = []
        while q:
            size = len(q)  # 当前层节点的个数
            t = []
            for _ in range(size):
                node = q.pop(0)
                t.append(node.val)

                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            ret.append(t)
        return ret[::-1]
