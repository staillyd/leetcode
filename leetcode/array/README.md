# 数组
## [删除有序数组中的重复项](leetcode/array/26.py)
- [Link](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array/)
- 给你一个有序数组nums,请你**原地**删除重复出现的元素，使每个元素只出现一次 ，返回删除后数组的新长度。不要使用额外的数组空间，你必须在**原地**修改输入数组并在使用 O(1) 额外空间的条件下完成

```python
def removeDuplicates(self, nums: List[int]) -> int:
    '''快慢指针'''
    j=1#慢指针
    for i in range(1,len(nums)):#快指针
        if nums[i]!=nums[j-1]:
            nums[j]=nums[i]
            j+=1
    return j
```

```python
'''舍弃'''
def removeDuplicates_del(self, nums: List[int]) -> int:
    cnt=0#重复个数
    len_=len(nums)
    for i in range(1,len_):
        replace_i=i-cnt#replace_i:不重复时需要替换的位置
        if nums[i]!=nums[replace_i-1]:#i:当前元素
            nums[replace_i]=nums[i]
        else:
            cnt+=1
    return len_-cnt
```
## [删除有序数组中的重复项 II](80.py)
- [Link](https://leetcode-cn.com/problems/remove-duplicates-from-sorted-array-ii/)
- 给你一个有序数组 nums ，请你 原地 删除重复出现的元素，使每个元素 **最多出现两次** ，返回删除后数组的新长度。不要使用额外的数组空间，你必须在 原地 修改输入数组 并在使用 O(1) 额外空间的条件下完成。
```python
def removeDuplicates(self, nums: List[int]) -> int:
    '''快慢指针'''
    j=2
    for i in range(2,len(nums)):
        if nums[i]!=nums[j-2]:
            nums[j]=nums[i]
            j+=1
    return j
```

```python
'''舍弃'''
def removeDuplicates_del(self, nums: List[int]) -> int:
    cnt=0#超过两次的个数
    this_num_cnt=1#当前数字出现的次数
    len_=len(nums)
    for i in range(1,len_):
        replace_i=i-cnt#replace_i:需要替换的位置
        if nums[i]!=nums[replace_i-1]:
            nums[replace_i]=nums[i]
            this_num_cnt=1
        else:
            this_num_cnt+=1
            if this_num_cnt<=2:
                nums[replace_i]=nums[i]
            else:
                cnt+=1
    return len_-cnt
```

## [移除元素](27.py)
- 给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 原地 修改输入数组。元素的顺序可以改变。你**不需要考虑数组中超出新长度后面的元素**。
```python
def removeElement(self, nums: List[int], val: int) -> int:
    '''快慢指针,遍历一次,不管后面的元素'''
    slow=0
    for fast in range(len(nums)):
        if nums[fast]!=val:
            nums[slow]=nums[fast]
            slow+=1
    return slow
```
```python
def removeElement_modify(self, nums: List[int], val: int) -> int:
    '''首尾指针'''
    l=0
    r=len(nums)-1
    while l<=r:#和快排不同处,在l==r时不跳出
        if nums[l]==val:#避免重复赋值
            nums[l]=nums[r]
            r=r-1
        else:
            l+=1
    return l
```

## [移动零](283.py)
- 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
```python
def moveZeroes(self, nums: List[int]) -> None:
    '''快慢指针'''
    j=0
    for i in range(len(nums)):
        if nums[i]!=0:
            nums[j]=nums[i]
            j+=1
    
    for i in range(j,len(nums)):
        nums[i]=0
```