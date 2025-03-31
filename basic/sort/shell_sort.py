class Shell_Sort(object):

    def __init__(self) -> None:
        super().__init__()

    def sort(self, arr):
        '''
        
        @Note:
            间隔从l/2减小到1的过程中，将处在相同间隔的元素提取出来单独进行插入排序
        '''
        gap = len(arr) // 2
        while True:
            for i in range(gap):  #当前共gap组子数组
                # 对每个子数组,带gap的插入排序
                for j in range(i + gap, len(arr), gap):
                    num = arr[j]
                    for k in range(i, j, gap)[::-1]:  #在j之前gap开始每隔gap来一次
                        if arr[k] > num:
                            arr[k + gap] = arr[k]
                            if k == i:  #!!!注意边界条件!!!
                                arr[k] = num
                        else:
                            arr[k + gap] = num
                            break
            if gap == 1:
                break
            gap = gap // 2


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    shell_sort = Shell_Sort()
    shell_sort.sort(arr)
    print(arr)
