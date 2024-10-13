# 查找算法
## [二分查找](binary_search.cpp)
- $T(n)=O(nlog(n))$
```c++
int binary_search(int arr[], int len, int key) {
    int l = 0, r = len - 1;
    while (l <= r) { // <=
        int m = l + (r - l) / 2;
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
        int m = l + (r - l) / 2;
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
        int m = l + (r - l) / 2; // 向下取整
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
        int m = l + (r - l) / 2;
        if (arr[m] > key) {
            r = m - 1;
        } else if (arr[m] < key) {
            l = m + 1;
        } else {
            if (m + 1 < len && arr[m] != arr[m + 1]) {
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
        int m = l + (r - l) / 2;
        if (arr[m] < key) {
            l = m + 1;
        } else {
            if (m - 1 >= 0 && arr[m - 1] < key) {
                return m;
            }
            r = m - 1;
        }
    }
    return -1;
}
```

## [查找最后一个小于等于给定值的元素](binary_search_4.py)
```python
def search(self,arr,item):
    '''查找最后一个小于等于给定值的元素'''
    l=0
    r=len(arr)-1
    while True:
        m=(l+r)//2
        if arr[m]>item:
            r=m-1
        else:
            if m==len(arr)-1 or arr[m+1]>item:# 终止条件
                return m
            l=m+1
        if l>r:#注意二分查找可以相等,与排序的递归退出条件不同
            return -1
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