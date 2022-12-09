# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def preorderTraversal(self, root: TreeNode) -> List[int]:
        '''前序  [根、左、右]
        
        @Note:
            非递归
        '''
        if root is None:
            return []
        ret = []
        s = [root]  #stack!!
        while s:
            node = s.pop()
            ret.append(node.val)
            if node.right:  #注意  先入后出
                s.append(node.right)
            if node.left:
                s.append(node.left)
        return ret

    def preorderTraversal_1(self, root: TreeNode) -> List[int]:
        '''前序  [根、左、右]
        
        @Note:
            看成只有三个节点（根节点，左子树，右子树）的树，不需要展开，直接调用
        '''
        if root is None:
            return []
        l = self.preorderTraversal(root.left)
        r = self.preorderTraversal(root.right)

        ret = []
        ret.append(root.val)
        ret.extend(l)
        ret.extend(r)

        return ret
