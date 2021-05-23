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

