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
    固定顺序位arr[len(arr)-i-1],比较迭代位与后一位，如果不需要交换则表明已经排好序，将最大值填充到固定的顺序位中
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
def sort(self,arr):
    '''
    
    @Note:将第一待排序序列第一个元素看做一个有序序列，把第二个元素到最后一个元素当成是未排序序列。
        从头到尾依次扫描未排序序列，将扫描到的每个元素插入有序序列的适当位置
    '''
    for i in range(1,len(arr)):
        num=arr[i]
        for j in range(i)[::-1]:#i-1->0
            if arr[j]>num:
                arr[j+1]=arr[j]#索引j->j+1,j+1是当前所需要赋值的索引
                if j==0:#!!!注意边界条件!!!
                    arr[j]=num
            else:
                arr[j+1]=num
                break
```

## [希尔排序](shell_sort.py)
- 简单插入排序的一种改进版本
- $S(n)=O(1)$
- n小,$T(n)=O(n^2)$
- n大,$T(n)=O(nlog(n))$

```python
def sort(self,arr):
    '''
    
    @Note:
        间隔从l/2减小到1的过程中，将处在相同间隔的元素提取出来单独进行插入排序
    '''
    gap=len(arr)//2
    while True:
        for i in range(gap):#当前共gap组子数组
            # 对每个子数组,带gap的插入排序
            for j in range(i+gap,len(arr),gap):
                num=arr[j]
                for k in range(i,j,gap)[::-1]:#在j之前gap开始每隔gap来一次
                    if arr[k]>num:
                        arr[k+gap]=arr[k]
                        if k==i:#!!!注意边界条件!!!
                            arr[k]=num
                    else:
                        arr[k+gap]=num
                        break
        if gap==1:
            break
        gap=gap//2
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
- $T(n)=O(nlog(n))$
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

## [堆排序](heap_sort.py)
- 优先队列
- ![](imgs/堆.png)
```python
class PrioQueue:
    '''优先队列'''
    def __init__(self,l) -> None:
        self.arr=l
        if l:
            self.build_heap()
    
    def enqueue(self,num):
        '''入队'''
        self.arr.append(num)
        # 类似插入排序   最后一位上浮
        j=(len(self.arr)-1-1)//2#注意
        last_j=len(self.arr)-1
        while j>0 and self.arr[j]>num:
            self.arr[last_j]=self.arr[j]
            last_j=j
            j=(j-1)//2
        self.arr[last_j]=num

    def sift_down(self,select,num):
        '''类似插入排序  下沉
        
        @Note:
            select: 当前堆顶的索引
            num:    堆顶元素看成的数值，实际堆顶是什么无关紧要
        '''
        last_j=select
        j=2*select+1#堆的左侧
        while j<len(self.arr):
            if j+1<len(self.arr) and self.arr[j+1]<self.arr[j]:
                j+=1# 取堆左右侧更小的一侧作为当前位置
            if num<self.arr[j]:
                break#num<堆的左右两侧
            self.arr[last_j]=self.arr[j]
            last_j=j
            j=2*last_j+1
        self.arr[last_j]=num

    def dequeue(self):
        '''出队,返回堆顶(select),取出最后一个数,把他当成堆顶
        第一位下沉到合适位置'''
        ret=self.arr[0]
        num=self.arr.pop()
        if len(self.arr)>0:
            self.sift_down(0,num)
        return ret

    def build_heap(self):
        '''对一个列表进行堆的初始化,从非叶子节点开始(end//2往0排)'''
        for i in range(len(self.arr)//2,-1,-1):
            self.sift_down(i,self.arr[i])

if __name__=='__main__':
    # heap_sort: 构建堆(sift_down)->出列
    solution=PrioQueue([1,3,4,2,1,5,4])
    while len(solution.arr)>0:
        print(solution.dequeue())

```