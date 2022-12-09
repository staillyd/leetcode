# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def postorderTraversal(self, root: TreeNode) -> List[int]:
        '''非递归,看成只有三个节点（根节点，左子树，右子树）的树

        @Note:
            根右左->左右根
        '''
        if root is None:
            return []
        s = [root]
        ret = []
        while s:
            node = s.pop()
            ret.append(node.val)
            if node.left:  #注意  先入后出
                s.append(node.left)
            if node.right:
                s.append(node.right)
        return ret[::-1]

    def postorderTraversal_1(self, root: TreeNode) -> List[int]:
        '''后序遍历
        
        @Note:
            递归
        '''
        if root is None:
            return []
        l = self.postorderTraversal(root.left)
        r = self.postorderTraversal(root.right)

        res = []
        res.extend(l)
        res.extend(r)
        res.append(root.val)
        return res
