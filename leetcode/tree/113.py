# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def pathSum(self, root: TreeNode, targetSum: int) -> List[List[int]]:
        '''dfs+路径记录'''
        path = []
        ret = []

        def dfs(root, targetSum):
            if root is None:
                return

            path.append(root.val)
            if root.val == targetSum and root.left is None and root.right is None:
                ret.append(path.copy())  #!!!!拷贝

            dfs(root.left, targetSum - root.val)
            dfs(root.right, targetSum - root.val)
            path.pop()

        dfs(root, targetSum)
        return ret
