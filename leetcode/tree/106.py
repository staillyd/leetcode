# Definition for a binary tree node.
class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:

    def buildTree(self, inorder: List[int], postorder: List[int]) -> TreeNode:
        '''传递下标'''
        index = {}  #元素在中序的下标
        for i in range(len(inorder)):
            index[inorder[i]] = i

        def build(inorder: List[int], postorder: List[int], i_l, i_r, p_l, p_r) -> TreeNode:
            if i_l > i_r:
                return None
            root_val = postorder[p_r]
            i = index[root_val]

            return TreeNode(root_val,build(inorder,postorder,i_l,i-1,p_l,p_l+(i-i_l-1)),\
                    build(inorder,postorder,i+1,i_r,p_l+(i-i_l),p_r-1))

        return build(inorder, postorder, 0, len(inorder) - 1, 0, len(postorder) - 1)

    def buildTree_1(self, inorder: List[int], postorder: List[int]) -> TreeNode:
        if len(postorder) == 0:
            return None
        root_val = postorder[-1]
        i = inorder.index(root_val)

        left_inorder = inorder[:i]
        right_inorder = inorder[i + 1:]
        left_postorder = postorder[:i]
        right_postorder = postorder[i:len(postorder) - 1]  #左闭右开!!
        return TreeNode(root_val, self.buildTree(left_inorder, left_postorder),
                        self.buildTree(right_inorder, right_postorder))


if __name__ == '__main__':
    inorder = [9, 3, 15, 20, 7]
    postorder = [9, 15, 7, 20, 3]
    solution = Solution()
    solution.buildTree(inorder, postorder)
