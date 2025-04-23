# 查找算法
## [二分查找](binary_search.cpp)
- $T(n)=O(nlog(n))$
```c++
int binary_search(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) { // <=
        int m = l + ((r - l) >> 1);
        if (arr[m] > key) {
            r = m - 1;
        } else if (arr[m] < key) {
            l = m + 1;
        } else {
            return m;
        }
    }
    return -1;
}
```

## [查找第一个等于给定值](binary_search_1.cpp)
```c++
int binary_search(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] > key) {
            r = m -1;
        } else if (arr[m] < key) {
            l = m + 1;
        } else {
            if (m == 0 || arr[m] != arr[m - 1]) { // 终止条件
                return m;
            }
            r = m - 1;
        }
    }
    return -1;
}

int binary_search2(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l < r) {   // <
        int m = l + ((r - l) >> 1); // 向下取整
        if (arr[m] < key) {
            l = m + 1;
        } else  { // 找第一个>=key  主要是上一个方法不能应对需要查找元素不相邻的情况
            r = m;
        }
    }
    return (arr[l] == key) ? l : -1;
}
```

## [查找最后一个值等于给定值的元素](binary_search_2.py)
```c++
int binary_search(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) { // <=
        int m = l + ((r - l) >> 1);
        if (arr[m] > key) {
            r = m - 1;
        } else if (arr[m] < key) {
            l = m + 1;
        } else {
            if (m == len - 1 || arr[m] != arr[m + 1]) {
                return m;
            }
            l = m + 1;
        }
    }
    return -1;
}

int binary_search2(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l < r) {  // <
        int m = l + (r - l + 1) / 2; // 向上取整
        if (arr[m] > key) {
            r = m - 1;
        } else  { // 找最后一个<=key   主要是上一个方法不能应对需要查找元素不相邻的情况, 如找不动点
            l = m;
        }
    }
    return (arr[l] == key) ? l : -1;
}
```

## [查找第一个大于等于给定值的元素](binary_search_3.cpp)
```c++
int binary_search(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] < key) {
            l = m + 1;
        } else {
            if (m == 0 || arr[m - 1] < key) {
                return m;
            }
            r = m - 1;
        }
    }
    return -1;
}
```

## [查找最后一个小于等于给定值的元素](binary_search_4.py)
```c++
int binary_search(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (arr[m] > key) {
            r = m - 1;
        } else {
            if (m == len - 1 || arr[m + 1] > key) {
                return m;
            }
            l = m + 1;
        }
    }
    return -1;
}
```

## [在排序数组中查找元素的第一个和最后一个位置](34.py)
```python
def searchRange(self, nums: List[int], target: int) -> List[int]:
    '''在排序数组中查找元素的第一个和最后一个位置'''
    first,last=-1,-1
    # 找第一个
    l,r=0,len(nums)-1
    while l<=r:
        m=(l+r)//2
        if nums[m]<target:
            l=m+1
        elif nums[m]>target:
            r=m-1
        else:
            if m==0 or nums[m-1]!=target:
                first=m
                break
            r=m-1
    
    if first==-1:
        return [-1,-1]
    # 找最后一个
    l,r=first,len(nums)-1
    while l<=r:
        m=(l+r)//2
        if nums[m]<target:
            l=m+1
        elif nums[m]>target:
            r=m-1
        else:
            if m==len(nums)-1 or nums[m+1]!=target:
                last=m
                break
            l=m+1
    return [first,last]
```

## [x 的平方根](69.py)
```python
def mySqrt(self, x: int) -> int:
    '''求平方根'''
    l,r=0,x
    ret=-1
    while l<=r:
        m=(l+r)//2
        this_product=m*m
        if this_product<x:
            ret=m
            l=m+1
        elif this_product>x:
            r=m-1
        else:
            return m
    return ret
```

