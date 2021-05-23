class Select_Sort(object):
    def __init__(self) -> None:
        super().__init__()
    
    def sort(self,arr):
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

if __name__=='__main__':
    arr=[int(x) for x  in input().strip().split(' ')]
    insert_sort=Select_Sort()
    insert_sort.sort(arr)
    print(arr)