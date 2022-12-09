class Insert_Sort(object):

    def __init__(self) -> None:
        super().__init__()

    def sort(self, arr):
        '''
        
        @Note:将第一待排序序列第一个元素看做一个有序序列，把第二个元素到最后一个元素当成是未排序序列。
            从头到尾依次扫描未排序序列，将扫描到的每个元素插入有序序列的适当位置
        '''
        for i in range(1, len(arr)):
            num = arr[i]
            # for j in range(i)[::-1]:#i-1->0
            #     if arr[j]>num:
            #         arr[j+1]=arr[j]#索引j->j+1,j+1是当前所需要赋值的索引
            #         if j==0:#!!!注意边界条件!!!
            #             arr[j]=num
            #     else:
            #         arr[j+1]=num
            #         break
            j = i - 1
            while j >= 0 and arr[j] > num:
                arr[j + 1] = arr[j]
                j -= 1
            arr[j + 1] = num


if __name__ == '__main__':
    arr = [int(x) for x in input().strip().split(' ')]
    insert_sort = Insert_Sort()
    insert_sort.sort(arr)
    print(arr)
