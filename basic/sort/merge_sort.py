class Merge_Sort(object):

    def ____init__(self) -> None:
        super().__init__()

    def merge(self, arr, l, m, r):
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
        a = [x for x in arr[l:m]]
        b = [x for x in arr[m:r]]
        # 合并两顺序数组
        a_idx, b_idx, arr_idx = 0, 0, l
        while True:
            if a[a_idx] < b[b_idx]:
                arr[arr_idx] = a[a_idx]
                a_idx += 1
                arr_idx += 1
            else:
                arr[arr_idx] = b[b_idx]
                b_idx += 1
                arr_idx += 1
            if a_idx == len(a) or b_idx == len(b):  #注意边界条件
                break

        if a_idx != len(a):
            arr[arr_idx:r] = a[a_idx:]
        if b_idx != len(b):
            arr[arr_idx:r] = b[b_idx:]

    def sort(self, arr, l, r):
        '''
        
        @Note:
            左排序->右排序->合并
        '''
        if l >= r:  #递归终止条件
            return
        m = (l + r) // 2
        self.sort(arr, l, m)
        self.sort(arr, m + 1, r)
        self.merge(arr, l, m + 1, r + 1)


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    merge_sort = Merge_Sort()
    merge_sort.sort(arr, 0, len(arr) - 1)
    print(arr)
