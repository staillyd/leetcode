from typing import List


class Solution:

    def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
        '''合并两个有序数组
        
        @Note:
            类似归并排序，从后往前
        '''
        i, j, k = m - 1, n - 1, m + n - 1
        if n == 0:
            return
        while True:
            if nums1[i] > nums2[j]:
                nums1[k] = nums1[i]
                k -= 1
                i -= 1
            else:
                nums1[k] = nums2[j]
                j -= 1
                k -= 1
            if i == -1 or j == -1:
                break
        if i == -1:
            nums1[:j + 1] = nums2[:j + 1]  #注意左闭右开


if __name__ == '__main__':
    nums1 = [1, 0]  #[int(x) for x  in input().strip().split(' ')]
    m = 1  #int(input().strip())
    nums2 = [2]  #[int(x) for x  in input().strip().split(' ')]
    n = 1  #int(input().strip())
    solution = Solution()
    solution.merge(nums1, m, nums2, n)
    print(nums1)
