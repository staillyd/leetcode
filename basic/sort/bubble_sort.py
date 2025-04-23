class Bubble_Sort(object):

    def __init__(self) -> None:
        super().__init__()

    def sort(self, arr):
        '''舍弃 这种方式不同情况的时间复杂度都是$O(n^2)$
        
        @Note:
            固定顺序位(a[i]),比较固定位和迭代位，将最小值填充到固定的顺序位中
            有点像选择排序法(在未排序序列中找到最小元素，存放到排序序列的起始位置)
        '''
        for i in range(len(arr)):
            for j in range(i + 1, len(arr)):
                if arr[i] > arr[j]:
                    arr[i], arr[j] = arr[j], arr[i]

    def sort_true(self, arr):
        '''时间复杂度分情况讨论
        
        @Note:
            固定顺序位arr[len(arr)-i-1],比较迭代位与后一位，如果不需要交换则表明已经排好序，将最大值填充到固定的顺序位中
        '''
        for i in range(len(arr)):
            finish = True
            for j in range(len(arr) - i - 1):
                if arr[j] > arr[j + 1]:
                    arr[j], arr[j + 1] = arr[j + 1], arr[j]
                    finish = False
            if finish:
                break


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    bubble_sort = Bubble_Sort()
    bubble_sort.sort_true(arr)
    print(arr)
