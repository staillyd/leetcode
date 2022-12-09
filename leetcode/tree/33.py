class Solution:

    def verifyPostorder(self, postorder: List[int]) -> bool:
        '''左右根
        
        @Note:
            <,>,=
        '''
        if len(postorder) == 0:
            return True
        root_val = postorder[-1]
        right_start = len(postorder) - 1
        for i in range(len(postorder) - 1):
            if postorder[i] > root_val:
                right_start = i
                break
        left_postorder = postorder[:right_start]
        right_postorder = postorder[right_start:len(postorder) - 1]
        for i in range(right_start, len(postorder) - 1):
            if postorder[i] < root_val:
                return False
        return self.verifyPostorder(left_postorder) and self.verifyPostorder(
            right_postorder)
