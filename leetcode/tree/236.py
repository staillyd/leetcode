# Definition for a binary tree node.
class TreeNode:

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class Solution:

    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode',
                             q: 'TreeNode') -> 'TreeNode':
        path = []
        ret = []

        def dfs(root, p, q):
            if root is None:
                return

            path.append(root)
            if root.val == p.val or root.val == q.val:
                ret.append(path.copy())

            dfs(root.left, p, q)
            dfs(root.right, p, q)
            path.pop()

        dfs(root, p, q)
        ret_node = None
        for i in range(len(ret[0])):
            if ret[0][i] == ret[1][i]:
                ret_node = ret[0][i]
            else:
                break
        return ret_node
