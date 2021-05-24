# 排序算法
## [冒泡排序](bobble_sort.py)
- $S(n)=O(1)$
- $T(n)=O(n^2)$
  1. 给定的数组按照顺序已经排好:只需要进行n-1次比较,两两交换次数为0,时间复杂度为$O(n)$
  2. 给定的数组按照逆序排列:需要进行$\frac{n*(n-1)}{2}$次比较,时间复杂度为,$O(n^2)$
  3. 给定的数组杂乱无章.在这种情况下,平均时间复杂度$O(n^2)$
- 稳定的排序算法(**两个相等的数，在排序过后，相对位置保持不变**)
```python
'''时间复杂度分情况讨论
        
@Note:
    固定顺序位(a[i]),比较迭代位与后一位，如果不需要交换则表明已经排好序，将最大值填充到固定的顺序位中
'''
for i in range(len(arr)):
    finish=True
    for j in range(len(arr)-i-1):
        if arr[j]>arr[j+1]:
            arr[j],arr[j+1]=arr[j+1],arr[j]
            finish=False
    if finish:
        break
```

``` python
'''舍弃  这种方式不同情况的时间复杂度都是$O(n^2)$
        
@Note:
    固定顺序位(a[i]),比较固定位和迭代位，将最小值填充到固定的顺序位中
    有点像选择排序法(在未排序序列中找到最小元素，存放到排序序列的起始位置)
'''
for i in range(len(arr)):
    for j in range(i+1,len(arr)):
        if arr[i]>arr[j]:
            arr[i],arr[j]=arr[j],arr[i]
```

## [插入排序法](insert_sort.py)
- $S(n)=O(1)$
- $T(n)=O(n^2)$
  1. 给定的数组按照顺序已经排好:只需要进行n-1次比较,两两交换次数为0,时间复杂度为$O(n)$
  2. 给定的数组按照逆序排列:需要进行$\frac{n*(n-1)}{2}$次比较,时间复杂度为,$O(n^2)$
  3. 给定的数组杂乱无章.在这种情况下,平均时间复杂度$O(n^2)$
- 稳定的排序算法(两个相等的数，在排序过后，相对位置保持不变)
```python
'''
        
@Note:将第一待排序序列第一个元素看做一个有序序列，把第二个元素到最后一个元素当成是未排序序列。
    从头到尾依次扫描未排序序列，将扫描到的每个元素插入有序序列的适当位置
'''
for i in range(1,len(arr)):
    num=arr[i]
    for j in range(i)[::-1]:#i-1->0
        if arr[j]>num:
            arr[j+1]=arr[j]#索引j->j+1,j+1是当前所需要赋值的索引
        else:
            arr[j+1]=num
            break
```

## [选择排序法](select_sort.py)
- $S(n)=O(1)$
- $T(n)=O(n^2)$
- 选择排序是一种不稳定的排序算法
  -  5，8，5，2，9 这样一组数据，使用选择排序算法来排序的话，第一次找到最小元素 2，与第一个 5 交换位置，那第一个 5 和中间的 5 顺序就变了，所以就不稳定了。正是因此，相对于冒泡排序和插入排序，选择排序就稍微逊色了。

```python
'''
        
@Note:
    在未排序序列中找到最小元素，存放到排序序列的起始位置
'''
for i in range(len(arr)):
    min_index=i
    for j in range(i+1,len(arr)):
        if arr[j]<arr[min_index]:
            min_index=j
    arr[i],arr[min_index]=arr[min_index],arr[i]
```

## [归并排序](merge_sort.py)
- $S(n)=O(n)$
- $T(n)=O(n^2)$
- 对于规模为 n 的问题,一共要进行 log(n) 次的切分,每一层的合并复杂度都是 O(n),所以整体时间复杂度为 O(nlogn)
- 合并 n 个元素需要分配一个大小为 n 的额外数组，所以空间复杂度为 O(n)
- 归并排序是稳定的排序算法
- 注意边界条件
```python
def merge(self,arr,l,m,r):
    '''合并两顺序数组
    
    @param:
        arr:     list    输入数组
        l:       int     左边界开始索引
        m:       int     右边界开始索引
        r:       int     右边界结束索引+1
    @Note:
        复制两子数组->合并两数组到原数组对应位置
    '''
    # 复制子数组
    a=[x for x in arr[l:m]]
    b=[x for x in arr[m:r]]
    # 合并两顺序数组
    a_idx,b_idx,arr_idx=0,0,l
    while True:
        if a[a_idx]<b[b_idx]:
            arr[arr_idx]=a[a_idx]
            a_idx+=1
            arr_idx+=1
        else:
            arr[arr_idx]=b[b_idx]
            b_idx+=1
            arr_idx+=1
        if a_idx==len(a) or b_idx==len(b):#注意边界条件
            break
    
    if a_idx!=len(a):
        arr[arr_idx:r]=a[a_idx:]
    if b_idx!=len(b):
        arr[arr_idx:r]=b[b_idx:]

def sort(self,arr,l,r):
    '''
    
    @Note:
        左排序->右排序->合并
    '''
    if l>=r:#递归终止条件
        return
    m=(l+r)//2
    self.sort(arr,l,m)
    self.sort(arr,m+1,r)
    self.merge(arr,l,m+1,r+1)
```

## [快速排序](quick_sort.py)
- $S(n)=O(1)*O(log(n))=O(log(n))$
- $T(n)=O(nlog(n))$
- 对于规模为 n 的问题,一共要进行 log(n) 次的切分,每一层的复杂度都是 O(n),所以整体时间复杂度为 O(nlogn)
  - 但是，如果每次在选择基准值的时候，都不幸地选择了子数组里的最大或最小值。即每次把把数组分成了两个更小长度的数组，其中一个长度为 1，另一个的长度是子数组的长度减 1。这样的算法复杂度变成 O(n²)。
- 快速排序法的优化
  - 最理想的基准点是：被基准点分开的两个子数组中，数据的数量差不多。
  - 三数取中法:从区间的首、尾、中间，分别取出一个数，然后对比大小，取这 3 个数的中间值作为分区点
```python
def sort(self,arr,l,r):
    '''递归,注意终止条件
    
    @Note:
        1->2->3:把数组变为 <=R,R,>=R
        1:定枢轴
        2:循环(!!!内部每条都要加在递归条件内的条件!!!)
            1:向左查找<枢轴的索引
            2:替换左索引元素,左索引右移
            3:向右查找>枢轴的索引
            4:替换右索引元素,右索引左移
        3:左索引元素=枢轴
        4:左半、右半快排
    '''
    if l>=r:#递归终止条件
        return
    num=arr[l]
    start=l
    end=r
    while start<end:#!!!内部每条都要加在递归条件内的条件!!!
        while start<end and arr[end]>=num:#向左查找<枢轴的索引
            end-=1
        if start<end:
            arr[start]=arr[end]
            start+=1
        while start<end and arr[start]<=num:#向右查找>枢轴的索引
            start+=1
        if start<end:
            arr[end]=arr[start]
            end-=1
    arr[start]=num
    self.sort(arr,l,start-1)
    self.sort(arr,start+1,r)
```
