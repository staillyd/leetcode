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