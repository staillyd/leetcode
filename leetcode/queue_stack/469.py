class Solution:

    def nextGreaterElement(self, nums1: List[int],
                           nums2: List[int]) -> List[int]:
        '''单调减栈<     左<   右<='''
        s = []
        dic = {}
        for i, num in enumerate(nums2):
            while s and s[-1] < num:
                dic[s.pop()] = num
            s.append(num)
        ret = [-1 for _ in range(len(nums1))]
        for i, num in enumerate(nums1):
            if num in dic:
                ret[i] = dic[num]
        return ret
