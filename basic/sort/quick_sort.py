class Quick_Sort(object):

    def __init__(self) -> None:
        super().__init__()

    def sort(self, arr, l, r):
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
        if l >= r:  #递归终止条件
            return
        num = arr[l]
        start = l
        end = r
        while start < end:  #!!!内部每条都要加在递归条件内的条件!!!
            while start < end and arr[end] >= num:  #向左查找<枢轴的索引
                end -= 1
            if start < end:
                arr[start] = arr[end]
                start += 1
            while start < end and arr[start] <= num:  #向右查找>枢轴的索引
                start += 1
            if start < end:
                arr[end] = arr[start]
                end -= 1
        arr[start] = num
        self.sort(arr, l, start - 1)
        self.sort(arr, start + 1, r)


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    quick_sort = Quick_Sort()
    quick_sort.sort(arr, 0, len(arr) - 1)
    print(arr)
