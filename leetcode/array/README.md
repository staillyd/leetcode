# 数组
## [多数元素](169.py)
- [Link](https://leetcode-cn.com/problems/majority-element/)
- 给定一个大小为 n 的数组，找到其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。可以假设数组是非空的，并且给定的数组总是存在多数元素。
- 摩尔投票
- 字典计数
- 数组排序
```python
def majorityElement(self, nums: List[int]) -> int:
    '''查找数组中的多数元素,多数元素:出现次数>n/2的元素.
    
    @Note:
        对拼消耗,最差所有人都联合起来对付你
    '''
    major=None
    cnt=0
    for num in nums:
        if cnt==0:
            major=num
            cnt=1
        else:
            cnt+=1 if major==num else -1
    return major
```

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
- [Link](https://leetcode-cn.com/problems/remove-element/)
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
- [Link](https://leetcode-cn.com/problems/move-zeroes/)
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

## [数组中的重复数字](3.py)
- [Link](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)
- 在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
- 变量
  - i
  - num
  - nums\[num\]
```python
def findRepeatNumber(self, nums: List[int]) -> int:
    '''原地交换'''
    for i,num in enumerate(nums):
        while i!=num:#当前位索引!=当前位
            if num==nums[num]:#如果已经归位(nums[num])
                return num
            nums[i],nums[num]=nums[num],nums[i]#归位(nums[num])
            num=nums[i]
    return -1

def findRepeatNumber_del(self, nums: List[int]) -> int:
    '''内存占用高'''
    dic={}
    for i in nums:
        if i not in dic:
            dic[i]=True
        else:
            return i
    return -1
```

## [旋转数组](189.py)
- [Link](https://leetcode-cn.com/problems/rotate-array/)
- 给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数
- 反转数组可以用一个变量保存首位,然后遍历数组后索引赋值前值,末尾索引赋值保存的首位
```python
def rotate(self, nums: List[int], k: int) -> None:
    k=k%len(nums)
    if k==0:
        return
    nums[:]=nums[::-1]#反转数组
    nums[:k]=nums[:k][::-1]
    nums[k:]=nums[k:][::-1]
```

## [螺旋矩阵](54.py)
- [Link](https://leetcode-cn.com/problems/spiral-matrix/)
- 给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素
- 纯逻辑题.定义sx,sy,ex,ey.
```python
def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
    direct=0
    output_arr=[]
    sx,sy,ex,ey=0,0,len(matrix)-1,len(matrix[0])-1
    while sx<=ex and sy<=ey:
        if direct==0:
            output_arr.extend(matrix[sx][sy:ey+1])
            sx+=1
            direct=1
        elif direct==1:
            for x in range(sx,ex+1):
                output_arr.append(matrix[x][ey])
            ey-=1
            direct=2
        elif direct==2:
            for y in range(sy,ey+1)[::-1]:
                output_arr.append(matrix[ex][y])
            ex-=1
            direct=3
        elif direct==3:
            for x in range(sx,ex+1)[::-1]:
                output_arr.append(matrix[x][sy])
            sy+=1
            direct=0
    return output_arr
```

## [两数之和](1.py)
- [Link](https://leetcode-cn.com/problems/two-sum/)
- 给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出和为目标值target的那两个整数，并返回它们的数组下标。
```python
def twoSum(self, nums: List[int], target: int) -> List[int]:
    '''字典存储'''
    num_idx={}
    for i,num in enumerate(nums):
        find_num=target-num
        if find_num in num_idx:
            return [num_idx[find_num],i]
        num_idx[num]=i
```

## [三数之和](15.py)
- [Link](https://leetcode-cn.com/problems/3sum/submissions/)
- 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。
```python
def threeSum(self, nums: List[int]) -> List[List[int]]:
    '''a+b+c=0的不重复解
    
    @Note:
        排序,三指针,固定一个,剩余两个双边遍历
    '''
    ret=[]
    lens=len(nums)
    if lens<3:#特殊情况
        return []
    nums=sorted(nums)#排序
    for i in range(lens):
        a=nums[i]
        if a>0:#a>0,往后没解了
            break
        if i>0 and a==nums[i-1]:#去除重复解
            continue
        l=i+1
        r=lens-1
        while l<r:
            b,c=nums[l],nums[r]
            sum=a+b+c
            if sum==0:
                ret.append([a,b,c])
                while l<r and nums[l+1]==nums[l]:#下一个元素等于当前元素(去重)
                    l+=1
                l+=1
                while l<r and nums[r-1]==nums[r]:#下一个元素等于当前元素(去重)
                    r-=1
                r-=1
            elif sum<0:
                l+=1
            elif sum>0:
                r-=1
    return ret
```

## [四数之和](18.py)
- [Link](https://leetcode-cn.com/problems/4sum/)
- 给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
```python
def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
    '''a+b+c+d=target的不重复解
    
    @Note:
        排序,四指针,固定两个,剩余两个双边遍历
    '''
    ret=[]
    lens=len(nums)
    if lens<4:
        return []
    nums=sorted(nums)
    for i in range(lens):#当前循环获取当前值下所有合适解
        # if nums[i]>target:#与target=0不同
        #     break
        if i>0 and nums[i]==nums[i-1]:#注意边界
            continue
        for j in range(i+1,lens):#当前循环获取当前值下所有合适解
            if j>i+1 and nums[j]==nums[j-1]:
                continue
            l=j+1
            r=lens-1
            while l<r:
                sum=nums[i]+nums[j]+nums[l]+nums[r]
                if sum==target:
                    ret.append([nums[i],nums[j],nums[l],nums[r]])
                    while l<r and nums[l+1]==nums[l]:#下一值与当前值相等(去重)
                        l+=1
                    l+1
                    while l<r and nums[r-1]==nums[r]:
                        r-=1
                    r-=1
                elif sum>target:
                    r-=1
                else:
                    l+=1
    return ret
```

## [较小的三数和](259.py)
- [Link](https://leetcode-cn.com/problems/3sum-smaller/)
- 给定一个长度为 n 的整数数组和一个目标值 target，寻找能够使条件 nums[i] + nums[j] + nums[k] < target 成立的三元组  i, j, k 个数（0 <= i < j < k < n）
```python
def threeSumSmaller(self, nums: List[int], target: int) -> int:
    '''较小的三数和
    
    @Note:
        排序->三指针,固定一个,双边遍历
    '''
    count=0
    lens=len(nums)
    nums=sorted(nums)
    for i in range(lens):
        l=i+1
        r=lens-1
        while l<r:#当前i下的所有满足条件的个数
            if nums[i]+nums[l]+nums[r]>=target:
                r-=1
            else:
                count+=r-l
                l+=1#双边遍历
    return count
```

## [最接近的三数之和](16.py)
- [Link](https://leetcode-cn.com/problems/3sum-closest/)
- 给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。
```python
def threeSumClosest(self, nums: List[int], target: int) -> int:
    '''最接近的三数和
    
    @Note:
        排序->三指针,固定一个,双边遍历. 添加一个绝对差值判断
    '''
    lens=len(nums)
    nums=sorted(nums)
    diff=10000
    ret=None
    for i in range(lens):
        if i>0 and nums[i]==nums[i-1]:
            continue
        l=i+1
        r=lens-1
        while l<r:
            sum=nums[i]+nums[l]+nums[r]
            if abs(sum-target)<diff:
                diff=abs(sum-target)
                ret=sum
            if sum==target:
                return sum
            elif sum>target:
                r-=1
            elif sum<target:
                l+=1
    return ret
```

## [合并两个有序数组](88.py)
- [Link](https://github.com/doocs/leetcode/blob/main/solution/0000-0099/0088.Merge%20Sorted%20Array/README.md)
- 给你两个有序整数数组 nums1 和 nums2，请你将 nums2 合并到 nums1 中，使 nums1 成为一个有序数组。初始化 nums1 和 nums2 的元素数量分别为 m 和 n 。你可以假设 nums1 的空间大小等于 m + n，这样它就有足够的空间保存来自 nums2 的元素。
```python
def merge(self, nums1: List[int], m: int, nums2: List[int], n: int) -> None:
    '''合并两个有序数组
    
    @Note:
        类似归并排序，从后往前
    '''
    i,j,k=m-1,n-1,m+n-1
    if n==0:
        return
    while True:
        if nums1[i]>nums2[j]:
            nums1[k]=nums1[i]
            k-=1
            i-=1
        else:
            nums1[k]=nums2[j]
            j-=1
            k-=1
        if i==-1 or j==-1:
            break
    if i==-1:
        nums1[:j+1]=nums2[:j+1]#注意左闭右开
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

## [寻找旋转排序数组中的最小值 II]
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
