# 查找算法
## [二分查找](binary_search.py)
- $T(n)=O(nlog(n))$
```python
def search(self,arr,item):
    l=0
    r=len(arr)-1
    while True:
        m=(l+r)//2
        if arr[m]==item:
            return m
        elif arr[m]<item:
            l=m+1
        elif arr[m]>item:
            r=m-1
        if l>r:#注意二分查找可以相等,与排序的递归退出条件不同
            return -1
```

## [查找第一个等于给定值](binary_search_1.py)
```python
def search(self,arr,item):
    '''查找第一个值等于给定值的元素'''
    l=0
    r=len(arr)-1
    while True:
        m=(l+r)//2
        if arr[m]<item:
            l=m+1
        elif arr[m]>item:
            r=m-1
        else:
            if m==0 or arr[m-1]!=item:# 终止条件
                return m
            r=m-1
        if l>r:#注意二分查找可以相等,与排序的递归退出条件不同
            return -1
```

## [查找最后一个值等于给定值的元素](binary_search_2.py)
```python
def search(self,arr,item):
    '''查找最后一个值等于给定值的元素'''
    l=0
    r=len(arr)-1
    while True:
        m=(l+r)//2
        if arr[m]<item:
            l=m+1
        elif arr[m]>item:
            r=m-1
        else:
            if m==len(arr)-1 or arr[m+1]!=item:# 终止条件
                return m
            l=m+1
        if l>r:#注意二分查找可以相等,与排序的递归退出条件不同
            return -1
```

## [查找第一个大于等于给定值的元素](binary_search_3.py)
```python
def search(self,arr,item):
    '''查找第一个大于等于给定值的元素'''
    l=0
    r=len(arr)-1
    while True:
        m=(l+r)//2
        if arr[m]<item:
            l=m+1
        else:
            if m==0 or arr[m-1]<item:# 终止条件
                return m
            r=m-1
        if l>r:#注意二分查找可以相等,与排序的递归退出条件不同
            return -1
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