## [寻找峰值](162.py)
- [Link](https://leetcode-cn.com/problems/find-peak-element/submissions/)
- 峰值元素是指其值大于左右相邻值的元素。
- 给你一个无重复元素的输入数组 nums，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回 任何一个峰值 所在位置即可。可以假设 nums[-1] = nums[n] = -∞ 。
1. 找最大值
2. 遍历找满足条件的
3. 二分法:比较m与m+1,更改左右边界
```python
def findPeakElement(self, nums: List[int]) -> int:
    '''返回索引,寻找无重复元素中的极大值'''
    l,r=0,len(nums)-1
    while l<r:#注意条件
        m=(l+r)//2
        if nums[m]>nums[m+1]:#比较m与m+1
            r=m
        else:
            l=m+1
    return l
```

## [寻找第一个错误版本](278.py)
- [Link](https://leetcode-cn.com/problems/first-bad-version/)
- 假设你有 n 个版本 [1, 2, ..., n]，你想找出导致之后所有版本出错的第一个错误的版本。
- 你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version 是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用 API 的次数。
```python
# The isBadVersion API is already defined for you.
# @param version, an integer
# @return an integer
# def isBadVersion(version):

class Solution:
    def firstBadVersion(self, n):
        """
        :type n: int
        :rtype: int
        """
        l,r=1,n
        while l<r:
            m=(l+r)//2
            ret=isBadVersion(m)
            if ret:
                r=m
            else:
                l=m+1
        return l
```

## [不动点](1064.py)
- [Link](https://leetcode-cn.com/problems/fixed-point/)
- 给定已经按 升序 排列、由不同整数组成的数组 arr，返回满足 arr[i] == i 的最小索引 i。如果不存在这样的 i，返回 -1
```python
def fixedPoint(self, arr: List[int]) -> int:
    '''寻找满足 arr[i] == i 的最小索引 i'''
    l,r=0,len(arr)-1
    while l<r:
        m=(l+r)//2
        if arr[m]<m:
            l=m+1
        elif arr[m]==m:
            r=m#要找最小索引
        else:
            r=m-1
    if arr[l]!=l:
        return -1
    else:
        return l
```

## [搜索旋转排序数组](33.cpp)
- [Link](https://leetcode.cn/problems/search-in-rotated-sorted-array/description/?envType=study-plan-v2&envId=top-100-liked)
- 在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。
- 给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。
- 你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
- 看哪半区是有序的, 再看target在哪半区
```cpp
int search(std::vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l <= r) {
        int m = l + ((r - l) >> 1);
        if (nums[m] == target) {
            return m;
        }
        if (nums[0] <= nums[m]) {                         // 左半区有序
            if (nums[0] <= target && target < nums[m]) {  // target在[0, m]对应区间, 由于nums[m]不等于target可以不写=
                r = m - 1;
            } else {
                l = m + 1;
            }
        } else {  // 右半区有序
            if (nums[m] < target && target <= nums[nums.size() - 1]) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
    }
    return -1;
}
```


## [寻找旋转排序数组中的最小值](153.py)
- [Link](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array/)
- 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
  - 若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
  - 若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]
  - 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。
  - 给你一个元素值 互不相同 的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。
```python
def findMin(self, nums: List[int]) -> int:
    '''寻找旋转排序数组中的最小值
    
    @Note:
        二分,若 nums[m] > nums[r]，说明最小值在 m 的右边，否则说明最小值在 m 的左边（包括 m）
    '''
    l,r=0,len(nums)-1
    while l<r:
        m=(l+r)//2
        if nums[m]>nums[r]:
            l=m+1
        else:
            r=m
    return nums[l]
```

## [寻找旋转排序数组中的最小值 II](154.py)
- [Link](https://leetcode-cn.com/problems/find-minimum-in-rotated-sorted-array-ii/)
- 已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转 后，得到输入数组。例如，原数组 nums = [0,1,4,4,5,6,7] 在变化后可能得到：
  - 若旋转 4 次，则可以得到 [4,5,6,7,0,1,4]
  - 若旋转 7 次，则可以得到 [0,1,4,4,5,6,7]
  - 注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]] 。
  - 给你一个可能存在 **重复** 元素值的数组 nums ，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的 最小元素 。
```python
def findMin(self, nums: List[int]) -> int:
    '''寻找旋转排序数组中的最小值
    
    @Note:
        若 nums[m] > nums[r]，说明最小值在 m 的右边；若 nums[m] < nums[r]，说明最小值在 m 的左边（包括 m）；若相等，无法判断，直接将 r 减 1。循环比较。
        m与r比较,返回l(l为查找索引)
    '''
    l,r=0,len(nums)-1
    while l<r:
        m=(l+r)//2
        if nums[m]>nums[r]:
            l=m+1
        elif nums[m]<nums[r]:
            r=m
        else:
            r-=1#为应对3、3、1、3情况
    return nums[l]
```
