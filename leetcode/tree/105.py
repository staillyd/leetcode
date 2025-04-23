# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def buildTree(self, preorder: List[int], inorder: List[int]) -> TreeNode:
        '''可以考虑传递下标，减少数组拷贝的时间'''
        if len(preorder) == 0:
            return None
        root_val = preorder[0]
        i = inorder.index(root_val)
        left_inorder = inorder[:i]
        right_inorder = inorder[i + 1:]
        left_preorder = preorder[1:1 + i]
        right_preorder = preorder[1 + i:]

        return TreeNode(root_val, self.buildTree(left_preorder, left_inorder),
                        self.buildTree(right_preorder, right_inorder))
