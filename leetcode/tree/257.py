# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def binaryTreePaths(self, root: TreeNode) -> List[str]:
        '''深度优先+路径记录'''
        path = []  #路径记录  全局变量，然后在dfs后pop最后一位
        ret = []

        def dfs(root: TreeNode):
            if root is None:
                return
            path.append(str(root.val))  # 前序
            if root.left is None and root.right is None:  #输出  画1～3层的树
                ret.append('->'.join(path))

            dfs(root.left)
            dfs(root.right)
            path.pop()  # 不pop的话path其实是前序遍历

        dfs(root)
        return ret
