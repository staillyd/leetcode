# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def rightSideView(self, root: TreeNode) -> List[int]:
        '''层序遍历的最右侧'''
        if root is None:
            return []
        q = [root]  #队列
        ret = []
        while q:
            size = len(q)
            for i in range(size):
                node = q.pop(0)

                if i == size - 1:
                    ret.append(node.val)

                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
        return ret
