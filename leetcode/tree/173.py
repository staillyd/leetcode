# Definition for a binary tree node.
from typing import List


class TreeNode:

    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class BSTIterator:

    def __init__(self, root: TreeNode):

        def inorder(root) -> List:
            if root is None:
                return []
            l = inorder(root.left)
            r = inorder(root.right)

            ret = []
            ret.extend(l)
            ret.append(root.val)
            ret.extend(r)

            return ret

        self.inorder_list = inorder(root)
        self.cur = 0

    def next(self) -> int:
        ret = self.inorder_list[self.cur]
        self.cur += 1
        return ret

    def hasNext(self) -> bool:
        return self.cur < len(self.inorder_list)


# Your BSTIterator object will be instantiated and called as such:
# obj = BSTIterator(root)
# param_1 = obj.next()
# param_2 = obj.hasNext()
